#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define FRAMERATE 60

enum SNAKE_DIRECTION { SDIR_UP, SDIR_DOWN, SDIR_LEFT, SDIR_RIGHT };

struct game_point {
	int x;
	int y;
};

struct game {
    SDL_Window *window;
	SDL_Renderer *renderer;
	struct game_point *body;
	struct game_point food;

	int size;
	int screen_width;
	int screen_height;
	int fps;
    int grid_width;
    int grid_height;
	int speed;

    bool alive;
	bool is_running;
	bool isgrowing;
	int direction;
};

struct game *game_create(void);
int game_init(struct game *game);
int game_run(struct game *game);
int update_game(struct game *game);
int move_snake_body(struct game *game);
int generate_food(struct game *game);
int generate_head(struct game *game);
int game_terminate(struct game *game);
int change_direction(struct game *game, int type);

#endif
