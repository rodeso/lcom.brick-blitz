#include <lcom/lcf.h>

#include "interrupt.h"

#include <lcom/lab3.h>
#include <stdbool.h>
#include <stdint.h>

extern uint8_t scancodes[2];
extern int scancode_curr_byte;

extern bool isMake;
extern bool big_scancode;
extern int globalCounter;




int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}



int(kbd_test_scan)() {  //reading the scancodes via KBD interrupts. ESC ends the reading.
  int size = 1;
  int ipc_status,r;
  message msg;

  uint32_t keyboard_mask=0;
  uint8_t bit_no=0;


  if (keyboard_subscribe_int(&bit_no)!=0) {return 1;} //subscribes/activates the interrupts
  keyboard_mask=BIT(bit_no);


  while (scancodes[scancode_curr_byte] != ESC_SCANCODE) {  //while the scancode isnt the ESC one
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & keyboard_mask) {
            kbc_ih();
            if (!big_scancode) {
              kbd_print_scancode(isMake, size, scancodes);
              size = 1;
              
            }
            else
              size = 2;
          }
          break;
        default:
          break;
      }
    }
  }
  if (keyboard_unsubscribe_int()) //unsubscribes the interrupts
    return 1;

  return 0;
}

int(kbd_test_poll)() { //reading the scancodes via polling. ESC ends the reading.
    printf("%s is running!\n", __func__);
    uint8_t scancode;
    while (scancodes[0]!=ESC_SCANCODE) {  //while the scancode isnt the ESC one
        if (read_scancode(OUTPUT_BUFFER_KEYBOARD, &scancode) == 0) {
          kbd_print_scancode(!(scancode & BREAK_CODE), scancode == 0xE0 ? 2 : 1, &scancode);
        }
    }

    if (enable_interrupts()) return 1; //after scancode reading process, reactivate the interrupts to avoid keyboard problems

  return 0;
}



int(kbd_test_timed_scan)(uint8_t n) { //reading the scancodes via KBD interrupts. ESC ends the reading or if the given n time passes without receiving scancodes
  int size = 1;
  int ipc_status,r;
  message msg;

  int time_passed=0;

  uint32_t timer_mask=0;
  uint8_t bit_no1=0;
  uint32_t keyboard_mask=0;
  uint8_t bit_no2=0;


  if (timer_subscribe_int(&bit_no1)!=0) {return 1;}   //enable interrupts for the timer and for the keyboard
  timer_mask=BIT(bit_no1);
  if (keyboard_subscribe_int(&bit_no2)!=0) {return 1;}
  keyboard_mask=BIT(bit_no2);


  while (scancodes[scancode_curr_byte] != ESC_SCANCODE && time_passed < n) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & timer_mask) {
            timer_int_handler();
            if (globalCounter % 60==0) {
                time_passed++;
            }
          }

          if (msg.m_notify.interrupts & keyboard_mask) {
            kbc_ih();
            if (!big_scancode) {
              kbd_print_scancode(isMake, size, scancodes);
              size = 1;
              
            }
            else
              size = 2;
          }

          break;
        default:
          break;
      }
    }
  }
  if (timer_unsubscribe_int()) {return 1;}
  if (keyboard_unsubscribe_int()) {return 1;}
  

  return 0;
}
