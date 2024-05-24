#ifndef _LCOM_OBJECTS_H_
#define _LCOM_OBJECTS_H_

#include <stdio.h>
#include "sprite/manager.h"

typedef struct {
    int x;      // x-coordinate of the background
    int y;      // y-coordinate of the background
    Sprite *sprite;
} Background;

typedef struct {
    int x;      // x-coordinate of the brick
    int y;      // y-coordinate of the brick
    int contact; // flag to indicate if the brick is destroyed
    Sprite *sprite;
} Ball;

typedef struct {
    int x;      // x-coordinate of the brick
    int y;      // y-coordinate of the brick
    int width;
    int height;
    int destroyed; // flag to indicate if the brick is destroyed
    Sprite *sprite;
} Brick;

typedef struct {
    int x; // X-coordinate of the paddle
    int y; // Y-coordinate of the paddle
    int width;
    int height;
    Sprite *sprite;
} Paddle;


void initBackground(Background* background, int x, int y, Sprite *sprite);
void initBall(Ball* ball, int x, int y, int contact, Sprite *sprite);
void initBrick(Brick* brick, int x, int y, int width, int height, int destroyed, Sprite *sprite);
void initPaddle(Paddle* paddle, int x, int y, int width, int height, Sprite *sprite);
void movePaddleLeft(Paddle* paddle, int distance);
void movePaddleRight(Paddle* paddle, int distance);

#endif