#include <stdio.h>

// Define the Paddle class
typedef struct {
    int x; // X-coordinate of the paddle
    int y; // Y-coordinate of the paddle
    int width;
    int height;
} Paddle;

// Function to initialize the paddle
void initPaddle(Paddle* paddle, int x, int y, int width, int height) {
    paddle->x = x;
    paddle->y = y;
}

// Function to move the paddle left
void movePaddleLeft(Paddle* paddle, int distance) {
    paddle->x -= distance;
}

// Function to move the paddle right
void movePaddleRight(Paddle* paddle, int distance) {
    paddle->x += distance;
}

// Function to draw the paddle
void drawPaddle(const Paddle* paddle) {
    printf("Paddle: x=%d, y=%d, width=%d, height=%d\n", paddle->x, paddle->y, paddle->width, paddle->height);
}
