/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIScrollableFrame.hpp"
#include "CanvasUtilities.hpp"
#include "GUI.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
auto GUIScrollableFrame::Render() const -> void {
  if (!this->GetVisible())
    return;

  auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};
  glEnable(GL_SCISSOR_TEST);
  auto bounds{GetBounds()};

  // Note: origin is bottom-left
  auto x{bounds.x * canvasSize.width};
  auto y{bounds.y * canvasSize.height};
  auto width{bounds.width * canvasSize.width};
  auto height{bounds.height * canvasSize.height};
  glScissor(x, canvasSize.height - y - height, width, height);

  this->RenderDerived();

  auto childComponents{this->GetChildComponents()};

  for (auto component : childComponents)
    component->Render();

  glDisable(GL_SCISSOR_TEST);
}
}
