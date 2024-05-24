#ifndef _LCOM_SPRITES_H_
#define _LCOM_SPRITES_H_

#include "xpm/background.xpm"
#include "xpm/ball.xpm"
#include "xpm/brick.xpm"
#include "xpm/paddle.xpm"

#include "sprite.h"

int drawSprite(Sprite *sprite, int x, int y);

void load_sprites();

void destroy_sprites();

#endif

