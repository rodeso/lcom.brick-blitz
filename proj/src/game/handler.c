#include "handler.h"

extern uint8_t scancodes[2];
GameState gameState = MENU;

void handle_keyboard() {
  switch(scancodes[0]) {
    case 0x1E:
      printf("Left arrow key pressed\n");
      break;
    case 0x20:
      printf("Right arrow key pressed\n");
      break;
    case 0x01:
      printf("ESC key pressed\n");
      gameState=EXIT;
    default:
      break;
  }
}
