#include "draw.h"


int drawBackground(Background *background) {
    drawSprite(background->sprite, background->x, background->y);
    return 0;
}
