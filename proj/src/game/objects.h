#ifndef _LCOM_OBJECTS_H_
#define _LCOM_OBJECTS_H_

#include <stdio.h>
#include "sprite/sprite.h"

typedef struct {
    int x;      // x-coordinate of the background
    int y;      // y-coordinate of the background
    Sprite *sprite;
} Background;

typedef struct {
    int x;      // x-coordinate of the ball
    int y;      // y-coordinate of the ball
    int oldx;   // x-coordinate of the ball in the previous frame
    int oldy;   // y-coordinate of the ball in the previous frame
    int dx;     // x-speed of the ball
    int dy;     // y-speed of the ball
    int base;   // flag to indicate if the brick is the base
    Sprite *sprite;
} Ball;

typedef struct {
    int x;      // x-coordinate of the brick
    int y;      // y-coordinate of the brick
    int destroyed; // flag to indicate if the brick is destroyed
    Sprite *sprite;
} Brick;

typedef struct {
    int x; // X-coordinate of the paddle
    int y; // Y-coordinate of the paddle
    int oldx; // old X-coordinate of the paddle
    Sprite *sprite;
} Paddle;

typedef struct {
    int x; // X-coordinate of the powerup
    int y; // Y-coordinate of the powerup
    int oldy; // old Y-coordinate of the powerup
    Sprite *sprite;
} Projectile;


void initBackground(Background* background, int x, int y, Sprite *sprite);
void initBall(Ball* ball, int x, int y, Sprite *sprite);
void initBrick(Brick* brick, int x, int y, Sprite *sprite);
void initPaddle(Paddle* paddle, int x, int y, Sprite *sprite);
void initProjectile(Projectile* projectile, Paddle paddle, Sprite *sprite);

#endif
