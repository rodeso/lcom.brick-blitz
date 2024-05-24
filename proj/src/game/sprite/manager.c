#include "manager.h"


Sprite *ball_sprite;
Sprite *brick_sprite;
Sprite *paddle_sprite;



int drawSprite(Sprite *sprite, int xPos, int yPos) {
    uint32_t current_color;

    for (int i = 0 ; i < sprite->height; i++) {
      for (int j = 0 ; j < sprite->width; j++) {
          current_color = sprite->map[j + i*sprite->width];
          if (current_color == 0x505050) {printf("its doing transparent");continue;}
          if (vbe_draw_pixel(xPos + j, yPos + i, current_color)) return 1;
      }
    }
    return 0; 
}
