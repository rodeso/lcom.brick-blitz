#include "manager.h"


Sprite *ball_sprite;
Sprite *brick_sprite;
Sprite *paddle_sprite;



int drawSprite(Sprite *sprite, int xPos, int yPos) {
    printf("drawSprite started\n");
    uint32_t current_color;
    printf("current_color started\n");
    printf("spritex: %d\n", sprite->width);
    printf("spritey: %d\n", sprite->height);

    for (int i = 0 ; i < sprite->height; i++) {
      for (int j = 0 ; j < sprite->width; j++) {
          printf("i=%d, j=%d ->sprite map started", i, j);
          current_color = sprite->map[j + i*sprite->width];
          printf("i=%d, j=%d ->sprite map ended", i, j);
          if (current_color == 0x505050) {printf("its doing transparent");continue;}
          printf("i=%d, j=%d ->transparent ended", i, j);
          if (vbe_draw_pixel(xPos + j, yPos + i, current_color)) return 1;
      }
    }
    printf("drawSprite ended\n");
    return 0; 
}
