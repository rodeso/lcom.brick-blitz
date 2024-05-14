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
    if (keyboard_read_scancode(&scancode)) return 1;
    if (scancode == 0x1E) return 1;
    return 0;
}
int (pressed_right) () {
    uint8_t scancode;
    if (keyboard_read_scancode(&scancode)) return 1;
    if (scancode == 0x20) return 1;
    return 0;
}


//----------------objects--------------------------------------------------------------------------------------------------------------------

int prepare_objects() {
    initPaddle(&paddle, 0, 0, 10, 10);
    for (int i = 0; i < 32; i++) {
        initBrick(&bricks[i], 0, 0, 10, 10); // This correctly initializes each brick in the array
    }
}
    initBall(&ball, 0, 0, 10, 10);
    return 0;
}
}


//----------------run--------------------------------------------------------------------------------------------------------------------


int (run)() {
    
    while(true) {
        if (pressed_left()) movePaddleLeft(&paddle, 1);
        if (pressed_right()) movePaddleRight(&paddle, 1);
    }



    return 0;
}