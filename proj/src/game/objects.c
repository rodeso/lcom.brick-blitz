#include "objects.h"


// Function to initialize a background
void initBackground(Background* background, int x, int y, Sprite *background_sprite) {
    background->x = x;
    background->y = y;
    background->sprite = background_sprite;
}
// Function to initialize a ball
void initBall(Ball* ball, int x, int y, Sprite *ball_sprite) {
    ball->x = x;
    ball->y = y;
    ball->base = true;
    ball->dx = 4;
    ball->dy = -4;
    ball->oldx = 0;
    ball->oldy = 0;
    ball->sprite = ball_sprite;

}
// Function to initialize a brick
void initBrick(Brick* brick, int x, int y, Sprite *brick_sprite) {
    brick->x = x;
    brick->y = y;
    brick->destroyed = false;
    brick->sprite = brick_sprite;
}
// Function to initialize the paddle
void initPaddle(Paddle* paddle, int x, int y, Sprite *paddle_sprite) {
    paddle->x = x;
    paddle->y = y;
    paddle->sprite = paddle_sprite;
}





