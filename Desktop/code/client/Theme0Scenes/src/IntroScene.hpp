/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia {
class GUIComponent;
}

namespace Forradia::Theme0 {
class IntroScene : public IScene {
 protected:
  virtual void InitializeDerived() override;

  virtual void OnEnterDerived() override;

  virtual void UpdateDerived() override;

  virtual void RenderDerived() const override;

 private:
  SharedPtr<GUIComponent> m_startText; ///< The text component for the start text.
};
}