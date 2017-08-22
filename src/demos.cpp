
#include <memory>

#include "deps.h"
#include "reg.h"

#include "states/IntroState.h"
#include "states/TweenDemoState.h"
#include "states/ParticleDemoState.h"
#include "states/SceneDemoState.h"

int main(int argc, char **argv) {
    auto game = std::make_shared<NGame>();

    // set up system for game
    game->platform_init(argc, argv);

    Reg::demoStates.push_back(std::make_shared<IntroState>());
    Reg::demoStates.push_back(std::make_shared<TweenDemoState>());
    Reg::demoStates.push_back(std::make_shared<ParticleDemoState>());
    Reg::demoStates.push_back(std::make_shared<SceneDemoState>());

    // Initialize NGame at max screen size, 30FPS target
    game->init(0, 0, 30);
    Reg::game = game;
    game->switch_state(Reg::demoStates[Reg::currentDemo]);
    // game->switch_state(std::make_shared<IntroState>());
    game->start();

    // clean up
    game->platform_deinit();

    return 0;
}
