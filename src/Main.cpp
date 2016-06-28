//
//  main.cpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#import <vector>
#include "slidemap_help.hpp"
#include "Loader.hpp"

#include "GLEnums.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"
#include "GLenums.hpp"

#define VIEWPORT_X 900
#define VIEWPORT_Y 450

#define TILE_MAP_WIDTH 90
#define TILE_MAP_HEIGHT 45
#define TILE_MAP_SIZE 7


struct TileColor {
    GLubyte r,
     g,
     b;
};


std::vector<std::vector<TileColor*> > tile_map;

std::vector<GLogic::Projectile> projectiles;
GLuint* ids;

GLogic::Hero* hero;
void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    
    tile_map.resize(TILE_MAP_SIZE);
    for (int i = 0 ; i < tile_map.size(); i++ ) {
        tile_map[i].resize(TILE_MAP_SIZE);
    }
    
    bool eita = true;
    for (int x = 0; x < tile_map.size(); x++) {
        for (int y =0; y < tile_map[x].size(); y++) {
            TileColor *quick_color = new TileColor();
            quick_color->r = 255;
            quick_color->g = 255;
            quick_color->b = 255;
            tile_map[x][y] = quick_color;
        }
    }
    
    ids = (GLuint*) calloc(2,sizeof(GLuint));
    char* filenames[] = {"bichooo_bin.ptm", "mapa.ptm"};
    const int texLength = 2;
    glGenTextures(texLength, ids);
    for (int i = 0; i < texLength; i++) {
        Image* image = readImage(filenames[i]);
        glBindTexture(GL_TEXTURE_2D, ids[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());
    }
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    int foo[8];
    for (int i =0; i< 8; i++) {
        foo[i] = ids[0];
    }
    hero = new GLogic::Hero(foo, 15);
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, VIEWPORT_X, -VIEWPORT_Y/2 - 10, VIEWPORT_Y/2 + 10, -VIEWPORT_X, VIEWPORT_Y);
}


void reshape(int width, int height){
    glutReshapeWindow(VIEWPORT_X, VIEWPORT_Y);
}

void keyboard(unsigned char key, int x, int y){
    switch(key) {
        case 'w':
            hero->walk(GLogic::NORTH);
            break;
        case 'a':
            hero->walk(GLogic::WEST);
            break;
        case 's':
            hero->walk(GLogic::SOUTH);
            break;
        case 'd':
            hero->walk(GLogic::EAST);
            break;
        case 'q':
            hero->walk(GLogic::NORTHWEST);
            break;
        case 'e':
            hero->walk(GLogic::NORTHEAST);
            break;
        case 'x':
            hero->walk(GLogic::SOUTHEAST);
            break;
        case 'z':
            hero->walk(GLogic::SOUTHWEST);
            break;
    }
    glutPostRedisplay();
}

void specialInput(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
    }
}


void specialUp(int key, int x, int y) {
}

void draw_losang(int x, int y, int log_width, int log_height) {
    //x and y are the lower left point of the losang of width and height
    glTexCoord2f(0,0);
    glVertex2f(x, y + log_height/2.0f); //x on the leftmost, y on center
    glTexCoord2f(0, 1);
    glVertex2f(x + log_width/2.0f, y + log_height);
    glTexCoord2f(1,1);
    glVertex2f(x + log_width, y + log_height/2.0f);
    glTexCoord2f(1,0);
    glVertex2f(x + log_width/2.0f, y);
}

void calculate_losang_lower_left_point(int* x, int* y, int collumn, int row, int log_width, int log_height) {
    //sor quer que mude pra ponto inferior esquerdo
    *x = collumn * log_width/2 + row * log_width/2;
    *y = collumn * log_height/2 - row * log_height/2;
}

void mouse(int button, int state, int mx, int my)
{
    std::cout << "it is at " << mx << " and " << my << "\n";
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glBindTexture(GL_TEXTURE_2D, ids[1]);
    glBegin(GL_QUADS);
    //x and y are the lower left point of the losang of width and height
    glTexCoord2f(0,0);
    glVertex2f(0, 0); //x on the leftmost, y on center
    glTexCoord2f(0, 1);
    glVertex2f(VIEWPORT_X/2.0f, VIEWPORT_Y/2.0f);
    glTexCoord2f(1,1);
    glVertex2f(VIEWPORT_X, 0);
    glTexCoord2f(1,0);
    glVertex2f(VIEWPORT_X/2.0f, -VIEWPORT_Y/2.0f);
    glEnd();
    
    const int log_width = TILE_MAP_WIDTH;
    const int log_height = TILE_MAP_HEIGHT;
    int* x = (int*) calloc(1, sizeof(int));
    int* y = (int*) calloc(1, sizeof(int));
    
    glColor3ub(255, 255, 255);
    
    glBindTexture(GL_TEXTURE_2D, hero->getTextureID());
    Point heroLocation = hero->getLocation();
    calculate_losang_lower_left_point(x, y, heroLocation.x, heroLocation.y, log_width, log_height);
    draw_losang(*x, *y, log_width, log_height);
    
    
    
    
    glFlush();
    
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(specialInput);
    glutSpecialUpFunc(specialUp);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
