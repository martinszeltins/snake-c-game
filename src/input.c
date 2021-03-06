#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "input.h"

int input_handle(struct game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->is_running = false;
		}

		if (event.type == SDL_KEYDOWN) {
			int key = event.key.keysym.sym;

			switch (key) {
                case SDLK_ESCAPE:
                    game->is_running = false;
                    break;

                case SDLK_q:
                    game->is_running = false;
                    break;

                case SDLK_KP_ENTER:
                case 0x0D:
                    if (!game->is_alive) {
                        game_reset(game);
				    }

                    break;

                default:
                    change_direction(game, key);
            }
		}
	}

	return 0;
}