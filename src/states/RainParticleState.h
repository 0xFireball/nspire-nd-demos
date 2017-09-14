
#pragma once

#include "../deps.h"
#include "../sprites/Ball.h"
#include "BaseDemoState.h"

class RainParticleState : public BaseDemoState {
public:
  std::shared_ptr<NParticleEmitter> emitter;
  float rainDiv = 32;

  virtual void create() {
    this->setClearColor(NColor(0.95, 0.95, 0.95));

    emitter = std::make_shared<NParticleEmitter>(80);
    add(emitter);

    BaseDemoState::create();
  }

  virtual void update(float dt) {
    // for (int i = 0; i < Reg::game->width / rainDiv; i++) {
    //   for (int j = 0; j < Reg::game->height / rainDiv; j++) {
    //     if (RNG::randf() < 0.2) {
    //       float xVar = (RNG::randf() * rainDiv * 2) - rainDiv;
    //       float yVar = (RNG::randf() * rainDiv * 2) - rainDiv;
    //       emitter->emitSquare(i * rainDiv + xVar, j * rainDiv + yVar, 3,
    //                           NParticleEmitter::velocity_spread(40, -20, 20),
    //                           NColor::rand_col(0.89, 0.05, 0.35, 0.05),
    //                           RNG::randf() * 3. + 1.);
    //     }
    //   }
    // }
    emitter->emitSquare(
        (1 + RNG::randf()) * (game->width / 2), RNG::randf() * game->height, 3,
        NParticleEmitter::velocity_spread(20, -80, 80),
        NColor::rand_col(0.89, 0.05, 0.35, 0.05), RNG::randf() * 4. + 1.);

    BaseDemoState::update(dt);
  }
};
