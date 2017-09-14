
#pragma once

#include "../deps.h"
#include "../sprites/Ball.h"
#include "BaseDemoState.h"

class IntroState : public BaseDemoState {
public:
  virtual void create() {
    auto ball = std::make_shared<Ball>(game->width / 2, game->height / 2);
    add(ball);

    BaseDemoState::create();
  }
};
