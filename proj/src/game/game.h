#pragma once
 
#include <stdint.h>

#include <lcom/lcf.h>
#include "objects.h"
#include "draw.h"
#include "handler.h"

#include "dvcs/graphics/vbe.h"
#include "dvcs/keyboard/kbc.h"
#include "dvcs/timer/pit.h"



int run();
int draw_frame();
int prepare_video();
int disable_video();
int prepare_keyboard();
int disable_keyboard();
int prepare_timer();
int disable_timer();
int prepare_objects();
