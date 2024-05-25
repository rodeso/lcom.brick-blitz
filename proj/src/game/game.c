#include "game/game.h"

extern GameState gameState;
uint8_t bit_no_keyboard = 0;
uint8_t bit_no_timer = 0;
Background background;
Background menu;
Background lost;
Background won;
Paddle paddle;
Brick bricks[72];
Ball ball;
extern vbe_mode_info_t vmi_p;
Sprite *background_sprite;
Sprite *menu_sprite;
Sprite *lost_sprite;
Sprite *won_sprite;
Sprite *ball_sprite;
Sprite *brick_sprite;
Sprite *paddle_sprite;
int lives = 3;
int destroyed = 0;
//----------------video--------------------------------------------------------------------------------------------------------------------


int (prepare_video)() {
    
    if(vbe_mapping_videoRAM_to_address_space(0x115)!=0) {return 1;}

    if(vbe_set_display_mode(0x115)!=0) {return 1;}

    printf("Initializing video...");

    return 0;
}

int (disable_video)() {
    if (vg_exit()) return 1;
    return 0;
}


//----------------keyboard--------------------------------------------------------------------------------------------------------------------


int (prepare_keyboard)() {
    if(keyboard_subscribe_int(&bit_no_keyboard)!=0) {return 1;}
    return 0;
}

int (disable_keyboard)() {
    if (keyboard_unsubscribe_int()) return 1;
    return 0;
}


//----------------timer--------------------------------------------------------------------------------------------------------------------


int (prepare_timer)() {
    if(timer_subscribe_int(&bit_no_timer)!=0) {return 1;}
    return 0;
}
int (disable_timer)() {
    if(timer_unsubscribe_int()) return 1;
    return 0;
}


//----------------objects--------------------------------------------------------------------------------------------------------------------


int (prepare_objects)() {

    background_sprite = create_sprite((xpm_map_t)background_xpm);
    menu_sprite = create_sprite((xpm_map_t)menu_xpm);
    lost_sprite = create_sprite((xpm_map_t)lost_xpm);
    won_sprite = create_sprite((xpm_map_t)won_xpm);
    ball_sprite = create_sprite((xpm_map_t)ball_xpm);
    paddle_sprite = create_sprite((xpm_map_t)paddle_xpm);
    brick_sprite = create_sprite((xpm_map_t)brick_xpm);


    initBackground(&background, 0, 0, background_sprite);
    initBackground(&menu,0,0,menu_sprite);
    initBackground(&lost,0,0,lost_sprite);
    initBackground(&won,0,0,won_sprite);
    initPaddle(&paddle, (background_sprite->width/2)-(paddle_sprite->width/2), 530, paddle_sprite);
    for (int i = 0; i < 72; i++) {
      initBrick(&bricks[i], BIT(4)+((i%12)*BIT(6)), BIT(4)+(int)(i/12)*BIT(5), brick_sprite);
    }
    initBall(&ball, (background_sprite->width/2)-(ball_sprite->width/2), 530-ball_sprite->height, ball_sprite);


    return 0;
}


//----------------run--------------------------------------------------------------------------------------------------------------------
int (draw_frame)() {
  if (gameState == GAME) {
    if(drawBackground(&background)) {return 1;}
    if(drawPaddle(&paddle)) {return 1;}
    for (int i=0; i<72; i++) {
      if (!bricks[i].destroyed) {
        if(drawBrick(&bricks[i])){return 1;}
      }
    }
    if(drawBall(&ball)) {return 1;}
  }
  else if (gameState == MENU) {
    if(drawBackground(&menu)) {return 1;}
  }
  else if (gameState == LOST) {
    if(drawBackground(&lost)) {return 1;}
  }
  else if (gameState == WON) {
    if(drawBackground(&won)) {return 1;}
  }
    return 0;
}
int move_ball() {
    ball.oldx = ball.x;
    ball.oldy = ball.y;

    if (ball.base) {
      ball.x = paddle.x + (paddle.sprite->width/2) - (ball.sprite->width/2);
      ball.y = paddle.y - ball.sprite->height;
      ball.dy = -BIT(2);
    } else {
        if (ball.x + ball.sprite->width >= vmi_p.XResolution - BIT(3) || ball.x <= BIT(3)) {
          ball.dx = -ball.dx;
          ball.contact = true;
        }
        if (ball.y <= BIT(3)) {
          ball.dy = -ball.dy;
          ball.contact = true;
        }
        if (ball.y + ball.sprite->height >= paddle.y+1 && ball.x + ball.sprite->width >= paddle.x && ball.x <= paddle.x + paddle.sprite->width) {
          ball.dy = -ball.dy;
          ball.contact = true;
        }
        if (ball.y + ball.sprite->height >= vmi_p.YResolution - 10) {
          ball.base = true;
          lives--;
          ball.contact = false;
        }
        for (int i = 0; i < 72; i++) {
          if (!bricks[i].destroyed) {
            if (ball.y <= bricks[i].y + brick_sprite->height && ball.y + ball.sprite->height >= bricks[i].y && ball.x + ball.sprite->width >= bricks[i].x && ball.x <= bricks[i].x + brick_sprite->width) {
              ball.dy = -ball.dy;
              bricks[i].destroyed = true;
              destroyed++;
              ball.contact = true;
            }
          }
        }
        ball.x += ball.dx;
        ball.y += ball.dy;
        

    }
    return 0;
}


int (run)() {
    int ipc_status,r=0;
    int frames = 0;
    message msg;

    while (gameState!=EXIT) {
    
    if ((r=driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & BIT(bit_no_timer)) {
            if (gameState == GAME) {
              frames++;
              if (frames % 5 == 0) { //60/5 = 12 fps
                move_ball();
                draw_frame();
              }
            } else {
              draw_frame();
            }
          }
          if (msg.m_notify.interrupts & BIT(bit_no_keyboard)){
            (kbc_ih)();
            handle_keyboard();
            
          } 
        }
      }
      if (lives == 0) {
        gameState = LOST;
        lives = 3;
      }
      if (destroyed == 72) {
        gameState = WON;
        destroyed = 0;
      }
    }
  return 0;
}
