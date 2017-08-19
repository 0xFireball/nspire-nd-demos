
#include <memory>

#include "deps.h"
#include "reg.h"

#include "states/IntroState.h"

int main(int argc, char **argv) {
    auto game = std::make_shared<NGame>();

    game->platform_init(argc, argv);

    Reg::demoStates.push_back(std::make_shared<IntroState>());

    // Initialize NGame at max screen size, 30FPS target
    game->init(0, 0, 30);
    Reg::game = game;
    game->switch_state(Reg::demoStates[Reg::currentDemo]);
    // game->switch_state(std::make_shared<IntroState>());
    game->start();

    return 0;
}
