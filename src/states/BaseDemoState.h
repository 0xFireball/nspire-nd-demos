
#pragma once

#include "../deps.h"

class BaseDemoState : public NState {
public:
    virtual void update(float dt) {
        bool esc = this->game->keys->pressed(SDLK_ESCAPE);
        if (esc) {
            this->game->quit();
        }

        bool nextDemo = this->game->keys->justPressed(SDLK_TAB, game->get_frame_count());
        if (nextDemo) {
            Reg::currentDemo++;
            Reg::currentDemo %= (int)Reg::demoStates.size();
            game->switch_state(Reg::demoStates[Reg::currentDemo], false);
        }

        NState::update(dt);
    }
};
