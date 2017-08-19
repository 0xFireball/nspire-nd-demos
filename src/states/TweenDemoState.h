
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"
#include "../sprites/Ball.h"

class TweenDemoState : public BaseDemoState {
public:
    float mg = 40;
    std::shared_ptr<NTweenManager> tweenManager;
    std::shared_ptr<Ball> ball;
    bool side = false;
    std::shared_ptr<NTween> ballTween;
    
    virtual void create() {
        ball = std::make_shared<Ball>(mg, mg);
        ball->vel.set(0, 0);
        add(ball);

        tweenManager = std::make_shared<NTweenManager>();
        this->add(tweenManager);

        BaseDemoState::create();
    }

    virtual void update(float dt) {
        if (!ballTween || ballTween->done) {
            ballTween = tweenManager->tween(
                tweenBall(ball->x, side ? mg : game->width - mg), 1.0f);
            side = !side;
        }

        BaseDemoState::update(dt);
    }

    std::shared_ptr<NTween> tweenBall(float &v, float e) {
        return std::make_shared<NTween>(v, e,
            EaseFunctions::EASE_QUAD_IN);
    }
};
