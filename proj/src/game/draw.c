#include "draw.h"


int drawBackground(Background *background) {
    printf("draw_background started\n");
    drawSprite(background->sprite, background->x, background->y);
    printf("draw_background ended\n");
    return 0;
}
