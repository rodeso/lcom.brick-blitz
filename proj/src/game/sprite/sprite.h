#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include <lcom/lcf.h>
#include "dvcs/graphics/vbe.h"
#include "xpm/background.xpm"
#include "xpm/menu.xpm"
#include "xpm/lost.xpm"
#include "xpm/won.xpm"
#include "xpm/ball.xpm"
#include "xpm/ball2.xpm"
#include "xpm/brick.xpm"
#include "xpm/paddle.xpm"
#include "xpm/missile.xpm"
#include "xpm/missileIcon.xpm"
#include "xpm/life.xpm"


typedef struct {
    uint16_t height;
    uint16_t width;
    uint32_t *map;
} Sprite; 

Sprite *create_sprite(xpm_map_t pic);
void destroy_sprite(Sprite *sp);
int drawSprite(Sprite *sprite, int x, int y);

#endif
