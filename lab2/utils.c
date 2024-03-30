#include <lcom/lcf.h>

#include <stdint.h>

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
  /* To be implemented by the students */

  uint32_t temporary_value=0x0000;
  int res;

  res = sys_inb(port,&temporary_value);

  if (res==0) {value=(uint8_t*)temporary_value;}


  printf("%s is running!\n", __func__);
  return res;
}
