#ifndef _LCOM_DRAW_H_
#define _LCOM_DRAW_H_


#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "sprite/manager.h"
#include "objects.h"

int drawBackground(Background *background);

void drawBall(Ball *ball);

#endif
