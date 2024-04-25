#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_
#pragma once

#include <minix/sysutil.h>
#include <lcom/lcf.h>

//O teclado permite introduzir uma sequencia de caracteres (Palavras do Stor)
#include <stdbool.h>
#include <stdint.h>

#define IRQ0_VECTOR     0x50
#define IRQ1_VECTOR     0x01

#define KEYBOARD_IRQ_LINE    1
#define READ_KEYBOARD_STATUS 0x64
#define INPUT_BUFFER_KEYBOARD 0x64 //receives status and for sending KBC commands
#define OUTPUT_BUFFER_KEYBOARD 0x60 //receives scancodes and for sending commands to keyboard
#define ESC_SCANCODE       0x81
#define BREAK_CODE       BIT(7)
#define TWO_BYTES       0xE0
#define ENABLE_INT      BIT(0)
#define TIMEOUT_ERROR   BIT(6)
#define PARITY_ERROR    BIT(7)
#define OUTPUT_BUFFER_FULL BIT(0)
#define INPUT_BUFFER_FULL  BIT(1)
#define READ_COMMAND   0x20
#define WRITE_COMMAND   0x60
#define DELAY_US        20000

//exige apenas o aspeto do hardware (Palavras do Stor)

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */

  if (lsb==NULL) {return 1;}

  uint16_t filter = (val & 0xFF);
  *lsb = (uint8_t)filter;
  
  printf("%s is running!\n", __func__);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */

  if (msb==NULL) {return 1;}

  *msb = val >> 8;

  printf("%s is running!\n", __func__);
  return 0;
}
int (util_sys_inb)(int port, uint8_t *value) {

  if (value == NULL) return 1;

  uint32_t temporary_value=0;
  int res;

  res = sys_inb(port,&temporary_value);
  if (res == 1) return 1;
  *value = (uint8_t)temporary_value;

  return res;
}



int (enable_interrupts)();

int (read_KBC_outbuf)(uint8_t port, uint8_t *output, uint8_t mouse);
int (read_scancode)(uint8_t port,uint8_t* result);
int (write_command)(uint8_t port, uint8_t the_command);
int (kbc_ESC_exit)();
#endif
