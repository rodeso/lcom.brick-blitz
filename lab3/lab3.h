#pragma once
//O teclado permite introduzir uma sequencia de caracteres (Palavras do Stor)
#include <stdbool.h>
#include <stdint.h>

#define IRQ0_VECTOR     0x50 
#define IRQ1_VECTOR (IRQ0_VECTOR + 1)
//exige apenas o aspeto do hardware (Palavras do Stor)
int kbd_test_scan(); 
//IDK
int kbd_test_poll(); 
//I DONT KNOW
int kbd_test_timed_scan(uint8_t n);
//???
void kbc_ih(void);
//WHAT
int kbd_print_scancode(bool make, uint8_t size, uint8_t *bytes);
// -_-
int kbd_print_no_sysinb(uint32_t cnt);