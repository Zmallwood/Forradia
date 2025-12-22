/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIMovablePanel.hpp"
#include "Cursor.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include <ranges>

namespace Forradia {
    auto GUIMovablePanel::OnMouseDown(Uint8 mouseButton) -> bool {
        if (!this->GetVisible())
            return false;

        auto childComponents{this->GetChildComponents()};

        for (auto &childComponent : std::ranges::reverse_view(childComponents))
            if (childComponent->OnMouseDown(mouseButton))
                return true;

        auto mousePosition{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};
        auto draggableArea{this->GetDraggableArea()};
        if (draggableArea.Contains(mousePosition)) {
            this->StartMove();
            return true;
        }

        return false;
    }

    auto GUIMovablePanel::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool {
        this->StopMove();

        if (!this->GetVisible())
            return false;

        auto childComponents{this->GetChildComponents()};

        for (auto &childComponent : std::ranges::reverse_view(childComponents))
            if (childComponent->OnMouseUp(mouseButton, clickSpeed))
                return true;

        auto mousePos{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};
        if (GetBounds().Contains(mousePos)) {
            return true;
        }

        return false;
    }

    auto GUIMovablePanel::UpdateDerived() -> void {
        auto mousePosition{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};
        auto draggableArea{this->GetDraggableArea()};

        if (draggableArea.Contains(mousePosition)) {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }

        if (GetIsBeingMoved()) {
            auto newPosition{GetMoveStartingPosition() + mousePosition -
                             GetMoveStartingMousePosition()};
            this->SetPosition(newPosition);
        }
    }

    auto GUIMovablePanel::StartMove() -> void {
        m_isBeingMoved = true;
        m_moveStartingPosition = this->GetBounds().GetPosition();
        m_moveStartingMousePosition =
            GetNormallizedMousePosition(SDLDevice::Instance().GetWindow());
    }

    auto GUIMovablePanel::StopMove() -> void {
        m_isBeingMoved = false;
    }

    auto GUIMovablePanel::GetDraggableArea() const -> RectF {
        // Set the draggable area to the bounds of this panel as default. This can be overridden
        // by derived classes.
        return this->GetBounds();
    }
}
