/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIMovablePanel.hpp"
#include "MinorComponents/Cursor.hpp"
#include "MouseUtilities.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include <ranges>

namespace Forradia
{
    auto GUIMovablePanel::onMouseDown(Uint8 mouseButton) -> bool
    {
        if (!this->getVisible())
            return false;

        auto childComponents{this->getChildComponents()};

        for (auto &childComponent : std::ranges::reverse_view(childComponents))
        {
            if (childComponent->onMouseDown(mouseButton))
            {
                return true;
            }
        }

        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};
        auto draggableArea{this->getDraggableArea()};

        if (draggableArea.contains(mousePosition))
        {
            this->startMove();

            return true;
        }

        return false;
    }

    auto GUIMovablePanel::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        this->stopMove();

        if (!this->getVisible())
        {
            return false;
        }

        auto childComponents{this->getChildComponents()};

        for (auto &childComponent : std::ranges::reverse_view(childComponents))
        {
            if (childComponent->onMouseUp(mouseButton, clickSpeed))
            {
                return true;
            }
        }

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        if (getBounds().contains(mousePos))
        {
            return true;
        }

        return false;
    }

    auto GUIMovablePanel::updateDerived() -> void
    {
        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};
        auto draggableArea{this->getDraggableArea()};

        if (draggableArea.contains(mousePosition))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }

        if (getIsBeingMoved())
        {
            auto newPosition{getMoveStartingPosition() + mousePosition -
                             getMoveStartingMousePosition()};
            this->setPosition(newPosition);
        }
    }

    auto GUIMovablePanel::startMove() -> void
    {
        m_isBeingMoved = true;
        m_moveStartingPosition = this->getBounds().getPosition();
        m_moveStartingMousePosition = getNormalizedMousePosition(SDLDevice::instance().getWindow());
    }

    auto GUIMovablePanel::stopMove() -> void
    {
        m_isBeingMoved = false;
    }

    auto GUIMovablePanel::getDraggableArea() const -> RectF
    {
        // Set the draggable area to the bounds of this panel as default. This can be overridden
        // by derived classes.
        return this->getBounds();
    }
}
