#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include <lcom/lcf.h>
#include "dvcs/graphics/vbe.h"

typedef struct {
    uint16_t height;
    uint16_t width;
    uint32_t *map;
} Sprite; 

Sprite *create_sprite(xpm_map_t pic);
void destroy_sprite(Sprite *sp);
#endif
