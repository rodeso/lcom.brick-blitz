#include "kbc.h"

#include <lcom/lcf.h>

uint8_t scancodes[2];
int scancode_curr_byte=0;
bool big_scancode = false;
bool isMake;
int size;


int (read_status_register)(uint8_t* status) {
  //printf("%s is running!\n", __func__);
  if (util_sys_inb(INPUT_BUFFER_KEYBOARD, status)) {return 1;} //reading the KBC state
  return 0;
}
int (read_scancode)(uint8_t port,uint8_t* result) {
  //printf("%s is running!\n", __func__);
  int trying=0;
  while (trying < 20) {
      uint8_t status;
      if (read_status_register(&status)){return 1;}

      if (status & OUTPUT_BUFFER_FULL){ //if the output buffer is full, deliver the result

        if (!(((status & TIMEOUT_ERROR) || (status & PARITY_ERROR))) ){ //if there are no errors
          if (util_sys_inb(port,result)) return 1; //read and return
          return 0;
        }
        else return 1;
      }
      trying++; //keep trying to read
    }
    return 1;
}

int (read_KBC_outbuf)(uint8_t port, uint8_t *output, uint8_t mouse){
    int keep_trying = 0;
    while (keep_trying < 20){

    //read status
    uint8_t status;
    if (read_status_register(&status)) return 1;

    //if buffer  full
    if (status & OUTPUT_BUFFER_FULL){

      //if there are no errors
      if (!(((status & TIMEOUT_ERROR) || (status & PARITY_ERROR))) ){

        if (mouse && !(status & BIT(5))) return 1;
        if (!mouse && (status & BIT(5))) return 1;

        //read and return
        if (util_sys_inb(port,output)) return 1;
        return 0;
      } 

      else return 1;
    }
    tickdelay(micros_to_ticks(20000));
    keep_trying++;
  }

  return 1;
}

void (kbc_ih)() {
    printf("%s is running!\n", __func__);

    if (!big_scancode) {size=1;} //(re)establishing if the scancode has 1 or more bytes

    read_scancode(OUTPUT_BUFFER_KEYBOARD, &scancodes[scancode_curr_byte]); //reading process

    big_scancode=false;
    if (scancodes[scancode_curr_byte]==0xE0) { //if the scancode is long
        scancode_curr_byte=1;
        big_scancode=true;
    } else if (!big_scancode) { //if scancode is 1 byte, as usual
        if ((scancodes[scancode_curr_byte] & BIT(7))) isMake = false; // detect if scancode is breakcode
        else isMake = true; //or makecode
        scancode_curr_byte = 0;
    }

}


int (enable_interrupts)() {

  //warn you are going to read 0x20 -> read byte -> escrever a avisar que vais ler
  if (write_command(INPUT_BUFFER_KEYBOARD,READ_COMMAND)) return 1;

  //a seguir lês e guardas o command byte
  uint8_t command_byte;
  if (read_scancode(OUTPUT_BUFFER_KEYBOARD,&command_byte)) return 1;

  //ativas o bit 0 XXXXXXXX -> XXXXXXX1 -> INT 1: enable interrupts on OBF, from keyboard (slide 15, https://web.fe.up.pt/~pfs/aulas/lcom2324/at/4kbd.pdf)
  command_byte = command_byte | BIT(0);

  //warn you are going to write 0x60 -> write byte -> escrever que vais escrever
  if (write_command(INPUT_BUFFER_KEYBOARD,WRITE_COMMAND)) return 1; // 0x60 but is a command


  if (write_command(OUTPUT_BUFFER_KEYBOARD, command_byte)) return 1; //escrever (0x60 is a port here)

  return  0;
}

int (write_command)(uint8_t port, uint8_t the_command) {
    int trying=0;
    while (trying < 20) {

        uint8_t status;
        if (read_status_register(&status)) return 1;

        if (!(status & BIT(1))){
          if (sys_outb(port,the_command)) return 1;
          return 0;
        }

        trying++;
    }
    return 1;
}



