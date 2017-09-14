
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"

class ScrollCameraState : public BaseDemoState {
private:
  std::shared_ptr<NSprite> _player;
  static const int PLAYER_SPEED = 100;

public:
  virtual void create() {
    _player = std::make_shared<NSprite>(game->width / 2, game->height / 2);
    _player->makeGraphic(10, 10, NColor::fromRGBInt(252, 233, 32));
    add(_player);

    auto box = std::make_shared<NSprite>(40, 40);
    box->makeGraphic(20, 20, NColor::fromRGBInt(216, 205, 86));
    add(box);

    prepareCamera();

    BaseDemoState::create();
  }

  virtual void update(float dt) {
    std::vector<int> upKeys{SDLK_UP, SDLK_8};
    bool up = Reg::game->keys->anyPressed(upKeys);
    std::vector<int> downKeys{SDLK_DOWN, SDLK_2};
    bool down = Reg::game->keys->anyPressed(downKeys);
    std::vector<int> leftKeys{SDLK_LEFT, SDLK_4};
    bool left = Reg::game->keys->anyPressed(leftKeys);
    std::vector<int> rightKeys{SDLK_RIGHT, SDLK_6};
    bool right = Reg::game->keys->anyPressed(rightKeys);

    if (up && down) {
      up = down = false;
    }
    if (left && right) {
      left = right = false;
    }

    if (up) {
      _player->y -= PLAYER_SPEED * dt;
    }
    if (down) {
      _player->y += PLAYER_SPEED * dt;
    }
    if (left) {
      _player->x -= PLAYER_SPEED * dt;
    } else if (right) {
      _player->x += PLAYER_SPEED * dt;
    }

    BaseDemoState::update(dt);
  }

  virtual void onPausing() {
    // reset camera
    game->camera.reset();

    BaseDemoState::onPausing();
  }

  virtual void onResuming() {
    prepareCamera();

    BaseDemoState::onResuming();
  }

  void prepareCamera() {
    game->camera.follow(_player);
    game->camera.followStyle = NCameraFollowStyle::LOCKON;
  }
};
