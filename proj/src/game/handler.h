#include "dvcs/keyboard/kbc.h"
#include "dvcs/timer/pit.h"
#include "dvcs/graphics/vbe.h"
#include <lcom/lcf.h>

typedef enum {
    MENU,   
    GAME,
    LOST,
    WON,
    EXIT
} GameState;

void handle_keyboard();
