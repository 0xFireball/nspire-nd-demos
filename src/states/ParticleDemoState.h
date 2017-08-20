
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"
#include "../sprites/Ball.h"

class ParticleDemoState : public BaseDemoState {
public:
    std::shared_ptr<NParticleEmitter> emitter;
    std::shared_ptr<Ball> ball;

    virtual void create() {
        ball = std::make_shared<Ball>(game->width / 2, game->height / 2);
        add(ball);

        emitter = std::make_shared<NParticleEmitter>(40);
        add(emitter);

        BaseDemoState::create();
    }

    virtual void update(float dt) {
        auto ballCenter = ball->getCenter();
        emitter->emitSquare(ballCenter.getX(), ballCenter.getY(), 4, NParticleEmitter::velocity_spread(50),
            NColor(0.7, 0.7, 0.1), 1.0f);

        BaseDemoState::update(dt);
    }
};
