#pragma once

typedef int (*fun_close_t)(void); // ritorna 1 bool che indica se terminare
typedef void (*fun_key_t)(int, int); // see glfw.h