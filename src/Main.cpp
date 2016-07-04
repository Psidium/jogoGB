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
#include "SpriteId.hpp"

#include "png_texture.h"


#define TILE_MAP_WIDTH 200
#define TILE_MAP_HEIGHT (TILE_MAP_WIDTH/2)
#define TILE_MAP_SIZE 5

#define VIEWPORT_X (TILE_MAP_WIDTH * TILE_MAP_SIZE)
#define VIEWPORT_Y (TILE_MAP_HEIGHT * TILE_MAP_SIZE)


GLogic::Enemy* active_enemy;

GLogic::PointControl pointControl;
std::vector<std::vector<SpriteId> > fix_ground_ids;

GLogic::Projectile* projectile;

std::map<Point, GLogic::Sign> signOfPoint;

int ground_id;

GLuint* ids;

GLogic::Hero* hero;

char* pontos = (char*)calloc(5, sizeof(char));

int lifebar_text;

void calculate_losang_lower_left_point(int* x, int* y, int collumn, int row, int log_width, int log_height) {
    *x = collumn * log_width/2 + row * log_width/2;
    *y = collumn * log_height/2 - row * log_height/2;
}

Point calculate_losang_lower_left_point(Point tile_location, int log_width, int log_height) {
    int x, y;
    calculate_losang_lower_left_point(&x, &y, tile_location.x, tile_location.y, log_width, log_height);
    Point out;
    out.x = x;
    out.y = y;
    return out;
}

void calculate_row_collumn_of_point(int *row, int* collumn, int x, int y, int log_width, int log_height) {
    *row =(int)( (float) x/log_width - (float)  y /log_height );
    *collumn = (int) ((float) y/log_height + (float)x/log_width);
}

Point calculate_row_collumn_of_point(Point raw_point, int log_width, int log_height) {
    int row, collumn;
    calculate_row_collumn_of_point(&row, &collumn, raw_point.x, raw_point.y, log_width, log_height);
    Point out;
    out.y = row;
    out.x = collumn;
    return out;
}

void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    
    // ====================================== LOAD TEXTURA DO CHAO
    ground_id = png_texture_load("chao_tex.png", NULL, NULL);
    
    
    fix_ground_ids.resize(TILE_MAP_SIZE);
    for (int i = 0 ; i < fix_ground_ids.size(); i++ ) {
        fix_ground_ids[i].resize(TILE_MAP_SIZE);
        for (int j =0; j< TILE_MAP_SIZE; j++) {
            fix_ground_ids[i][j].hidden = true;
        }
    }
    
    
    // ========================================= LOAD SIGNOS
    int sprite_id = png_texture_load("sprite_signos.png", NULL, NULL);
    
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
            selected_tiles[k]->texture = sprite_id;
            k++;
        }
    }
    
    signOfPoint[(Point){4,2}] = GLogic::SAGITARIO;
    signOfPoint[(Point){1,4}] = GLogic::LEAO;
    signOfPoint[(Point){1,0}] = GLogic::ARIES;
    signOfPoint[(Point){4,1}] = GLogic::CAPRICORNIO;
    signOfPoint[(Point){2,4}] = GLogic::VIRGEM;
    signOfPoint[(Point){0,1}] = GLogic::TOURO;
    signOfPoint[(Point){3,0}] = GLogic::AQUARIO;
    signOfPoint[(Point){3,4}] = GLogic::LIBRA;
    signOfPoint[(Point){0,2}] = GLogic::GEMEOS;
    signOfPoint[(Point){2,0}] = GLogic::PEIXES;
    signOfPoint[(Point){4,3}] = GLogic::ESCORPIAO;
    signOfPoint[(Point){0,3}] = GLogic::CANCER;
    
    
    //============================== load HERO
    int hero_id = png_texture_load("hero_sprite.png", NULL, NULL);
    GameObject* h_objs[8];
    sprite_width = 1/3.0f;
    sprite_height = 1/8.0f;
    float x_coords[4] = {0, sprite_width, 2*sprite_width, 3*sprite_width};
    for (int i =0; i< 8; i++) {
        Animation* anim = new Animation(3);
        for (int j=0; j<3; j++) {
            SpriteId* sprite = new SpriteId;
            sprite->hidden = false;
            sprite->lower_left.x = x_coords[j];
            sprite->lower_left.y = i * sprite_height;
            sprite->upper_left.x = x_coords[j];
            sprite->upper_left.y = (i+1) * sprite_height;
            sprite->lower_right.x = x_coords[j+1];
            sprite->lower_right.y = i * sprite_height;
            sprite->upper_right.x = x_coords[j+1];
            sprite->upper_right.y = (i+1) * sprite_height;
            sprite->texture = hero_id;
            anim->addFrame(sprite);
        }
        
        h_objs[i] = new GameObject();
        h_objs[i]->setSprite(anim);
    }
    
    hero = new GLogic::Hero(h_objs, TILE_MAP_SIZE);
    
    Point heroLoc;
    calculate_losang_lower_left_point(&heroLoc.x, &heroLoc.y, 0, 1, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
    heroLoc.x += TILE_MAP_WIDTH/4.0f;
    heroLoc.y += TILE_MAP_HEIGHT/3.0f;
    hero->setPixelLocation(heroLoc);
    hero->setLocation((Point) {0,1});
    
    
    /////============================ LOAD ENEMYS
    
    
    int en_id = png_texture_load("signos_enemy.png", NULL, NULL);
    k=0;
    sprite_height = 1/3.0f;
    sprite_width = 1/4.0f;
    GLogic::Sign signos[] = {GLogic::SAGITARIO, GLogic::LEAO, GLogic::ARIES, GLogic::CAPRICORNIO, GLogic::VIRGEM, GLogic::TOURO, GLogic::AQUARIO, GLogic::LIBRA, GLogic::GEMEOS, GLogic::PEIXES, GLogic::ESCORPIAO, GLogic::CANCER};
    for (int i=0; i< 4; i++) {
        for (int j=0; j < 3; j++) {
            SpriteId sprite;
            sprite.lower_left.x = i * sprite_width;
            sprite.lower_left.y = j * sprite_height;
            sprite.upper_left.x = i * sprite_width;
            sprite.upper_left.y = (j+1) * sprite_height;
            sprite.lower_right.x = (i+1) * sprite_width;
            sprite.lower_right.y = j * sprite_height;
            sprite.upper_right.x = (i+1) * sprite_width;
            sprite.upper_right.y = (j+1) * sprite_height;
            sprite.hidden = false;
            sprite.texture = en_id;
            GLogic::Enemy::signToGO[signos[k++]] = sprite;
        }
    }
    active_enemy = new GLogic::Enemy(GLogic::LIBRA, (Point){ 2,2 }, 30, &pointControl);
    
    //================ LOAD PROJECTILE
    
    
    int proj_id = png_texture_load("projectile_sprite.png", NULL, NULL);
    k=0;
    sprite_height = 1/2.0f;
    sprite_width = 1/2.0f;
    GLogic::SignElement elementos[] = {GLogic::AR, GLogic::AGUA, GLogic::TERRA, GLogic::FOGO};
    for (int i=0; i< 2; i++) {
        for (int j=0; j < 2; j++) {
            SpriteId sprite;
            sprite.lower_left.x = i * sprite_width;
            sprite.lower_left.y = j * sprite_height;
            sprite.upper_left.x = i * sprite_width;
            sprite.upper_left.y = (j+1) * sprite_height;
            sprite.lower_right.x = (i+1) * sprite_width;
            sprite.lower_right.y = j * sprite_height;
            sprite.upper_right.x = (i+1) * sprite_width;
            sprite.upper_right.y = (j+1) * sprite_height;
            sprite.hidden = false;
            sprite.texture = proj_id;
            GLogic::Projectile::signToProjectile[elementos[k++]] = sprite;
        }
    }
    
    
    ///======================= LOAD LIFEBAR
    lifebar_text = png_texture_load("lifebar_sprite.png", NULL, NULL);
    
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
        case 'x':
            if (active_enemy != NULL) {
                Point enemy_tile = calculate_losang_lower_left_point(active_enemy->getLocation(), TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
                enemy_tile.x += TILE_MAP_WIDTH/2.0f;
                enemy_tile.y += TILE_MAP_HEIGHT/2.0f;
                projectile = hero->fireToCoordinate(enemy_tile, signOfPoint[hero->getLocation()]);
            }
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
    glBindTexture(GL_TEXTURE_2D, sprite.texture);
    glBegin(GL_POLYGON);
    glTexCoord2f(sprite.lower_left.x,sprite.lower_left.y);
    glVertex2f(x, y + log_height/2.0f);
    glTexCoord2f(sprite.upper_left.x,sprite.upper_left.y);
    glVertex2f(x + log_width/2.0f, y + log_height);
    glTexCoord2f(sprite.upper_right.x,sprite.upper_right.y);
    glVertex2f(x + log_width, y + log_height/2.0f);
    glTexCoord2f(sprite.lower_right.x,sprite.lower_right.y);
    glVertex2f(x + log_width/2.0f, y);
    glEnd();
}

void draw_rectangle_tex(SpriteId sprite, int x, int y, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, sprite.texture);
    glBegin(GL_POLYGON);
    glTexCoord2f(sprite.lower_left.x,sprite.lower_left.y);
    glVertex2f(x, y);
    glTexCoord2f(sprite.upper_left.x,sprite.upper_left.y);
    glVertex2f(x, y + height);
    glTexCoord2f(sprite.upper_right.x,sprite.upper_right.y);
    glVertex2f(x + width, y + height);
    glTexCoord2f(sprite.lower_right.x,sprite.lower_right.y);
    glVertex2f(x + width, y);
    glEnd();
}

inline float area_of_triangle(Point a, Point b, Point c) {
    int xayb = a.x * b.y;
    int xbyc = b.x * c.y;
    int xcya = c.x * a.y;
    int xayc = a.x * c.y;
    int xcyb = c.x * b.y;
    int xbya = b.x * a.y;
    return abs(xayb + xbyc + xcya - xayc - xcyb - xbya)/2.0f;
}

//generic losang point colision detector
bool collide(int px, int py, int log_x, int log_y, int log_width, int log_height) {
    int leftx = log_x + log_width;
    int uppery = log_y - log_height;
    //test outter bounds
    if (px < log_x || py > log_y || leftx < px || uppery > py) {
        std::cerr << "testing collision with point outside bounds?\n";
        return false;
    }
    Point offending_point;
    offending_point.x = px;
    offending_point.y = py;
    //get losang triangle points
    Point log_a, log_b, log_c;
    log_b.x = log_x + log_width/2;
    log_c.x = log_x + log_width/2;
    log_b.y = py;
    log_c.y = uppery;
    log_a.y = py + log_height/2;
    //if it's on the right side of bound
    if (px > log_b.x) {
        std::cerr << "testing colision on a right-sized point?\n";
        log_a.x = leftx;
    } else {
        log_a.x = px;
    }
    int area_of_half_losang = area_of_triangle(log_a, log_b, log_c);
    int triangle_1_area = area_of_triangle(offending_point, log_b, log_c);
    int triangle_2_area = area_of_triangle(log_a, offending_point, log_c);
    int triangle_3_area = area_of_triangle(log_a, log_b, offending_point);
    return area_of_half_losang == (triangle_1_area + triangle_2_area + triangle_3_area);
}

void tick_all(int value) {
    if (hero != NULL) {
        hero->tick();
    }
    if (active_enemy != NULL) {
        active_enemy = active_enemy->tick();
    } else {
        active_enemy = new GLogic::Enemy(static_cast<GLogic::Sign>(rand() % 12), (Point){ (rand()%3) +1, (rand()%3) +1}, 30, &pointControl);
    }
    if (projectile != NULL) {
        projectile = projectile->tick();
    }
    if (active_enemy != NULL && projectile != NULL) {
        active_enemy = active_enemy->receiveDamage(projectile, calculate_row_collumn_of_point(projectile->getLocation(), TILE_MAP_WIDTH, TILE_MAP_HEIGHT));
        if (active_enemy == NULL) {
            delete projectile;
            projectile = NULL;
        }
    }
    
    if (active_enemy != NULL && hero != NULL) {
        Point heroLoc = hero->getPixelLocation();
        heroLoc.x += TILE_MAP_WIDTH/2.0f;
        Point hero_current_tile = calculate_row_collumn_of_point(heroLoc, TILE_MAP_WIDTH, TILE_MAP_WIDTH);
        Point enemy_current_tile = active_enemy->getLocation();
        if (hero_current_tile == enemy_current_tile) {
            //exit(0);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(60, tick_all, 0);
}

void mouse(int button, int state, int mx, int my)
{
    if (state == GLUT_DOWN) {
        return;
    }
    my -= VIEWPORT_Y/2;
    Point selected_tile;
    
    calculate_row_collumn_of_point(&selected_tile.x, &selected_tile.y, mx, my, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
    if (selected_tile.x >= TILE_MAP_SIZE || selected_tile.y >= TILE_MAP_SIZE || fix_ground_ids[selected_tile.x][selected_tile.y].hidden) {
        return;
    }
    
    Point heroLoc;
    calculate_losang_lower_left_point(&heroLoc.x, &heroLoc.y, selected_tile.x, selected_tile.y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
    heroLoc.x += TILE_MAP_WIDTH/4.0f;
    heroLoc.y += TILE_MAP_HEIGHT/3.0f;
    hero->walkTo(heroLoc);
    hero->setLocation(selected_tile);
    //==== NAO PRECISO DO TESTE DE AREA DO TRIANGULO , NAO SEI PQ??????
    //pega x e y de inicio de desenho do losango
    //int log_x, log_y;
    //calculate_losang_lower_left_point(&log_x, &log_y, collumn, row, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
   // if (collide(mx, my, log_x, log_y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT)) {
     //   std::cout << "it is at " << mx << " and " << my << " and I think it is at " << row << " " << collumn << "\n";
    //} else {
    //    std::cout << "it is at " << mx << " and " << my << " and I think it is at " << row << " " << collumn-1 << " FIXED\n";
    //}
    glutPostRedisplay();

}



void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    int x = 0;
    int y = 0;
    
    SpriteId sp_hold;
    sp_hold.texture = ground_id;
    for (int i = 0; i < TILE_MAP_SIZE; i++) {
        for (int j = (int) TILE_MAP_SIZE - 1; j >= 0; j--) {
            calculate_losang_lower_left_point(&x, &y, i, j, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            
            glColor3ub(255, 255, 255);
            draw_losang_tex(sp_hold, x, y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            
            if (!fix_ground_ids[i][j].hidden) {
                draw_losang_tex(fix_ground_ids[i][j], x, y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            }
            
            
            //DEBUG- LINE AND ROW COL
            glColor3ub(0, 0, 0);
            draw_losang_line(x, y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
            
            glRasterPos2f(x+TILE_MAP_WIDTH/2,y+TILE_MAP_HEIGHT/2);
            
            char* pontos = (char*)calloc(5, sizeof(char));
            sprintf(pontos, "%d,%d", i, j);
            int charSize = strlen(pontos);
            for (int i = 0; i< charSize; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)pontos[i]);
            }
            free(pontos);
        }
    }
    
    /* testing mouse click
    glColor4ub(0xFF, 0, 0, 0x20);
    calculate_losang_lower_left_point(&x, &y, clicked.x, clicked.y, TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
    glBegin(GL_POLYGON);
    glVertex2f(x, y + TILE_MAP_HEIGHT/2.0f);
    glVertex2f(x + TILE_MAP_WIDTH/2.0f, y + TILE_MAP_HEIGHT);
    glVertex2f(x + TILE_MAP_WIDTH, y + TILE_MAP_HEIGHT/2.0f);
    glVertex2f(x + TILE_MAP_WIDTH/2.0f, y);
    glEnd();
     */
    
    glColor3ub(255, 255, 255);
    SpriteId* hero_now = hero->getGameObject()->getCurrentFrame();
    int hero_width = (int) (TILE_MAP_HEIGHT*7.0f/8.0f);
    draw_rectangle_tex(*hero_now, hero->getPixelLocation().x, hero->getPixelLocation().y, TILE_MAP_HEIGHT, hero_width);
    
    if (active_enemy != NULL) {
        Point enemy_source = calculate_losang_lower_left_point(active_enemy->getLocation(), TILE_MAP_WIDTH, TILE_MAP_HEIGHT);
        enemy_source.x += TILE_MAP_WIDTH/4.0f;
        enemy_source.y += TILE_MAP_HEIGHT/3.0f;
        draw_rectangle_tex(active_enemy->getSprite(), enemy_source.x, enemy_source.y, TILE_MAP_HEIGHT, TILE_MAP_HEIGHT);
        
        //draw the lifebar
        float hp_percentage = active_enemy->getCurrentHp();
        glBindTexture(GL_TEXTURE_2D, lifebar_text);
        
        enemy_source.x += 30;
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f,0.5f);
        glVertex2f(enemy_source.x, enemy_source.y);
        glTexCoord2f(0.0f,1.0f);
        glVertex2f(enemy_source.x, enemy_source.y + 10);
        glTexCoord2f(hp_percentage,1.0f);
        glVertex2f(enemy_source.x + 40 * hp_percentage, enemy_source.y + 10);
        glTexCoord2f(hp_percentage,0.5f);
        glVertex2f(enemy_source.x + 40 * hp_percentage, enemy_source.y);
        glEnd();
        if (hp_percentage < 1.0f) {
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0f - hp_percentage,0.0f);
            glVertex2f(enemy_source.x + 40 * hp_percentage, enemy_source.y);
            glTexCoord2f(1.0f - hp_percentage,0.5f);
            glVertex2f(enemy_source.x + 40 * hp_percentage, enemy_source.y + 10);
            glTexCoord2f(1.0f,0.5f);
            glVertex2f(enemy_source.x + 40, enemy_source.y + 10);
            glTexCoord2f(1.0f,0.0f);
            glVertex2f(enemy_source.x + 40, enemy_source.y);
            glEnd();
        }
        
    }
    
    if (projectile != NULL) {
        Point proj_loc = projectile->getLocation();
        draw_rectangle_tex(projectile->getSprite(), proj_loc.x, proj_loc.y, 30, 30);
    }
    
    
    glColor4ub(0, 0, 0, 255);
    glRasterPos2i(0,200);
    sprintf(pontos, "%d pontos\n", pointControl.getPoints());
    int charSize = strlen(pontos);
    for (int i = 0; i< charSize; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)pontos[i]);
    }
    
    
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    tick_all(0);
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
