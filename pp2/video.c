#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t x_res; // hor. resolution
    uint16_t y_res; // ver. resolution
    uint8_t bpp; // bits per pixel
    uint8_t r_sz; // red comp. size
    uint8_t r_pos; // red comp. LSB position
    uint8_t g_sz; // green comp. size
    uint8_t g_pos; // green comp. LSB position
    uint8_t b_sz; // blue comp. size
    uint8_t b_pos; // blue comp. LSB position
    phys_addr_t phys_addr; // video ram base physical addresses
} lpv_mode_info_t;

enum lpv_dir_t {
    lpv_hor, // horizontal line
    lpv_vert // vertical line
};

int lpv_set_mode(uint16_t mode);
int lpv_get_mode_info(uint16_t mode, lpv_mode_info_t* lmi_p);
uint8_t *video_map_phys(uint32_t ph_addr, size_t len);

int draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
	if (x >= hres || y >= vres) return 1;
	memcpy(video_mem + (y * hres + x) * bits_per_pixel / 8, (void *) color, bits_per_pixel / 8);
	return 0;
}

uint8_t *video_mem;
uint8_t hres, vres, bits_per_pixel;

int (pp_test_line)(uint8_t mode, enum lpv_dir_t dir, uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint32_t delay) {
	lpv_mode_info_t lmi;
	if (mode < 1 || mode > 4) return 1;
    if(lpv_set_mode(mode)) return 1;

	if (lpv_get_mode_info(mode, &lmi)) return 1;



	hres = lmi.x_res;
	vres = lmi.y_res;
	bits_per_pixel = lmi.bpp;
	video_mem = video_map_phys(lmi.phys_addr, lmi.x_res * lmi.y_res * lmi.bpp / 8);
	if (video_mem == NULL) return 1;


	uint32_t newColor = 0;
    if (mode == 3) {
        uint32_t red = ((1 << lmi.r_sz) - 1) & (color >> lmi.r_pos); 
        uint32_t green = ((1 << lmi.g_sz) - 1) & (color >> lmi.g_pos);
        uint32_t blue = ((1 << lmi.b_sz) - 1) & (color >> lmi.b_pos);
        newColor = (red << lmi.r_pos) | (green << lmi.g_pos) | (blue << lmi.b_pos);
    }
    else {
        newColor = color;
    }

	switch (dir) {
		case lpv_hor:
			for (int i = 0; i < len; i++) {
				if (draw_pixel(x + i, y, newColor)) return 1;
			}
			break;
		case lpv_vert:
			for (int i = 0; i < len; i++) {
				if (draw_pixel(x, y + i, newColor)) return 1;
			}
			break;
	}

    sleep(delay);
    if (lpv_set_mode(0)) return 1;
    return 0;
}