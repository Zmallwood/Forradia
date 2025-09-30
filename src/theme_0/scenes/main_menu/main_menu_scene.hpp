/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "core/scenes_core/i_scene.hpp"

namespace Forradia {
  class MainMenuScene : public IScene {
  protected:
    void InitializeDerived() override;

    void UpdateDerived() override;

    void RenderDerived() const override;
  };
}
