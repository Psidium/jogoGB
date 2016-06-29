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

#include "png_texture.h"


#define TILE_MAP_WIDTH 200
#define TILE_MAP_HEIGHT TILE_MAP_WIDTH/2
#define TILE_MAP_SIZE 5

#define VIEWPORT_X TILE_MAP_WIDTH * TILE_MAP_SIZE
#define VIEWPORT_Y TILE_MAP_HEIGHT * TILE_MAP_SIZE



struct TileColor {
    GLubyte r,
     g,
     b;
};

typedef struct {
    float x;
    float y;
} Pointf;

struct SpriteId {
    Pointf lower_left = {0, 0};
    Pointf upper_left = {0,1};
    Pointf upper_right = {1,1};
    Pointf lower_right = {1, 0};
    bool hidden = false;
};

std::vector<std::vector<SpriteId> > fix_ground_ids;

std::vector<GLogic::Projectile> projectiles;
int ground_id;
int sprite_id;

GLuint* ids;

GLogic::Hero* hero;
void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    
    ground_id = png_texture_load("chao_tex.png", NULL, NULL);
    
    
    fix_ground_ids.resize(TILE_MAP_SIZE);
    for (int i = 0 ; i < fix_ground_ids.size(); i++ ) {
        fix_ground_ids[i].resize(TILE_MAP_SIZE);
        for (int j =0; j< TILE_MAP_SIZE; j++) {
            fix_ground_ids[i][j].hidden = true;
        }
    }
    sprite_id = png_texture_load("sprite_signos.png", NULL, NULL);
    
    /*
     [ [0,2], [1,2], [2,2], [3,2]
       [0,1], [1,1], [2,1], [3,1]
       [0,0], [1,0], [2,0], [3,0] ]
     */
    std::vector<SpriteId*> selected_tiles(12);
    selected_tiles[0] = &fix_ground_ids[4][2];//sagitario
    selected_tiles[1] = &fix_ground_ids[1][4];//leao
    selected_tiles[2] = &fix_ground_ids[1][0];//aries
    selected_tiles[3] = &fix_ground_ids[4][1];//capricornio
    selected_tiles[4] = &fix_ground_ids[2][4];//virgem
    selected_tiles[5] = &fix_ground_ids[0][1];//touro
    selected_tiles[6] = &fix_ground_ids[3][0];//acuario
    selected_tiles[7] = &fix_ground_ids[3][4];//libra
    selected_tiles[8] = &fix_ground_ids[0][2];//gemeos
    selected_tiles[9] = &fix_ground_ids[2][0];//peixes
    selected_tiles[10] = &fix_ground_ids[4][3];//escorpiao
    selected_tiles[11] = &fix_ground_ids[0][3];//cancer
    int k = 0;
    float sprite_height = 1/3.0f;
    float sprite_width = 1/4.0f;
    for (int i = 0; i < 4; i++) {
        for (int j =0; j < 3; j++){
            selected_tiles[k]->lower_left.x = i * sprite_width;
            selected_tiles[k]->lower_left.y = j * sprite_height;
            selected_tiles[k]->upper_left.x = i * sprite_width;
            selected_tiles[k]->upper_left.y = (j+1) * sprite_height;
            selected_tiles[k]->lower_right.x = (i+1) * sprite_width;
            selected_tiles[k]->lower_right.y = j * sprite_height;
            selected_tiles[k]->upper_right.x = (i+1) * sprite_width;
            selected_tiles[k]->upper_right.y = (j+1) * sprite_height;
            selected_tiles[k]->hidden = false;
            k++;
        }
    }
    
    //============= UNUSED SO FAR
    ids = (GLuint*) calloc(3,sizeof(GLuint));
    
    char* filenames[] = {"bichooo_bin.ptm"};
    const int texLength = 1;
    glGenTextures(texLength, ids);
    for (int i = 0; i < texLength; i++) {
        Image* image = readImage(filenames[i]);
        glBindTexture(GL_TEXTURE_2D, ids[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());
    }
    
    int foo[8];
    for (int i =0; i< 8; i++) {
        foo[i] = ids[0];
    }
    hero = new GLogic::Hero(foo, 15);
    
    
    // ================= END OF UNUSED
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, VIEWPORT_X, -VIEWPORT_Y/2 + TILE_MAP_HEIGHT/2, VIEWPORT_Y/2 + TILE_MAP_HEIGHT/2, -VIEWPORT_X, VIEWPORT_Y);
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

void draw_losang_line(int x, int y, int log_width, int log_height) {
    glBegin(GL_LINE_LOOP);
    //x and y are the lower left point of the losang of width and height
    glVertex2f(x, y + log_height/2.0f); //x on the leftmost, y on center
    glVertex2f(x + log_width/2.0f, y + log_height);
    glVertex2f(x + log_width, y + log_height/2.0f);
    glVertex2f(x + log_width/2.0f, y);
    glEnd();
}

void draw_losang_tex(SpriteId sprite, int x, int y, int log_width, int log_height) {
    glBegin(GL_POLYGON);
    glTexCoord2f(sprite.lower_left.x,sprite.lower_left.y);
    glVertex2f(x, y + log_height/2.0f);
    glTexCoord2f(sprite.upper_left.x,sprite.upper_right.y);
    glVertex2f(x + log_width/2.0f, y + log_height);
    glTexCoord2f(sprite.upper_right.x,sprite.upper_right.y);
    glVertex2f(x + log_width, y + log_height/2.0f);
    glTexCoord2f(sprite.lower_right.x,sprite.lower_right.y);
    glVertex2f(x + log_width/2.0f, y);
    glEnd();
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
    
    int* x = (int*) calloc(1, sizeof(int));
    int* y = (int*) calloc(1, sizeof(int));
    
    SpriteId sp_hold;
    for (int i = 0; i < TILE_MAP_SIZE; i++) {
        for (int j = (int) TILE_MAP_SIZE - 1; j >= 0; j--) {
            glColor3ub(0, 0, 0);
            calculate_losang_lower_left_point(x, y, i, j, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            draw_losang_line(*x, *y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            glColor3ub(255, 255, 255);
            glBindTexture(GL_TEXTURE_2D, ground_id);
            draw_losang_tex(sp_hold, *x, *y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            
            if (!fix_ground_ids[i][j].hidden) {
                glBindTexture(GL_TEXTURE_2D, sprite_id);
                draw_losang_tex(fix_ground_ids[i][j], *x, *y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            }
        }
    }
    
    glFlush();
    
    //glutPostRedisplay();
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
