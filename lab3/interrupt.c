#include <lcom/lcf.h>
#include <lab3.h>
#include <lab2.h>

#define OUT_BUF (0x60)
void (kbc_ih)() {
    int buffer;
    buffer = util_sys_inb(OUT_BUF, IRQ1_VECTOR)
}