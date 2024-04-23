#include "vbe.h"


static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */



int(vbe_set_display_mode)(uint16_t mode) {

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno=0x10;
  r86.ah=0x4F; //Invoking VBE function...
  r86.al=0x02;  //0x02 - Set VBE Mode
  r86.bx=mode;  //Selection of the mode

  r86.bx = r86.bx | BIT(14);

  if(sys_int86(&r86)) {return 1;}
  
  if(r86.al != 0x4F) {return 1;} //function not supported

  if (r86.ah != 0x00) {
    switch(r86.ah) {
      case 0x01:
        printf("Function call failed");
        return 1;
      case 0x02:
        printf("Function is not supported in current HW configuration");
        return 1;
      case 0x03:
        printf("Function is invalid in current video mode");
        return 1;
    }
  }
   return 0;
}



int (vbe_mapping_videoRAM_to_address_space)(uint16_t mode) {
  struct minix_mem_range mr;
  unsigned int vram_base;  //VRAM's physical addresss
  unsigned int vram_size;  //VRAM's size, but you can use the frame-buffer size, instead
  int r;
  
  
  if(vbe_get_mode_info(mode,&vmi_p)!=0) {return 1;}

  vram_base=vmi_p.PhysBasePtr;
  vram_size=vmi_p.XResolution*vmi_p.YResolution*((vmi_p.BitsPerPixel+7)/8);

  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size; 

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
      panic("sys_privctl (ADD_MEM) failed: %d\n", r);
  }

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  if(video_mem == MAP_FAILED) {
      panic("couldn't map video memory");
  }

  return 0;

}



int (vbe_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x > vmi_p.XResolution || y > vmi_p.YResolution) return 1;



  unsigned int index = ((vmi_p.XResolution *y)+x) *((vmi_p.BitsPerPixel +7)/8);
  if (memcpy(&video_mem[index],&color, ((vmi_p.BitsPerPixel +7)/8))==NULL) return 1;

  return 0;
}



int (vbe_draw_line)(uint16_t x,uint16_t y,uint16_t len, uint32_t color) {
  for (int i = 0; i<len;i++) {
    if(vbe_draw_pixel(x+i,y, color)) return 1;
  }
  return 0;
}



int (vbe_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i<height; i++) {
    if(vbe_draw_line(x,y+i,width, color)) return 1;
  }
  return 0;
}


int (vbe_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  xpm_image_t img;

  uint8_t *c = xpm_load(xpm, XPM_INDEXED, &img);

  for (int h = 0 ; h < img.height ; h++) {
    for (int w = 0 ; w < img.width ; w++) {
      if (vbe_draw_pixel(x + w, y + h, *c) != 0) return 1;
      c++; 
    }
  }
  return 0;
}