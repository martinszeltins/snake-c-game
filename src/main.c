#include "game.h"

int main(int argc, char **argv)
{
    struct game *game = game_create();
    
    game_run(game);

    return 0;
}
