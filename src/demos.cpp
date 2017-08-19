
#include <memory>

#include "deps.h"
#include "reg.h"

#include "states/gamestate.h"

int main(int argc, char **argv) {
    auto game = std::make_shared<NGame>();

    game->platform_init(argc, argv);

    // Initialize NGame at max screen size, 30FPS target
    game->init(0, 0, 30);
    Reg::game = game;
    game->switch_state(new GameState());
    game->start();

    return 0;
}
