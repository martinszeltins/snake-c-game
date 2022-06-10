#include "game.h"

int main(int argc, char **argv)
{
    struct game *game = game_create();

    game_init(game);
    game_run(game);
    game_terminate(game);

    return 0;
}
