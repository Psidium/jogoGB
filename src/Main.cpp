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

#include "GLEnums.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"

#define VIEWPORT_X 900
#define VIEWPORT_Y 450

#define TILE_MAP_WIDTH 30
#define TILE_MAP_HEIGHT 15


struct QuickColor {
    GLubyte r,
     g,
     b;
};


std::vector<std::vector<QuickColor*> > tile_map;

void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    tile_map.resize(30);
    for (int i = 0 ; i < tile_map.size(); i++ ) {
        tile_map[i].resize(30);
    }
    
    bool eita = true;
    for (int x = 0; x < tile_map.size(); x++) {
        eita = !eita;
        for (int y =0; y < tile_map[x].size(); y++) {
            QuickColor *quick_color = new QuickColor();
            if (eita) {
                quick_color->r = 0;
                quick_color->g = 0;
                quick_color->b = 0;
            } else {
                quick_color->r = 127;
                quick_color->g = 127;
                quick_color->b = 127;
            }
            eita = !eita;
            tile_map[x][y] = quick_color;
        }
    }
    
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, VIEWPORT_X, -VIEWPORT_Y/2 - 10, VIEWPORT_Y/2 + 10, -VIEWPORT_X, VIEWPORT_Y);
}


void reshape(int width, int height){
    glutReshapeWindow(VIEWPORT_X, VIEWPORT_Y);
}

void keyboard(unsigned char key, int x, int y){
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

void draw_losang(int x, int y, int log_width, int log_height) {
    //x and y are the lower left point of the losang of width and height
    glVertex2f(x, y + log_height/2.0f); //x on the leftmost, y on center
    glVertex2f(x + log_width/2.0f, y + log_height);
    glVertex2f(x + log_width, y + log_height/2.0f);
    glVertex2f(x + log_width/2.0f, y);
}

void calculate_losang_lower_left_point(int* x, int* y, int collumn, int row, int log_width, int log_height) {
    //sor quer que mude pra ponto inferior esquerdo
    *x = collumn * log_width/2 + row * log_width/2;
    *y = collumn * log_height/2 - row * log_height/2;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_QUADS);
    
    const int log_width = TILE_MAP_WIDTH;
    const int log_height = TILE_MAP_HEIGHT;
    int* x = (int*) calloc(1, sizeof(int));
    int* y = (int*) calloc(1, sizeof(int));
    for (int i = 0; i < tile_map.size(); i++) {
        for (int j = (int) tile_map[i].size() - 1; j >= 0; j--) {
            const QuickColor quick_color = *tile_map[i][j];
            glColor3ub(quick_color.r, quick_color.g, quick_color.b);
            calculate_losang_lower_left_point(x, y, i, j, log_width, log_height);
            if (*x < 0) {
                wait(NULL);
            }
            draw_losang(*x, *y, log_width, log_height);
        }
    }
    glEnd();
    
    glFlush();
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
    glutSpecialFunc(specialInput);
    glutSpecialUpFunc(specialUp);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
