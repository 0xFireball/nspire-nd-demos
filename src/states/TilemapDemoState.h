
#pragma once

#include "../deps.h"
#include "BaseDemoState.h"

int TILEMAP_TILES[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

class TilemapDemoState : public BaseDemoState {
private:
  std::shared_ptr<NSprite> _player;
  std::shared_ptr<NTilemap> _map;
  std::unique_ptr<NCollision> collision;
  static const int PLAYER_SPEED = 60;

public:
  virtual void create() {
    _player = std::make_shared<NSprite>(60, 60);
    _player->makeGraphic(10, 10, NColor::fromRGBInt(252, 233, 32));
    add(_player);

    auto tileset = std::make_shared<NTileset>("pxn_tileset.bmp.tns", 16, 16);
    _map = std::make_shared<NTilemap>(Vec2(0, 0), TILEMAP_TILES, 20, 15, tileset);
    add(_map);

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

    // collisions
    collision->collide(_player, _map);

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
