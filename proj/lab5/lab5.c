// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>


#include "vbe.h"
#include "kbc.h"

extern vbe_mode_info_t vmi_p;


// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if(vbe_set_display_mode(mode) != 0) {return 1;}

  sleep(delay);

  if(vg_exit()!=0) {return 1;}

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  if(vbe_mapping_videoRAM_to_address_space(mode) != 0) {return 1;}

  if(vbe_set_display_mode(mode) != 0) {return 1;}

  if(vbe_draw_rectangle(x, y, width, height, color) != 0) {return 1;}

  if (kbc_ESC_exit() != 0) return 1;
  if (vg_exit() != 0) return 1;


  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if(vbe_set_display_mode(mode) != 0) {return 1;}

  if(vbe_mapping_videoRAM_to_address_space(mode) != 0) {return 1;}

  if(vbe_draw_pattern(mode, no_rectangles, first, step)!=0) {return 1;}

  if (kbc_ESC_exit() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  uint16_t mode = 0x105;

  if(vbe_set_display_mode(mode) != 0) {return 1;}

  if(vbe_mapping_videoRAM_to_address_space(mode) != 0) {return 1;}

  if(vbe_draw_xpm(xpm,x,y) != 0) {return 1;}
  
  if (kbc_ESC_exit() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,int16_t speed, uint8_t fr_rate) {

              
  uint16_t mode = 0x105;


  if(vbe_set_display_mode(mode) != 0) {return 1;}

  if(vbe_mapping_videoRAM_to_address_space(mode) != 0) {return 1;}


  //if speed>0 a distance, x=x+speed until x==xf ..same for y
  //if speed<0 a cada speed, frame, x=x+1 until x==xf ..same for y
  

  if (vbe_move(xpm, xi, yi, xf, yf, speed, fr_rate) !=0 ) {return 1;}


  if (kbc_ESC_exit() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 0;

}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}