/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIScrollableArea.hpp"
#include "CanvasUtilities.hpp"
#include "Cursor.hpp"
#include "CursorStyles.hpp"
#include "GUI.hpp"
#include "Image2DRenderer.hpp"
#include "Mouse/MouseInput.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
  auto GUIScrollableArea::UpdateDerived() -> void {
    GUIComponent::UpdateDerived();

    auto mousePos{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

    auto upArrowBounds{this->GetUpArrowBounds()};
    auto downArrowBounds{this->GetDownArrowBounds()};
    auto sliderBounds{this->GetSliderBounds()};

    if (upArrowBounds.Contains(mousePos)) {
      _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        m_scrollPosition -= 0.05F;
      }
    } else if (downArrowBounds.Contains(mousePos)) {
      _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        m_scrollPosition += 0.05F;
      }
    } else if (sliderBounds.Contains(mousePos)) {
      _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        m_movingSlider = true;
        m_sliderStartMoveYPos = m_scrollPosition;
        m_sliderStartMoveMouseYPos = mousePos.y;
      }
    }
    if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenReleased()) {
      m_movingSlider = false;
    }

    if (m_movingSlider) {
      auto delta{(mousePos.y - m_sliderStartMoveMouseYPos) / GUIComponent::GetBounds().height};
      m_scrollPosition = m_sliderStartMoveYPos + delta;
    }
    m_scrollPosition = std::max(0.0F, m_scrollPosition);
    m_scrollPosition = std::min(1.0F, m_scrollPosition);
  }

  auto GUIScrollableArea::Render() const -> void {
    if (!this->GetVisible())
      return;

    auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};
    glEnable(GL_SCISSOR_TEST);
    auto bounds{GUIComponent::GetBounds()};

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

    auto upArrowBounds{this->GetUpArrowBounds()};
    auto downArrowBounds{this->GetDownArrowBounds()};

    _<Image2DRenderer>().DrawImageByName(k_renderIDUpArrow, "GUIScrollbarUpArrow", upArrowBounds.x,
                                         upArrowBounds.y, upArrowBounds.width, upArrowBounds.height,
                                         true);

    _<Image2DRenderer>().DrawImageByName(k_renderIDDownArrow, "GUIScrollbarDownArrow",
                                         downArrowBounds.x, downArrowBounds.y,
                                         downArrowBounds.width, downArrowBounds.height, true);

    auto sliderBounds{this->GetSliderBounds()};

    _<Image2DRenderer>().DrawImageByName(k_renderIDSlider, "GUIScrollbarSlider", sliderBounds.x,
                                         sliderBounds.y, sliderBounds.width, sliderBounds.height,
                                         true);
  }

  auto GUIScrollableArea::GetBounds() const -> RectF {
    auto bounds{GUIComponent::GetBounds()};
    bounds.y -= m_scrollPosition * bounds.height;
    return bounds;
  }

  auto GUIScrollableArea::GetUpArrowBounds() const -> RectF {
    auto bounds{GUIComponent::GetBounds()};
    auto upArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth, bounds.y, k_scrollbarWidth,
                             k_scrollbarWidth}};
    return upArrowBounds;
  }

  auto GUIScrollableArea::GetDownArrowBounds() const -> RectF {
    auto bounds{GUIComponent::GetBounds()};
    auto downArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth,
                               bounds.y + bounds.height - k_scrollbarWidth, k_scrollbarWidth,
                               k_scrollbarWidth}};
    return downArrowBounds;
  }

  auto GUIScrollableArea::GetSliderBounds() const -> RectF {
    auto bounds{GUIComponent::GetBounds()};
    auto sliderX{bounds.x + bounds.width - k_scrollbarWidth};
    auto sliderWidth{k_scrollbarWidth};
    auto sliderHeight{0.08F};

    auto sliderY{bounds.y + k_scrollbarWidth +
                 (bounds.height - sliderHeight - 2 * k_scrollbarWidth) * m_scrollPosition};
    return {sliderX, sliderY, sliderWidth, sliderHeight};
  }
}
