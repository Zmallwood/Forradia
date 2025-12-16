/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
class MainScene : public IScene {
  virtual void InitializeDerived() override;

  virtual void OnEnterDerived() override;

  virtual void UpdateDerived() override;

  virtual void RenderDerived() const override;
};
}