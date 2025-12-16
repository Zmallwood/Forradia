/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0 {
class PlayScene : public IScene {
 protected:
  virtual void InitializeDerived() override;

  virtual void RenderDerived() const override;
};
}