#include "handler.h"

extern uint8_t scancodes[2];
extern Paddle paddle;
GameState gameState = MENU;

void handle_keyboard() {
  switch(scancodes[0]) {
    case 30:
      paddle.x -= 10;
      break;
    case 32:
      paddle.x += 10;
      break;
    case 1:
      gameState=EXIT;
    default:
      break;
  }
}
