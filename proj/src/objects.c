#include "objects.h"


// Function to initialize a brick
void initBall(Ball* ball, int x, int y, int contact) {
    ball->x = x;
    ball->y = y;
    ball->contact = contact;

}
// Function to initialize a brick
void initBrick(Brick* brick, int x, int y, int width, int height, int destroyed) {
    brick->x = x;
    brick->y = y;
    brick->width = width;
    brick->height = height;
    brick->destroyed = destroyed;
}
// Function to initialize the paddle
void initPaddle(Paddle* paddle, int x, int y, int width, int height) {
    paddle->x = x;
    paddle->y = y;
    paddle->width = width;
    paddle->height = height;
}

// Function to move the paddle left
void movePaddleLeft(Paddle* paddle, int distance) {
    paddle->x -= distance;
}

// Function to move the paddle right
void movePaddleRight(Paddle* paddle, int distance) {
    paddle->x += distance;
    printf("paddle moved");
}

// Function to draw the paddle
void drawPaddle(const Paddle* paddle) {
    create_sprite((char**) paddle_xpm);
}

