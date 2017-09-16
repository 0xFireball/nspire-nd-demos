
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"

class ScrollCameraState : public BaseDemoState {
private:
  std::shared_ptr<NSprite> _player;
  static const int PLAYER_SPEED = 100;
  std::shared_ptr<NGroup<NEntity>> _things;
  std::unique_ptr<NCollision> collision;

public:
  virtual void create() {
    _player = std::make_shared<NSprite>(game->width / 2, game->height / 2);
    _player->makeGraphic(10, 10, NColor::fromRGBInt(252, 233, 32));
    add(_player);

    _things = std::make_shared<NGroup<NEntity>>();

    auto box1 = std::make_shared<NSprite>(40, 40);
    box1->makeGraphic(20, 20, NColor::fromRGBInt(201, 193, 52));
    _things->add(box1);

    auto box2 = std::make_shared<NSprite>(160, 70);
    box2->makeGraphic(35, 35, NColor::fromRGBInt(137, 134, 74));
    box2->immovable = true;
    _things->add(box2);

    add(_things);

    prepareCamera();

    collision =
        std::make_unique<NCollision>(Rect(0, 0, game->width, game->height));

    BaseDemoState::create();
  }

  void movement(float dt) {
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
  }

  virtual void update(float dt) {
    movement(dt);

    // collide with things
    collision->collide(_player, _things);

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
