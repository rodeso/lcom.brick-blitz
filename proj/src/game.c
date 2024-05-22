#include "game.h"

uint8_t bit_no = 0;
Paddle paddle;
Brick bricks[32];
Ball ball;

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
    if(keyboard_subscribe_int(&bit_no)!=0) {return 1;}
    return 0;
}

int (disable_keyboard)() {
    if (keyboard_unsubscribe_int()) return 1;
    return 0;
}

int (pressed_left)() {
    uint8_t scancode;
    if (read_scancode(OUTPUT_BUFFER_KEYBOARD,&scancode)) return 1;
    if (scancode == 0x1E) return 1;
    return 0;
}

int (pressed_right) () {
    uint8_t scancode;
    if (read_scancode(OUTPUT_BUFFER_KEYBOARD,&scancode)) return 1;
    if (scancode == 0x20) return 1;
    return 0;
}
/*
int (pressed_ESC) () {
    uint8_t scancode;
    if (read_scancode(OUTPUT_BUFFER_KEYBOARD,&scancode)!=0) return 1;
    if (scancode == 0x81 ) return 1;
    return 0;
}*/

int (pressed_ESC)(int *flag) {
  int ipc_status,r=0;
  message msg;
  uint8_t scancode=0x00;

  uint32_t keyboard_mask=0;
  uint8_t bit_no=0;

  if(keyboard_subscribe_int(&bit_no) != 0) return 1;
  keyboard_mask=BIT(bit_no);

  while (scancode != 0x81){
    if ((r=driver_receive(ANY, &msg, &ipc_status)) != 0) { 
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & keyboard_mask) 
            read_scancode(OUTPUT_BUFFER_KEYBOARD, &scancode);
          break;
        default:
          break; 
      }
    }
  }
  flag = 0;
  if (keyboard_unsubscribe_int() != 0) return 1;
  return 0;
}


//----------------objects--------------------------------------------------------------------------------------------------------------------


int prepare_objects() {
    initPaddle(&paddle, 0, 0, 10, 10);
    for (int i = 0; i < 32; i++) {
        initBrick(&bricks[i], 0, 0, 10, 10, 0); // This correctly initializes each brick in the array
    }

    initBall(&ball, 0, 0, false);
    return 0;
}


//----------------run--------------------------------------------------------------------------------------------------------------------


int (run)() {
    drawPaddle(&paddle);



    return 0;
}
