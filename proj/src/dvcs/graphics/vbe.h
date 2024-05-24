
#pragma once
 
#include <stdint.h>

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#define yippee

vbe_mode_info_t vmi_p;
  



int (vbe_set_display_mode)(uint16_t mode);

int (vbe_mapping_videoRAM_to_address_space)(uint16_t mode);

int (vbe_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);  

int (vbe_draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vbe_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (vbe_draw_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

int (vbe_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

int (vbe_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,int16_t speed, uint8_t fr_rate);
