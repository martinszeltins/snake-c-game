#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include "game.h"
#include "input.h"
#include "renderer.h"

struct game *game_create(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);

    struct game *game = NULL;
    game = (struct game *) malloc(sizeof(struct game));

	bzero(game, sizeof(struct game));

    return game;
}

int game_init(struct game *game)
{
	game->speed = 100;

	if (game->screen_width == 0) {
		game->screen_width = WINDOW_WIDTH;
		game->screen_height = WINDOW_HEIGHT;
	}

    game->grid_width = 25;
	
    if (game->screen_width % game->grid_width != 0) {
		game->grid_width++;
	}

    game->grid_height = game->grid_width;
	game->size = 1;
    game->body = (struct game_point*) malloc(sizeof(struct game_point) * 512);
    game->is_alive = true;
	game->is_running = true;
	game->isgrowing = false;
	game->direction = SDIR_LEFT;

	if (game->fps == 0) {
		game->fps = FRAMERATE;
	}

	game->window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->screen_width,
        game->screen_height,
        0
    );

	char title[64];
    
    sprintf(title, "Score: %", game->size);
    SDL_SetWindowTitle(game->window, title);

	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetWindowResizable(game->window, SDL_FALSE);

	generate_head(game);
	generate_food(game);

	return 0;
}

int game_run(struct game *game)
{
    game_init(game);

    float ms_per_frame = 1000.0f / game->fps;

	Uint32 ms_per_move = 200;
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	Uint32 frame_time_stamp;
	Uint32 move_time_stamp;
	Uint32 frame_count = 0;

	move_time_stamp = frame_time_stamp = SDL_GetTicks();

    while (game->is_running) {
		frame_start = SDL_GetTicks();

        input_handle(game);
		render_game(game);

		if (frame_start - move_time_stamp > ms_per_move - game->speed) {
			update_game(game);
			move_time_stamp = frame_start;
		}

		frame_end = SDL_GetTicks();
		frame_count++;
		frame_duration = frame_end - frame_start;

		if (frame_end - frame_time_stamp >= 1000) {
			char title[64];
            sprintf(title, "Score: %", game->size);

            SDL_SetWindowTitle(game->window, title);
			frame_count = 0;
			frame_time_stamp = frame_end;
		}

		if (frame_duration < ms_per_frame) {
			float delay_time = ms_per_frame - frame_duration;
			float floor_time = floor(delay_time);

			if (delay_time - floor_time >= 0.5f) {
				floor_time += 1.0;
            }

			SDL_Delay(floor_time);
		}
    }

    game_terminate(game);

    return 0;
}

int update_game(struct game *game)
{
	if (!game->is_alive) return 0;

	move_snake_body(game);

	if (game->body[0].x == game->food.x && game->body[0].y == game->food.y) {
		game->isgrowing = true;
		generate_food(game);
	}

	for (int i = 1; game->is_alive && i < game->size; i++) {
		if (game->body[0].x == game->body[i].x && game->body[0].y == game->body[i].y) {
			game->is_alive = false;
			printf("======== Game over ========\n");
			printf("Score: %d.\n", game->size);
			printf("Press 'ENTER' to restart.\n");
		}
	}

	return 0;
}

int move_snake_body(struct game *game)
{
	if (game->isgrowing && game->size < 512) {
		++game->size;
		game->isgrowing = false;

		if (game->size % 5 == 0) {
			game->speed += 20;
		}
	}

	for (int i = game->size-1; i > 0; i--) {
		game->body[i] = game->body[i-1];
	}

	/* Move snake's head */
	switch (game->direction) {
        case SDIR_DOWN:	
            game->body[0].y += 1;
            break;
	
        case SDIR_UP:
            game->body[0].y -= 1;
            break;
	
        case SDIR_RIGHT:
            game->body[0].x += 1;
            break;

        case SDIR_LEFT:
            game->body[0].x -= 1;
            break;

        default:
            break;
	}

	if (game->body[0].x < 0) {
		game->body[0].x = game->grid_width-1;
	}

	if (game->body[0].x > game->grid_width-1) {
		game->body[0].x = 0;
	}

	if (game->body[0].y < 0) {
		game->body[0].y = game->grid_width-1;
	}

	if (game->body[0].y > game->grid_width-1) {
		game->body[0].y = 0;
	}

	return 0;
}

int generate_food(struct game *game)
{
	int limit_x = game->grid_width;
	int limit_y = game->grid_height;
	bool regen;

	do {
		game->food.x = rand() % limit_x;
		game->food.y = rand() % limit_y;

		regen = false;

		for (int i = 0; i < game->size; i++) {
			if (game->food.x == game->body[i].x && game->food.y == game->body[i].y) {
				regen = true;
			}
		}

	} while (regen);
    
	return 0;
}

int generate_head(struct game *game)
{
	int limit_x = game->grid_width;
	int limit_y = game->grid_height;

	game->body[0].x = SDL_GetTicks() % limit_x;
	game->body[0].y = SDL_GetTicks() % limit_y;

	return 0;
}

int game_terminate(struct game *game)
{
    if (game == NULL) return 0;

    SDL_DestroyWindow(game->window);
	SDL_DestroyRenderer(game->renderer);
    free(game->body);
    free(game);
    
    return 0;
}

int change_direction(struct game *game, int key)
{
	switch (key) {
        case SDLK_w:
        case SDLK_UP:
            if (game->direction != SDIR_DOWN || game->size == 1) {
                game->direction = SDIR_UP;
            }
            break;
	
        case SDLK_s:
        case SDLK_DOWN:
            if (game->direction != SDIR_UP || game->size == 1) {
                game->direction = SDIR_DOWN;
            }
            break;

        case SDLK_a:
        case SDLK_LEFT:
            if (game->direction != SDIR_RIGHT || game->size == 1) {
                game->direction = SDIR_LEFT;
            }
            break;

        case SDLK_d:
        case SDLK_RIGHT:
            if (game->direction != SDIR_LEFT || game->size == 1) {
                game->direction = SDIR_RIGHT;
            }
            break;

        default:
            break;
	};

	return 0;
}

int game_reset(struct game *game)
{
    game->is_alive = true;
    game->size = 1;
    game->speed = 100;
}