#include "game/game.h"

extern GameState gameState;
uint8_t bit_no_keyboard = 0;
uint8_t bit_no_timer = 0;
Background background;
Background background2;
Paddle paddle;
Brick bricks[72];
Ball ball;
extern vbe_mode_info_t vmi_p;
Sprite *background_sprite;
Sprite *background2_sprite;
extern Sprite *ball_sprite;
Sprite *brick_sprite;
Sprite *paddle_sprite;
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


/*int (prepare_timer)() {
    if(timer_subscribe_int(&bit_no_timer)!=0) {return 1;}
    return 0;
}
int (disable_timer)() {
    if(timer_unsubscribe_int()) return 1;
    return 0;
}*/


//----------------objects--------------------------------------------------------------------------------------------------------------------


int (prepare_objects)() {

    background_sprite = create_sprite((xpm_map_t)background_xpm);
    background2_sprite = create_sprite((xpm_map_t)background2_xpm);
    paddle_sprite = create_sprite((xpm_map_t)paddle_xpm);
    brick_sprite = create_sprite((xpm_map_t)brick_xpm);


    initBackground(&background, 0, 0, background_sprite);
    initBackground(&background2,0,0,background2_sprite);
    initPaddle(&paddle, 395, 500, paddle_sprite);
    for (int i = 0; i < 72; i++) {
      initBrick(&bricks[i], 16+((i%12)*64), (int)(i/12)*32, brick_sprite);
    }


    return 0;
}


//----------------run--------------------------------------------------------------------------------------------------------------------
int (draw_frame)() {
    if(drawBackground(&background)) {return 1;}
    if(drawPaddle(&paddle)) {return 1;}
    for (int i=0; i<72; i++) {
      if(drawBrick(&bricks[i])){return 1;}
    }
    return 0;
}

int (run)() {
    int ipc_status,r=0;
    message msg;

    while (gameState!=EXIT) {
    
    if ((r=driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & BIT(1)){
            (kbc_ih)();
            handle_keyboard();
            draw_frame();
          } 
        }
      }
    }
  return 0;
}
