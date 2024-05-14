#pragma once
 
#include <stdint.h>

#include <lcom/lcf.h>
#include "../objs/ball/ball.h"
#include "../objs/paddle/paddle.h"
#include "../objs/brick/brick.h"

#include "../../dvcs/graphics/vbe.h"
#include "../../dvcs/keyboard/kbc.h"

int run();
int prepare_video();
int disable_video();
int prepare_keyboard();
int disable_keyboard();
int prepare_objects();
