#pragma once
 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <lcom/lcf.h>
#include "objects.h"
#include "draw.h"

#include "dvcs/graphics/vbe.h"
#include "dvcs/keyboard/kbc.h"
#include "dvcs/timer/pit.h"
#include "dvcs/mouse/ps2.h"

typedef enum {
    MENU,   
    GAME,
    LOST,
    WON,
    EXIT
} State;

int run();
int draw_init();
int draw_frame();
int move_ball();
int prepare_video();
int disable_video();
int prepare_keyboard();
int disable_keyboard();
void handle_keyboard();
int prepare_timer();
int disable_timer();
int prepare_mouse();
int disable_mouse();
int prepare_screens();
int prepare_objects();
int projectileLaunch();
int move_projectile();
int move_bricks();
int move_marker();
