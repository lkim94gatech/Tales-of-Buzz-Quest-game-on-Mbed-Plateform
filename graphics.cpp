// ============================================
// The graphics class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include <cstdint>
#include "graphics.h"
#include "globals.h"
#include <ctime>




///////////////////////////////////////////
// Drawing Images based on Characters
///////////////////////////////////////////

//Additional color definitions
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}


///////////////////////////////////////////
//Simple drawing of objects using uLCD methods
///////////////////////////////////////////

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_player(int u, int v, int key, bool visible)
{
    if (!visible) {
        draw_banyan(u, v);
        return;
    }
    if (key)
    {
        uLCD.filled_rectangle(u, v, u+11, v+11, YELLOW);
    }
    else
    {
        uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    }
}


void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_door(int u, int v)
{
    draw_nothing(u,v);
    uLCD.line(u, v+6, u+11, v+6, 0xFFFF00);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

///////////////////////////////////////////
//Sprite drawing of objects using draw_img function
///////////////////////////////////////////

void draw_plant(int u, int v)
{
    const char* img = 
        "           "
        " GGGGGGGG  "
        " GGGGGGGGG "
        "GGGGGGGGGGG"
        "GGGGGGGGGGG"
        " GGGGGGGG  "
        "    DD     "
        "    DD     "
        "    DD     "
        "   DDDDD   "
        "  D  D  D  ";
    draw_img(u, v, img);
}


void draw_npc(int u, int v)
{
    const char* img = 
        "     R     "
        "    RRR    "
        "   RRRRR   "
        "  RRRRRRR  "
        " RRRRYRRRR "
        "RRRRYYYRRRR"
        " RRRRYRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "    RRR    "
        "     R     ";
    draw_img(u, v, img);
}

void draw_stairs(int u, int v)
{
    const char* img =
        "        333"
        "        353"
        "      33333"
        "      35553"
        "    3333333"
        "    3555553"
        "  333333333"
        "  355555553"
        "33333333333"
        "35555555553"
        "33333333333";
    draw_img(u, v, img);
}



////////////////////////////////////////////
//Examples of Piskel sprite C array export
////////////////////////////////////////////

void draw_buzz(int u, int v)
{

int new_piskel_data[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xff0000ff, 0xff606060, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff0000ff, 0xffffffff, 0xff0000ff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffff00, 0xffffff00, 0xffffff00, 0xff0000ff, 0xff0000ff, 0xff606060, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff137bff, 0xffffffff, 0x00000000, 0x00000000, 
0xff137bff, 0x00000000, 0xff137bff, 0xff58110c, 0xff58110c, 0xff58110c, 0xffffff00, 0xff58110c, 0xff137bff, 0x00000000, 0x00000000, 
0x00000000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0xffffff00, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xffffff00, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_fire(int u, int v) {
int fire_sprite[121] = {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 0x00000000, 
0x00000000, 0x00000000, 0xff0092ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 0x00000000, 
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0000ff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0092ff, 0xff0092ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 0xff0092ff, 0xff0092ff, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

    uLCD.BLIT(u, v, 11, 11, fire_sprite);
}

void draw_earth(int u, int v)
{

int earth_sprite[121] = {
0xff004b96, 0xff004b96, 0xff01274d, 0xff01274d, 0xff01274d, 0xff00ff00, 0xff01274d, 0xff01274d, 0xff004b96, 0xff004b96, 0xff004b96, 
0xff004b96, 0xff004b96, 0xff004b96, 0xff00ff00, 0xff00ff00, 0xff01274d, 0xff00ff00, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 
0xff004b96, 0xff00ff00, 0xff00ff00, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff01274d, 0xff00ff00, 0xff004b96, 0xff01274d, 
0xff004b96, 0xff01274d, 0xff01274d, 0xff01274d, 0xff004b96, 0xff004b96, 0xff004b96, 0xff01274d, 0xff00ff00, 0xff004b96, 0xff00ff00, 
0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff00ff00, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 
0xff004b96, 0xff00ff00, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff01274d, 0xff01274d, 0xff01274d, 0xff004b96, 0xff004b96, 
0xff004b96, 0xff01274d, 0xff004b96, 0xff00ff00, 0xff01274d, 0xff004b96, 0xff00ff00, 0xff004b96, 0xff00ff00, 0xff004b96, 0xff004b96, 
0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff01274d, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff00ff00, 
0xff004b96, 0xff00ff00, 0xff01274d, 0xff004b96, 0xff00ff00, 0xff004b96, 0xff01274d, 0xff004b96, 0xff004b96, 0xff004b96, 0xff01274d, 
0xff00ff00, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff00ff00, 0xff004b96, 0xff01274d, 0xff01274d, 0xff004b96, 
0xff01274d, 0xff01274d, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff00ff00, 0xff01274d, 0xff004b96
};

   uLCD.BLIT(u,v, 11,11, earth_sprite);
        
}

void draw_water(int u, int v)
{

int water_sprite[121] = {
0xffffd200, 0xffff1300, 0xffff1300, 0xffffd200, 0xffffd200, 0xffffd200, 0xffff6d00, 0xffffd200, 0xfffdfdfd, 0xffffd200, 0xffffa500, 
0xffffa500, 0xffffa500, 0xfffdfdfd, 0xffff1300, 0xffffa500, 0xffffd200, 0xffffd200, 0xffff6d00, 0xffffa500, 0xffffa500, 0xffffd200, 
0xffff6d00, 0xffff6d00, 0xffff6d00, 0xfffdfdfd, 0xfffdfdfd, 0xffffa500, 0xffffd200, 0xffff1300, 0xfffdfdfd, 0xfffdfdfd, 0xffffd200, 
0xffffd200, 0xffff1300, 0xffff1300, 0xffff6d00, 0xffff6d00, 0xfffdfdfd, 0xffffa500, 0xffffa500, 0xffffd200, 0xffff1300, 0xffffd200, 
0xfffdfdfd, 0xfffdfdfd, 0xffff1300, 0xffff1300, 0xffff6d00, 0xffffd200, 0xfffdfdfd, 0xfffdfdfd, 0xffffa500, 0xffff1300, 0xffff1300, 
0xffffd200, 0xffff1300, 0xfffdfdfd, 0xffffa500, 0xffffa500, 0xffffa500, 0xffff1300, 0xffffa500, 0xfffdfdfd, 0xfffdfdfd, 0xffffd200, 
0xffffd200, 0xffffd200, 0xffff6d00, 0xffff6d00, 0xffffa500, 0xffffa500, 0xffffa500, 0xffff1300, 0xffff6d00, 0xfffdfdfd, 0xffffd200, 
0xffffd200, 0xffff1300, 0xffff1300, 0xffff1300, 0xffffa500, 0xffff6d00, 0xffff6d00, 0xffffd200, 0xffffa500, 0xffffd200, 0xffffd200, 
0xffffa500, 0xffffa500, 0xfffdfdfd, 0xffffa500, 0xffffa500, 0xffffd200, 0xffffa500, 0xffffa500, 0xffffa500, 0xfffdfdfd, 0xffff1300, 
0xffffd200, 0xffff6d00, 0xfffdfdfd, 0xffffa500, 0xffff1300, 0xfffdfdfd, 0xfffdfdfd, 0xffff1300, 0xffff1300, 0xffff1300, 0xffff1300, 
0xffff1300, 0xffffa500, 0xffffa500, 0xffffd200, 0xffffd200, 0xffff6d00, 0xffff6d00, 0xffff6d00, 0xffffd200, 0xffff6d00, 0xffffd200
};

   uLCD.BLIT(u,v, 11,11, water_sprite);
        
}

///////////////////////////////////////////
//Other sprites
///////////////////////////////////////////

void draw_cave1(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave2(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave3(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333000"
        "33333333000"
        "33333333000";
    draw_img(u, v, img);
}
void draw_cave4(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}


void draw_mud(int u, int v)
{
   const char* img = 
        "DDDDDDDDDDD"
        "DDD3333DD3D"
        "D33D33D33DD"
        "D3DDD33D33D"
        "DD333D333DD"
        "D33D33DDDD"
        "DDD333D333D"
        "DD3DDD3DD3D"
        "D3D333D33DD"
        "DDDDD33DDDD"
        "DDDDDDDDDDD";
    draw_img(u, v, img);
}

void draw_boss(int u, int v) {
int boss_sprite[121] = {
0xff000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff000000, 
0xff0000ff, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff000000, 0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 0xff000000, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffff2900, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffff2900, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0x00000000, 0x00000000, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff000000, 0xff0000ff, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000
};

    uLCD.BLIT(u, v, 11, 11, boss_sprite);
}

void draw_slain_enemy(int u, int v) {
int slain_sprite[121] = {
0xff0000ff, 0x00000000, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0x00000000, 0xff0000ff, 
0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0x00000000, 
0x00000000, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0xff000000, 0xfff9f9f9, 0xff000000, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0x00000000, 
0x00000000, 0xfff9f9f9, 0xff000000, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0xff000000, 0xfff9f9f9, 0x00000000, 
0x00000000, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0x00000000, 
0x00000000, 0xfff9f9f9, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xfff9f9f9, 0x00000000, 
0x00000000, 0x00000000, 0xfff9f9f9, 0xff0000ff, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xff0000ff, 0xfff9f9f9, 0x00000000, 0x00000000, 
0x00000000, 0xff0000ff, 0xff0000ff, 0xfff9f9f9, 0xff000000, 0xff000000, 0xff000000, 0xfff9f9f9, 0xff0000ff, 0xff0000ff, 0x00000000, 
0x00000000, 0xff0000ff, 0x00000000, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0x00000000, 0xff0000ff, 0x00000000, 
0xff0000ff, 0x00000000, 0x00000000, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0xfff9f9f9, 0x00000000, 0x00000000, 0xff0000ff
};

    uLCD.BLIT(u, v, 11, 11, slain_sprite);
}

void draw_badguy1(int u, int v) {
int badguy1_sprite[121] = {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 0x00000000, 0x00000000, 0x00000000, 
0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 0x00000000, 0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 
0xfff20019, 0xffffffff, 0x00000000, 0x00000000, 0xfff20019, 0xfff20019, 0xfff20019, 0x00000000, 0x00000000, 0xffffffff, 0xfff20019, 
0xfff20019, 0xffffffff, 0xfff20019, 0x00000000, 0xff0000ff, 0xfff20019, 0xff0000ff, 0x00000000, 0xfff20019, 0xffffffff, 0xfff20019, 
0xffffffff, 0xffffffff, 0xfff20019, 0xffffffff, 0xfff20019, 0xfff20019, 0xfff20019, 0xffffffff, 0xfff20019, 0xffffffff, 0xffffffff, 
0xfff20019, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xfff20019, 
0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 
0xfff20019, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff20019, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

    uLCD.BLIT(u, v, 11, 11, badguy1_sprite);
}

void draw_badguy2(int u, int v) {
int badguy2_sprite[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xff000000, 0x00000000, 0x00000000, 
0x00000000, 0xff000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xff000000, 0x00000000, 
0xff000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xff000000, 
0xff000000, 0xffffffff, 0xff000000, 0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000, 0xff000000, 0xffffffff, 0xff000000, 
0xff000000, 0xffffffff, 0xffffffff, 0xfff2835e, 0xffffffff, 0xffffffff, 0xffffffff, 0xfff2835e, 0xffffffff, 0xffffffff, 0xff000000, 
0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 
0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 
0x00000000, 0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 0x00000000, 
0x00000000, 0x00000000, 0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0x00000000, 0x00000000, 0x00000000
};

    uLCD.BLIT(u, v, 11, 11, badguy2_sprite);
}

void draw_chest(int u, int v) {
    int chest_sprite[121] = {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 0xff00f6f2, 0xff00f6f2, 0xff00f6f2, 0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 0xff00f6f2, 0xff00f6f2, 0xff00f6f2, 0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff004b96, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
};

    uLCD.BLIT(u, v, 11, 11, chest_sprite);
}

void draw_banyan(int u, int v) {
    int banyan_sprite[121] = {
0xff007800, 0xff007800, 0xff007800, 0xff03c703, 0xff03c703, 0xff03c703, 0xff03c703, 0xff03c703, 0xff007800, 0xff007800, 0xff03c703, 
0xff007800, 0xff03c703, 0xff02a302, 0xff02a302, 0xff0000ff, 0xff007800, 0xff007800, 0xff03c703, 0xff03c703, 0xff007800, 0xff0000ff, 
0xff02a302, 0xff0000ff, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 
0xff007800, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff03c703, 0xff03c703, 0xff03c703, 0xff03c703, 0xff02a302, 
0xff007800, 0xff007800, 0xff02a302, 0xff02a302, 0xff03c703, 0xff02a302, 0xff02a302, 0xff007800, 0xff007800, 0xff02a302, 0xff007800, 
0xff007800, 0xff02a302, 0xff02a302, 0xff007800, 0xff03c703, 0xff02a302, 0xff02a302, 0xff02a302, 0xff03c703, 0xff007800, 0xff03c703, 
0xff007800, 0xff0000ff, 0xff02a302, 0xff007800, 0xff03c703, 0xff02a302, 0xff0000ff, 0xff02a302, 0xff007800, 0xff03c703, 0xff0000ff, 
0xff02a302, 0xff007800, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 0xff02a302, 0xff02a302, 0xff03c703, 0xff03c703, 0xff02a302, 
0xff02a302, 0xff02a302, 0xff03c703, 0xff02a302, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 
0xff02a302, 0xff02a302, 0xff03c703, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 0xff007800, 0xff0000ff, 0xff02a302, 0xff007800, 
0xff007800, 0xff02a302, 0xff03c703, 0xff0000ff, 0xff02a302, 0xff007800, 0xff02a302, 0xff02a302, 0xff02a302, 0xff007800, 0xff007800
};
    uLCD.BLIT(u, v, 11, 11, banyan_sprite);
}

void draw_christmas_tree(int u, int v) {
    // Define the sprite frames for the Christmas tree
    int christmas_tree_frames[4][121] = {
      {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff0000ff, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff0000ff, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff0000ff, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 
0xff007800, 0xff007800, 0xff0000ff, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 
0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff0000ff, 0xff007800, 0xff007800, 0xff007800, 0xff0000ff, 0xff007800, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xffff8f00, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffff8f00, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xffff8f00, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 
0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xffff8f00, 0xff007800, 0xff007800, 0xff007800, 
0xffff8f00, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00fff0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff00fff0, 0xff007800, 0xff00fff0, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0xff007800, 0xff00fff0, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 
0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff00fff0, 0xff007800, 0xff007800, 0xff00fff0, 0xff007800, 
0xff007800, 0xff00fff0, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff0092ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0xff007800, 0xff0092ff, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 0x00000000, 
0x00000000, 0xff007800, 0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0x00000000, 
0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0xff007800, 0xff0092ff, 0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0xff007800, 
0xff007800, 0xff007800, 0xff007800, 0xff0092ff, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff007800, 0xff0092ff, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff004385, 0xff004385, 0xff004385, 0x00000000, 0x00000000, 0x00000000, 0x00000000
}
    };

    // Animation loop - cycles through the frames
    for (int frame = 0; frame < 4; ++frame) {
        // Draw the current frame
        uLCD.BLIT(u, v, 11, 11, christmas_tree_frames[frame]);
        // Wait for a short duration to display this frame
        wait(0.5); // Adjust the timing as necessary
    }
}