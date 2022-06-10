#include "game.h"

int main(int argc, char **argv)
{
    struct game *game = create_game();

    game_init(game);
    game_run(game);
    game_terminate(game);

    return 0;
}
