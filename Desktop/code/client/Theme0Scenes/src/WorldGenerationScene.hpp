/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
class WorldGenerationScene : public IScene {
 protected:
  virtual void OnEnterDerived() override;
};
}