#pragma once
 
#include <stdint.h>

#include <lcom/lcf.h>
#include "objects.h"

#include "vbe.h"
#include "kbc.h"
#include "pit.h"

int run();
int prepare_video();
int disable_video();
int prepare_keyboard();
int disable_keyboard();
int prepare_objects();
