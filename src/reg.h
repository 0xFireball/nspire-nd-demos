
#pragma once

#include "deps.h"

struct Reg {
  public:
    static std::shared_ptr<NGame> game;
    static std::vector<std::shared_ptr<NState>> demoStates;
    static int currentDemo;
};
