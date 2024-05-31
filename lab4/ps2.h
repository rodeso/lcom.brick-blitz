#ifndef _LCOM_PS2_H_
#define _LCOM_PS2_H_
#pragma once

 
#include <stdint.h>

#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <stdint.h>
#include <stdio.h>

#define IRQ_LINE_MOUSE 12 /**< Mouse IRQ line */
#define INPUT_BUFFER 0x64 /**< Sending KBC commands and arguments */
#define OUTPUT_BUFFER 0x60 /**< Receive acknowledgements and responses */
#define MOUSE_COMMAND_HEADS_UP 0xD4 /**< Request forwarding of byte (command) to the mouse */
#define ACK 0xFA /**< Acknowledgement byte */
#define SET_STREAM_MODE 0xEA /**< Set stream mode command */
#define ENABLE_DATA_REPORTING 0xF4 /**< Enable data reporting command */
#define DISABLE_DATA_REPORTING 0xF5 /**< Disable data reporting command */

#define yippee



  

int (mouse_write_data)(uint8_t command);
void (mouse_sync_bytes)();
void (mouse_bytes_to_packet)();
int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
#endif 
