#include <stdbool.h>

typedef struct {
    int x;      // x-coordinate of the brick
    int y;      // y-coordinate of the brick
    bool destroyed; // flag to indicate if the brick is destroyed
} Brick;

// Function to initialize a brick
void initBrick(Brick* brick, int x, int y, int width, int height) {
    brick->x = x;
    brick->y = y;
    brick->destroyed = false;
}

// Function