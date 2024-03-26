#include <lcom/lcf.h>
#include <lab3.h>
#include <keyboard.h>

int hook_id=0;
uint8_t scancodes[2];
int scancode_curr_byte=0;
bool big_scancode = false;
bool isMake;
int size;

int (read_status_register)(uint8_t* status) {
  if (util_sys_inb(INPUT_BUFFER_KEYBOARD, status)) {return 1;} //reading the KBC state
  return 0;
}
int (read_scancode)(uint8_t port,uint8_t* result) {
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
      trying++; //if not full, keep reading

      
    }
    return 1;
}

void (kbc_ih)() {

    uint8_t status;

    if (!big_scancode) {size=1;} //(re)establishing if the scancode has 1 or more bytes

    read_scancode(OUTPUT_BUFFER_KEYBOARD, &scancodes[scancode_curr_byte]); //reading process

    if (scancodes[scancode_curr_byte]==0xE0) { //if the scancode is long
        scancode_curr_byte=1;
        big_scancode=true;
    } else if (!big_scancode) { //if scancode is 1 byte, as usual
        if ((scancodes[scancode_curr_byte] & BIT(7))) isMake = false; // detect if scancode is breakcode
        else isMake = true; //or makecode
        scancode_curr_byte = 0;
    }

}


int (keyboard_subscribe_int)(uint8_t *bit_no) {
    printf("%s is running!\n", __func__);

    if(bit_no==NULL) {return 1;}
    
    hook_id=KEYBOARD_IRQ;
    *bit_no=hook_id;

    int pol = sys_irqsetpolicy(IRQ1_VECTOR,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id);
    if (pol==1) {return 1;}

    return 0;

}

int (keyboard_unsubscribe_int)() {

    printf("%s is running!\n", __func__);

    int pol = sys_irqrmpolicy(&hook_id);
    if (pol==1) {return 1;}

    return 0;
}