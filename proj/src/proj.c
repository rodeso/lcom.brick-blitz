// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "game/game.h"

extern uint8_t bit_no;
extern Paddle paddle;
extern Brick bricks[32];
extern Ball ball;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (proj_main_loop)(int argc, char *argv[]){
    if (prepare_keyboard()) return 1;
    printf("keyboard prepared\n");
    if (prepare_video()) return 1;
    printf("video prepared\n");
    if (prepare_objects()) return 1;
    printf("objects prepared\n");
    if(draw_frame()) return 1;
    printf("frame drawn\n");
    if (run()) return 1;
    printf("game ran\n");
    if (disable_keyboard()) return 1;
    printf("keyboard disabled\n");
    if (disable_video()) return 1;
    printf("video disabled\n");

    return 0;
}
