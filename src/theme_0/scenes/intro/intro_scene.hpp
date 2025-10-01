/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/scenes_core/i_scene.hpp"

namespace forr {
  class GUIComponent;

  class IntroScene : public IScene {
  protected:
    void InitializeDerived() override;

    void OnEnterDerived() override;

    void UpdateDerived() override;

    void RenderDerived() const override;

  private:
    s_ptr<GUIComponent> m_startText;
  };
}
