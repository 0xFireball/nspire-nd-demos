
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"
#include "../sprites/Ball.h"

class TweenDemoState : public BaseDemoState {
public:
    virtual void create() {
        float mg = 40;
        auto ball = std::make_shared<Ball>(mg, mg);
        ball->vel.set(0, 0);
        add(ball);

        auto tweenManager = std::make_shared<NTweenManager>();
        this->add(tweenManager);
        
        tweenManager->tween(
            ballTween(ball->x, game->width - mg), 1.0f, tweenDone);

        BaseDemoState::create();
    }

    static void tweenDone(NTweenParams&) {
        // TODO
    }

    std::shared_ptr<NTween> ballTween(float &v, float e) {
        return std::make_shared<NTween>(v, e,
            EaseFunctions::EASE_QUAD_IN);
    }
};
