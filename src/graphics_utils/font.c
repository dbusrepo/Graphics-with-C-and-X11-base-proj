#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "common.h"
#include "screen_info_rgb.h"
#include "font.h"

#define FONT_Y_SIZE 13
#define FONT_X_SIZE 8
#define FONT_SPACING 2

static const uint8_t period[] =
        {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t space[] =
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t digits[][FONT_Y_SIZE] = {
        {0x0,0x0, 0x18,0x3C,0x66,0xC3,0xC3,0xC3,0xC3,0xC3,0x66,0x3C,0x18},
        {0x0,0x0, 0x7F,0x7F,0xC,0xC,0xC,0xC,0xC,0xC,0x6C,0x3C,0xC},
        {0x0,0x0, 0xFF,0xFF,0xC0,0x60,0x30,0x18,0xC,0x6,0xC6,0x66,0x3C},
        {0x0,0x0, 0x7E,0xC3,0x3,0x6,0xC,0x38,0xC,0x6,0x3,0xC3,0x7E},
        {0x0,0x0, 0x6,0x6,0x6,0x6,0xFF,0xFF,0xC6,0xC6,0x66,0x36,0x1E},
        {0x0,0x0, 0x7E,0xFF,0xC3,0x3,0x3,0xFF,0xFE,0xC0,0xC0,0xC0,0xFE},
        {0x0,0x0, 0x7E,0xFF,0xC3,0xC3,0xC3,0xFF,0xFE,0xC0,0xC0,0xC0,0x7E},
        {0x0,0x0, 0x60,0x60,0x60,0x60,0x30,0x18,0xC,0x6,0x3,0x3,0xFF},
        {0x0,0x0, 0x7E,0xFF,0xC3,0xC3,0xC3,0x7E,0xC3,0xC3,0xC3,0xC3,0x7E},
        {0x0,0x0, 0x7E,0xFF,0xC3,0x3,0x3,0x7F,0xC3,0xC3,0xC3,0xC3,0x7E}
};

static const uint8_t letters[][FONT_Y_SIZE] = {
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
        {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
        {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
        {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
        {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
        {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
        {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
        {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
        {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
        {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
        {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
        {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
        {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
        {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
        {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

static uint8_t font_bitmaps[256][13];
static uint8_t *text_color;

void set_text_color(screen_info_rgb_t *screen_info, uint32_t red, uint32_t green, uint32_t blue) {

    uint32_t native_col = ext_to_native(screen_info, red, green, blue);

    uint32_t mask = MAX_BYTE;
    uint32_t shift = 0;

    // stuff the bytes in the unsigned long col into the text-color buffer, in
    // little-endian order
    uint8_t *c = text_color;
    for(uint32_t i=0; i < screen_info->bytes_per_pixel; i++) {
        *c++ = (uint8_t)((native_col & mask) >> shift);
        mask <<= BITS_PER_BYTE;
        shift += BITS_PER_BYTE;
    }
}

void font_init(screen_info_rgb_t *screen_info) {

    text_color = malloc(screen_info->bytes_per_pixel * sizeof(uint8_t));
    set_text_color(screen_info, screen_info->ext_max_red, screen_info->ext_max_green, screen_info->ext_max_blue);

    //- create font bitmaps
    for(int i=0; i<26; i++) {
        for(int j=0; j<13; j++) {
            font_bitmaps['A' + i][j] = letters[i][j];
            font_bitmaps['a' + i][j] = letters[i][j];
        }
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<13; j++) {
            font_bitmaps['0' + i][j] = digits[i][j];
        }
    }

    for(int j=0; j<13; j++) {
        font_bitmaps[' '][j] = space[j];
    }

    for(int j=0; j<13; j++) {
        font_bitmaps['.'][j] = period[j];
    }
}


//#define SW_RAST_Y_REVERSAL(height,y) ((height) - (y))
#define SW_RAST_Y_REVERSAL(ysize,y) (y)

void draw_text(screen_info_rgb_t *screen_info, uint32_t xsize, uint32_t ysize, uint32_t x, uint32_t y, const char *text) {

    uint32_t x_offset = x * screen_info->bytes_per_pixel;
    uint8_t *pix;

    for(uint32_t font_y=0; font_y < FONT_Y_SIZE; font_y++) {
        pix= screen_info->buffer + x_offset + ((y + font_y) * xsize) * screen_info->bytes_per_pixel;

        for(size_t c=0; c<strlen(text); c++) {
            for(uint32_t font_x=0, current_bit=0x80;
                font_x < FONT_X_SIZE;
                font_x++, current_bit >>= 1)
            {
                if(font_bitmaps[(size_t)text[c]][FONT_Y_SIZE-1-font_y] & current_bit) {
                    // found a lit pixel so draw it
                    uint8_t *fg_color = text_color;
                    for(uint32_t b=0; b < screen_info->bytes_per_pixel; b++) {
                        *pix++ =  *fg_color++;
                    }
                } else {
                    // 0 or empty pixel so move to the next
                    pix += screen_info->bytes_per_pixel;
                }
            }
            for(uint32_t font_x=0; font_x < FONT_SPACING; font_x++) {
                pix += screen_info->bytes_per_pixel;
            }
        }
    }
}
