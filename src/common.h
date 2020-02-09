#ifndef _COMMON_H
#define _COMMON_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SNAKE_SPEED 10

#define DEFAULT_S_W 10
#define DEFAULT_S_H DEFAULT_S_W
#define DEFAULT_F_W DEFAULT_S_W
#define DEFAULT_F_H DEFAULT_S_W

#define FPS 60
#define FPS_DIV 20
#define FPS_THR (FPS / FPS_DIV)

enum game_state_e {
    MAIN_MENU,
    INIT_GAME,
    PLAY,
    OVER,

    STATES_ALL
};

#endif