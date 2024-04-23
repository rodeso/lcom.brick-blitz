
#pragma once
 
#include <stdint.h>

#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdint.h>
#include <stdio.h>

#define yippee

vbe_mode_info_t vmi_p;
  
//int (vbe_display_vbe_contr_info)(struct vg_vbe_contr_info *info_p);



int (vbe_set_display_mode)(uint16_t mode);

int (vbe_mapping_videoRAM_to_address_space)(uint16_t mode);

int (vbe_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);  

int (vbe_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vbe_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
