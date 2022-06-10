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

struct snake_game_point {
	int x;
	int y;
};

struct snake_game {
    SDL_Window *window;
	SDL_Renderer *renderer;
	struct snake_game_point *body;
	struct snake_game_point food;

	int size;
	int screen_width;
	int screen_height;
	int fps;
    int grid_width;
    int grid_height;
	int speed;

    bool alive;
	bool isrunning;
	bool isgrowing;
	int direction;
};

struct snake_game *create_snake_game(void);
int init_game(struct snake_game *game);
int snake_game_run(struct snake_game *game);
int update_snake_game(struct snake_game *game);
int move_snake_body(struct snake_game *game);
int generate_food(struct snake_game *game);
int generate_head(struct snake_game *game);
int destroy_snake_game(struct snake_game *game);

#endif
