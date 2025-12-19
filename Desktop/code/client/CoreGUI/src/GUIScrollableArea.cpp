/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIScrollableArea.hpp"
#include "CanvasUtilities.hpp"
#include "GUI.hpp"
#include "Image2DRenderer.hpp"
#include "Mouse/MouseInput.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
  auto GUIScrollableArea::UpdateDerived() -> void {
    GUIComponent::UpdateDerived();

    auto mousePos{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

    auto upArrowBounds{GetUpArrowBounds()};
    auto downArrowBounds{GetDownArrowBounds()};

    if (upArrowBounds.Contains(mousePos)) {
      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        m_scrollPosition -= 0.02F;
      }
    } else if (downArrowBounds.Contains(mousePos)) {
      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        m_scrollPosition += 0.02F;
      }
    }
  }

  auto GUIScrollableArea::Render() const -> void {
    if (!this->GetVisible())
      return;

    auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};
    glEnable(GL_SCISSOR_TEST);
    auto bounds{GetBounds()};

    // Note: origin is bottom-left
    auto x{bounds.x * canvasSize.width};
    auto y{bounds.y * canvasSize.height + m_scrollPosition * bounds.height * canvasSize.height};
    auto width{bounds.width * canvasSize.width};
    auto height{bounds.height * canvasSize.height};
    glScissor(x, canvasSize.height - y - height, width, height);

    this->RenderDerived();

    auto childComponents{this->GetChildComponents()};

    for (auto component : childComponents)
      component->Render();

    glDisable(GL_SCISSOR_TEST);

    auto upArrowBounds{this->GetUpArrowBounds()};
    auto downArrowBounds{this->GetDownArrowBounds()};

    _<Image2DRenderer>().DrawImageByName(k_renderIDUpArrow, "GUIScrollbarUpArrow", upArrowBounds.x,
                                         upArrowBounds.y, upArrowBounds.width, upArrowBounds.height,
                                         true);

    _<Image2DRenderer>().DrawImageByName(k_renderIDDownArrow, "GUIScrollbarDownArrow",
                                         downArrowBounds.x, downArrowBounds.y,
                                         downArrowBounds.width, downArrowBounds.height, true);

    auto sliderX{bounds.x + bounds.width - k_scrollbarWidth};
    auto sliderWidth{k_scrollbarWidth};
    auto sliderHeight{0.1F};

    auto sliderY{bounds.y + upArrowBounds.height +
                 (bounds.height - sliderHeight - 2 * upArrowBounds.height) * m_scrollPosition +
                 m_scrollPosition * bounds.height};

    _<Image2DRenderer>().DrawImageByName(k_renderIDSlider, "GUIScrollbarSlider", sliderX, sliderY,
                                         sliderWidth, sliderHeight, true);
  }

  auto GUIScrollableArea::GetBounds() const -> RectF {
    auto bounds{GUIComponent::GetBounds()};
    bounds.y -= m_scrollPosition * bounds.height;
    return bounds;
  }

  auto GUIScrollableArea::GetUpArrowBounds() const -> RectF {
    auto bounds{GetBounds()};
    auto upArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth,
                             bounds.y + m_scrollPosition * bounds.height, k_scrollbarWidth,
                             k_scrollbarWidth}};
    return upArrowBounds;
  }

  auto GUIScrollableArea::GetDownArrowBounds() const -> RectF {
    auto bounds{GetBounds()};
    auto downArrowBounds{
        RectF{bounds.x + bounds.width - k_scrollbarWidth,
              bounds.y + bounds.height - k_scrollbarWidth + m_scrollPosition * bounds.height,
              k_scrollbarWidth, k_scrollbarWidth}};
    return downArrowBounds;
  }
}
