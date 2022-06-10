#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "controller.h"

int handle_input(struct snake_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->isrunning = false;
		}

		if (event.type == SDL_KEYDOWN) {
			int key = event.key.keysym.sym;

			switch (key) {
                case SDLK_ESCAPE:
                    game->isrunning = false;
                    break;

                case SDLK_q:
                    game->isrunning = false;
                    break;

                case SDLK_KP_ENTER:
                case 0x0D:
                    if (!game->alive) {
                        game->alive = true;
                        game->size = 1;
                        game->speed = 0.1;
				    }

                    break;

                default:
                    change_direction(game, key);
            }
		}
	}

	return 0;
}

int change_direction(struct snake_game *game, int type)
{
	switch (type) {
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
