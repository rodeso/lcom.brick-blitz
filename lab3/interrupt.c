#include <lcom/lcf.h>
#include <lab3.h>
#include <lab2.h>
#include <keyboard.h>

int hook_id=0;


void (kbc_ih)() {
    
    uint8_t status;
    int buf = util_sys_inb(OUT_BUF, &status);
    if (buf=1) {return 1;}










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