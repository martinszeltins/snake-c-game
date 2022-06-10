#include "game.h"

int main(int argc, char **argv)
{
    struct snake_game *snake_game = create_snake_game();

    init_game(snake_game);
    snake_game_run(snake_game);
    destroy_snake_game(snake_game);

    return 0;
}
