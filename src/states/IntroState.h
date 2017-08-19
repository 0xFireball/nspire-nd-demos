
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"
#include "../sprites/Ball.h"

class IntroState : public BaseDemoState {
public:
    virtual void create() {
        auto ball = std::make_shared<Ball>(game->width / 2, game->height / 2);
        add(ball);

        BaseDemoState::create();
    }
};
