#pragma once

#include "../graphics_utils/screen_settings.h"
#include "../graphics_utils/input_keys.h"
#include "../graphics_utils/screen_info.h"

typedef void (*fun_update_t)(int64_t elapsed_time);
typedef void (*fun_draw_t)(void);
typedef void (*fun_finish_t)(void);
typedef void (*fun_key_t)(int key, int action);

typedef struct app app_t;

app_t *app_init(screen_settings_t *screen_settings);

void app_run(app_t *app,
             fun_update_t update_fun,
             fun_draw_t draw_fun,
             fun_finish_t finish_fun,
             fun_key_t key_fun);

screen_info_t *app_get_screen_info(app_t *app);

uint32_t app_get_width(app_t *app);
uint32_t app_get_height(app_t *app);
void app_show_fps(app_t *app, int x, int y);

void app_clear_screen(app_t *app);
void app_toggle_fullscreen(app_t *app);
void app_stop(app_t *app); // used in the call back

///* Image/texture information */
//typedef struct {
//    int Width, Height;
//    int Format;
//    int BytesPerPixel;
//    unsigned char *Data;
//} GLFWimage;
