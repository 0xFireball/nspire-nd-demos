
#pragma once

#include "../deps.h"
#include "../reg.h"

class Ball : public NSprite {
private:
  static const int MOVEMENT_SPEED = 80;

public:
  Vec2 vel;

  Ball(int x, int y) : NSprite(x, y), vel(Vec2(this->MOVEMENT_SPEED)) {
    loadGraphic("ball.bmp.tns", 16, 16);
    std::vector<int> blink_frames{0, 1};
    this->animation.add("blink", blink_frames, 2);
  }

  virtual void update(float dt) {
    this->setPosition(this->getPosition() + this->vel * dt);

    // bounce off walls
    Vec2 pos = this->getPosition();
    if (pos.getX() < 0) {
      this->x = 0;
      this->vel.setX(-this->vel.getX());
    }
    if (pos.getX() + this->width > Reg::game->width) {
      this->x = Reg::game->width - this->width;
      this->vel.setX(-this->vel.getX());
    }
    if (pos.getY() < 0) {
      this->y = 0;
      this->vel.setY(-this->vel.getY());
    }
    if (pos.getY() + this->width > Reg::game->height) {
      this->y = Reg::game->height - this->width;
      this->vel.setY(-this->vel.getY());
    }

    this->animation.play("blink");

    NSprite::update(dt);
  }
};
