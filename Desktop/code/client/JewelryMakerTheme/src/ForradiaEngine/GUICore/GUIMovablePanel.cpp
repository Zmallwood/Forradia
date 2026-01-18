/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIMovablePanel.hpp"
#include <ranges>
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"

namespace ForradiaEngine
{
    auto GUIMovablePanel::onMouseDown(Uint8 mouseButton) -> bool
    {
        If (!this->getVisible())
        {
            return false;
        }

        auto childComponents{this->getChildComponents()};

        Loop (auto &childComponent : std::ranges::reverse_view(childComponents))
        {
            If (childComponent->onMouseDown(mouseButton))
            {
                return true;
            }
        }

        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};
        auto draggableArea{this->getDraggableArea()};

        If (draggableArea.contains(mousePosition))
        {
            this->startMove();

            return true;
        }

        return false;
    }

    auto GUIMovablePanel::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        this->stopMove();

        If (!this->getVisible())
        {
            return false;
        }

        auto childComponents{this->getChildComponents()};

        Loop (auto &childComponent : std::ranges::reverse_view(childComponents))
        {
            If (childComponent->onMouseUp(mouseButton, clickSpeed))
            {
                return true;
            }
        }

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        If (getBounds().contains(mousePos))
        {
            return true;
        }

        return false;
    }

    auto GUIMovablePanel::updateDerived() -> void
    {
        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};
        auto draggableArea{this->getDraggableArea()};

        If (draggableArea.contains(mousePosition))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }

        If (getIsBeingMoved())
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
