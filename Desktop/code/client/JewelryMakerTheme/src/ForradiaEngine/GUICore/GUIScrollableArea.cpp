/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIScrollableArea.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/MinorComponents/CursorStyles.hpp"
#include "GUI.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"

namespace ForradiaEngine
{
    auto GUIScrollableArea::onMouseDown(Uint8 mouseButton) -> bool
    {
        if (!this->getVisible())
        {
            return false;
        }

        auto upArrowBounds{this->getUpArrowBounds()};
        auto downArrowBounds{this->getDownArrowBounds()};
        auto sliderBounds{this->getSliderBounds()};

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        if (upArrowBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);

            m_scrollPosition -= k_scrollbarMoveStepSize;
        }
        else if (downArrowBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);

            m_scrollPosition += k_scrollbarMoveStepSize;
        }
        else if (sliderBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);

            m_movingSlider = true;
            m_sliderStartMoveYPos = m_scrollPosition;
            m_sliderStartMoveMouseYPos = mousePos.y;
        }

        return false;
    }

    auto GUIScrollableArea::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (!this->getVisible())
        {
            return false;
        }

        m_movingSlider = false;

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        if (getBounds().contains(mousePos))
        {
            return true;
        }

        return false;
    }

    auto GUIScrollableArea::updateDerived() -> void
    {
        GUIComponent::updateDerived();

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto upArrowBounds{this->getUpArrowBounds()};
        auto downArrowBounds{this->getDownArrowBounds()};
        auto sliderBounds{this->getSliderBounds()};

        auto bounds{GUIComponent::getBounds()};

        if (upArrowBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else if (downArrowBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else if (sliderBounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
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

    auto GUIScrollableArea::render() const -> void
    {
        if (!this->getVisible())
        {
            return;
        }

        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};
        glEnable(GL_SCISSOR_TEST);
        auto bounds{GUIComponent::getBounds()};

        // Note: origin is bottom-left
        auto xPos{bounds.x * canvasSize.width};
        auto yPos{bounds.y * canvasSize.height};
        auto width{bounds.width * canvasSize.width};
        auto height{bounds.height * canvasSize.height};
        glScissor(xPos, canvasSize.height - yPos - height, width, height);

        this->renderDerived();

        auto childComponents{this->getChildComponents()};

        for (const auto &component : childComponents)
            component->render();

        glDisable(GL_SCISSOR_TEST);

        auto upArrowBounds{this->getUpArrowBounds()};
        auto downArrowBounds{this->getDownArrowBounds()};

        Image2DRenderer::instance().drawImageByName(
            k_renderIDUpArrow, "GUIScrollbarUpArrow", upArrowBounds.x, upArrowBounds.y,
            upArrowBounds.width, upArrowBounds.height, true);

        Image2DRenderer::instance().drawImageByName(
            k_renderIDDownArrow, "GUIScrollbarDownArrow", downArrowBounds.x, downArrowBounds.y,
            downArrowBounds.width, downArrowBounds.height, true);

        auto sliderBounds{this->getSliderBounds()};

        Image2DRenderer::instance().drawImageByName(k_renderIDSlider, "GUIScrollbarSlider",
                                                    sliderBounds.x, sliderBounds.y,
                                                    sliderBounds.width, sliderBounds.height, true);
    }

    auto GUIScrollableArea::getBounds() const -> RectF
    {
        auto bounds{GUIComponent::getBounds()};
        bounds.y -= m_scrollPosition * bounds.height;

        return bounds;
    }

    auto GUIScrollableArea::getUpArrowBounds() const -> RectF
    {
        auto bounds{GUIComponent::getBounds()};
        auto upArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth, bounds.y,
                                 k_scrollbarWidth, k_scrollbarWidth}};

        return upArrowBounds;
    }

    auto GUIScrollableArea::getDownArrowBounds() const -> RectF
    {
        auto bounds{GUIComponent::getBounds()};
        auto downArrowBounds{RectF{bounds.x + bounds.width - k_scrollbarWidth,
                                   bounds.y + bounds.height - k_scrollbarWidth, k_scrollbarWidth,
                                   k_scrollbarWidth}};

        return downArrowBounds;
    }

    auto GUIScrollableArea::getSliderBounds() const -> RectF
    {
        auto bounds{GUIComponent::getBounds()};
        auto sliderX{bounds.x + bounds.width - k_scrollbarWidth};
        auto sliderWidth{k_scrollbarWidth};
        auto sliderHeight{k_sliderHeight};

        auto sliderY{bounds.y + k_scrollbarWidth +
                     (bounds.height - sliderHeight - 2 * k_scrollbarWidth) * m_scrollPosition};

        return {sliderX, sliderY, sliderWidth, sliderHeight};
    }
}
