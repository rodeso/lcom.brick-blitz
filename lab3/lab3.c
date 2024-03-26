#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <.minix-src/include/i386/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

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



int(kbd_test_scan)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);
  


    uint8_t irq_set;

    if (keyboard_subscribe_int(&irq_set) != 0) {return 1;}


  //este é o loop do timer test int, que falta editar para funcionar aqui
    while (time > 0) {
    
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed: %d\n", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: {
          if (msg.m_notify.interrupts & irq_set) {
            timer_int_handler();
            if (globalCounter % 60 == 0) {
              timer_print_elapsed_time();
              time--;
            }
          }
        break;
      }
      default:
        break;
      }
    }
  }










  /*if (breakcode == 0x81)
    return 0;
    */




  sys_irqrmpolicy();
  return 1;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
