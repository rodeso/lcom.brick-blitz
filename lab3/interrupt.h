#ifndef _LCOM_INTERRUPT_H_
#define _LCOM_INTERRUPT_H_
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
#define INPUT_BUFFER_KEYBOARD 0x64
#define OUTPUT_BUFFER_KEYBOARD 0x60
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


// :D
int (keyboard_subscribe_int)(uint8_t *bit_no);
// D:
int (keyboard_unsubscribe_int)();

int (enable_interrupts)();

int (read_scancode)(uint8_t port,uint8_t* result);
int (write_command)(uint8_t port, uint8_t the_command);

#endif
