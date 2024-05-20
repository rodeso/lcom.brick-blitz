#include <stdbool.h>

typedef struct {
    int x;      // x-coordinate of the brick
    int y;      // y-coordinate of the brick
    bool contact; // flag to indicate if the brick is destroyed
} Ball;

// Function to initialize a brick
void initBall(Ball* ball, int x, int y, bool contact) {
    ball->x = x;
    ball->y = y;
    ball->contact = contact;

}


