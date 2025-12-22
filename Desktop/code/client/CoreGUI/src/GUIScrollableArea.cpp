/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIScrollableArea.hpp"
#include "CanvasUtilities.hpp"
#include "Cursor.hpp"
#include "CursorStyles.hpp"
#include "GUI.hpp"
#include "Image2DRenderer.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include <GL/gl.h>

namespace Forradia
{
    auto GUIScrollableArea::OnMouseDown(Uint8 mouseButton) -> bool
    {
        if (!this->GetVisible())
            return false;

        auto upArrowBounds{this->GetUpArrowBounds()};
        auto downArrowBounds{this->GetDownArrowBounds()};
        auto sliderBounds{this->GetSliderBounds()};

        auto mousePos{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};

        if (upArrowBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
            m_scrollPosition -= k_scrollbarMoveStepSize;
        }
        else if (downArrowBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
            m_scrollPosition += k_scrollbarMoveStepSize;
        }
        else if (sliderBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
            m_movingSlider = true;
            m_sliderStartMoveYPos = m_scrollPosition;
            m_sliderStartMoveMouseYPos = mousePos.y;
        }

        return false;
    }

    auto GUIScrollableArea::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (!this->GetVisible())
            return false;

        m_movingSlider = false;

        auto mousePos{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};
        if (GetBounds().Contains(mousePos))
        {
            return true;
        }

        return false;
    }

    auto GUIScrollableArea::UpdateDerived() -> void
    {
        GUIComponent::UpdateDerived();

        auto mousePos{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};

        auto upArrowBounds{this->GetUpArrowBounds()};
        auto downArrowBounds{this->GetDownArrowBounds()};
        auto sliderBounds{this->GetSliderBounds()};

        auto bounds{GUIComponent::GetBounds()};

        if (upArrowBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else if (downArrowBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else if (sliderBounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }

        if (m_movingSlider)
        {
            auto delta{(mousePos.y - m_sliderStartMoveMouseYPos)};
            m_scrollPosition = m_sliderStartMoveYPos +
                               delta / (bounds.height - k_sliderHeight - 2 * k_scrollbarWidth);
        }
        m_scrollPosition = std::max(0.0F, m_scrollPosition);
        m_scrollPosition = std::min(1.0F, m_scrollPosition);
    }

    auto GUIScrollableArea::Render() const -> void
    {
        if (!this->GetVisible())
            return;

        auto canvasSize{GetCanvasSize(SDLDevice::Instance().GetWindow())};
        glEnable(GL_SCISSOR_TEST);
        auto bounds{GUIComponent::GetBounds()};

        // Note: origin is bottom-left
        auto xPos{bounds.x * canvasSize.width};
        auto yPos{bounds.y * canvasSize.height};
        auto width{bounds.width * canvasSize.width};
        auto height{bounds.height * canvasSize.height};
        glScissor(xPos, canvasSize.height - yPos - height, width, height);

        this->RenderDerived();

        auto childComponents{this->GetChildComponents()};

        for (const auto &component : childComponents)
            component->Render();

        glDisable(GL_SCISSOR_TEST);

        auto upArrowBounds{this->GetUpArrowBounds()};
        auto downArrowBounds{this->GetDownArrowBounds()};

        Image2DRenderer::Instance().DrawImageByName(
            k_renderIDUpArrow, "GUIScrollbarUpArrow", upArrowBounds.x, upArrowBounds.y,
            upArrowBounds.width, upArrowBounds.height, true);

        Image2DRenderer::Instance().DrawImageByName(
            k_renderIDDownArrow, "GUIScrollbarDownArrow", downArrowBounds.x, downArrowBounds.y,
            downArrowBounds.width, downArrowBounds.height, true);

        auto sliderBounds{this->GetSliderBounds()};

        Image2DRenderer::Instance().DrawImageByName(k_renderIDSlider, "GUIScrollbarSlider",
                                                    sliderBounds.x, sliderBounds.y,
                                                    sliderBounds.width, sliderBounds.height, true);
    }

    auto GUIScrollableArea::GetBounds() const -> RectF
    {
        auto bounds{GUIComponent::GetBounds()};
        bounds.y -= m_scrollPosition * bounds.height;
        return bounds;
    }

    auto GUIScrollableArea::GetUpArrowBounds() const -> RectF
    {
        auto bounds{GUIComponent::GetBounds()};
        auto upArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth, bounds.y,
                                 k_scrollbarWidth, k_scrollbarWidth}};
        return upArrowBounds;
    }

    auto GUIScrollableArea::GetDownArrowBounds() const -> RectF
    {
        auto bounds{GUIComponent::GetBounds()};
        auto downArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth,
                                   bounds.y + bounds.height - k_scrollbarWidth, k_scrollbarWidth,
                                   k_scrollbarWidth}};
        return downArrowBounds;
    }

    auto GUIScrollableArea::GetSliderBounds() const -> RectF
    {
        auto bounds{GUIComponent::GetBounds()};
        auto sliderX{bounds.x + bounds.width - k_scrollbarWidth};
        auto sliderWidth{k_scrollbarWidth};
        auto sliderHeight{k_sliderHeight};

        auto sliderY{bounds.y + k_scrollbarWidth +
                     (bounds.height - sliderHeight - 2 * k_scrollbarWidth) * m_scrollPosition};
        return {sliderX, sliderY, sliderWidth, sliderHeight};
    }
}
