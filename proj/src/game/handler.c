#include "handler.h"

extern uint8_t scancodes[2];
extern Paddle paddle;
extern Ball ball;
GameState gameState = MENU;

void handle_keyboard() {
  switch(scancodes[0]) {
    case 30: //A
    if (paddle.x > 0)
      paddle.x -= BIT(3);
      break;
    case 32: //D
    if (paddle.x + paddle.sprite->width < vmi_p.XResolution)
      paddle.x += BIT(3);
      break;
    case 1: //ESC
    if (gameState == MENU) {
      gameState=EXIT;
    }
    else if (gameState == GAME) {
      gameState = MENU;
    }
    else if (gameState == LOST || gameState == WON) {
      gameState = MENU;
    }
      break;
    case 57: //Spacebar
      break;
    case 28: //Enter
    if (gameState == MENU) {
      gameState = GAME;
    }
    else if (gameState == LOST || gameState == WON) {
      gameState = MENU;
    }
    else if (gameState == GAME) {
      ball.base = false;
    }
    break;
    default:
      break;
  }
}
