#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>
extern int globalCounter; 

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {

  printf("%s is running!\n", __func__);

  uint8_t st=0x00; 

  int cnf=timer_get_conf(timer,&st);  //creation of readback command for status byte request
  if (cnf==1) {return 1;}

  int dis = timer_display_conf(timer,st,field);  //displaying of the specified field of the status
  if (dis==1) {return 1;}

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  
  printf("%s is running!\n", __func__);
  
  int res= timer_set_frequency(timer,freq); //specific change/reconfiguration of the given timer

  return res;
}

int(timer_test_int)(uint8_t time) {

  printf("%s is running!\n", __func__);
  int ipc_status, r; 
  message msg;

  uint32_t irq_set = 0;
  uint8_t bit_no = 0;

  if (timer_subscribe_int(&bit_no) != 0) {return 1;} //subscribes/activates interrupts for the timer
  irq_set = BIT(bit_no);

  while (time > 0) {
    
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed: %d\n", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: {
          if (msg.m_notify.interrupts & irq_set) {
            timer_int_handler();  //increments global counter
            if (globalCounter % 60 == 0) {  //when global counter equals to a minute passed, decrement the time remaining
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

  if (timer_unsubscribe_int() != 0) {return 1;} //unsubscribes interrupts for the timer
  return 0; 
}
