// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "ps2.h"
#include "pit.h"

extern uint8_t byte_index;
extern struct packet mouse_packet;


// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status,r;
  message msg;

  uint32_t mouse_mask=0;
  uint8_t bit_no=0;

  if (mouse_subscribe_int(&bit_no)!=0) {return 1;} //subscribes/activates the interrupts
  mouse_mask=BIT(bit_no);

  
  if(mouse_write_data(0XF4)!=0) {return 1;}; //Enable stream mode Data Reporting

  while (cnt){
    if ((r=driver_receive(ANY, &msg, &ipc_status)) != 0) { 
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & mouse_mask) 
            mouse_ih();
            mouse_sync_bytes();
            if (byte_index==3) {
              mouse_bytes_to_packet();
              mouse_print_packet(&mouse_packet);
              byte_index=0;
              cnt--;
            }
          break;
        default:
          break; 
      }
    }
  }

  if(mouse_write_data(0XF5)!=0) {return 1;}; //Disable stream mode Data Reporting

  if (mouse_unsubscribe_int()!=0){return 1;}
    return 1;

}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

/*int (mouse_test_gesture)() {
    printf("%s: under construction\n", __func__);
    return 1;
}*/


