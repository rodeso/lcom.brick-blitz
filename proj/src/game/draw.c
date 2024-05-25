#include "draw.h"


int drawBackground(Background *background) {
    if(drawSprite(background->sprite, background->x, background->y)!=0) {return 1;}
    return 0;
}

int drawPaddle(Paddle *paddle) {
    if(drawSprite(paddle->sprite, paddle->x, paddle->y)!=0) {return 1;}
    return 0;
}

int drawBrick(Brick *brick) {
    if(drawSprite(brick->sprite, brick->x, brick->y)!=0) {return 1;}
    return 0;
}

int drawBall(Ball *ball) {
    if(drawSprite(ball->sprite, ball->x, ball->y)!=0) {return 1;}
    return 0;
}

int drawProjectile(Projectile *projectile) {
    if(drawSprite(projectile->sprite, projectile->x, projectile->y)!=0) {return 1;}
    return 0;
}
