#include "graphics.h"


int(set_display_mode)(uint16_t mode) {

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno=0x10;
  r86.ah=0x4F; //Invoking VBE function...
  r86.al=0x02;  //0x02 - Set VBE Mode
  r86.bx=mode;

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


