#include "objects.h"


// Function to initialize a background
void initBackground(Background* background, int x, int y, Sprite *background_sprite) {
    background->x = x;
    background->y = y;
    background->sprite = background_sprite;
}
// Function to initialize a ball
void initBall(Ball* ball, int x, int y, int contact, Sprite *ball_sprite) {
    ball->x = x;
    ball->y = y;
    ball->contact = contact;
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

// Function to move the paddle left
void movePaddleLeft(Paddle* paddle, int distance) {
    paddle->x -= distance;
}

// Function to move the paddle right
void movePaddleRight(Paddle* paddle, int distance) {
    paddle->x += distance;
}




