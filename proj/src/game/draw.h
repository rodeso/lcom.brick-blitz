#ifndef _LCOM_DRAW_H_
#define _LCOM_DRAW_H_


#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "objects.h"

int drawBackground(Background *background);

int drawPaddle(Paddle *paddle);

int drawBrick(Brick *brick);

int drawBall(Ball *ball);

int drawProjectile(Projectile *projectile);

#endif
