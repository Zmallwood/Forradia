/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIContainerWindow.hpp"
#include "ContainedObjects.hpp"
#include "GUIScrollableArea.hpp"
#include "GUIWindowTitleBar.hpp"
#include "Image2DRenderer.hpp"
#include "MouseUtilities.hpp"
#include "Object.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0 {
    auto GUIContainerWindow::Initialize(ContainedObjects &containedObjects) -> void {
        m_guiContainerWindowArea = std::make_shared<GUIContainerWindowArea>(this, containedObjects);
        this->AddChildComponent(m_guiContainerWindowArea);
    }

    std::shared_ptr<Object> *GUIContainerWindow::GetObjectPtrPtr(PointF position) {
        return m_guiContainerWindowArea->GetObjectPtrPtr(position);
    }

    auto GUIContainerWindowArea::Initialize(GUIWindow *parentWindow,
                                            ContainedObjects &containedObjects) -> void {
        m_panel = std::make_shared<GUIContainerWindowPanel>(parentWindow, containedObjects);
        this->AddChildComponent(m_panel);
    }

    std::shared_ptr<Object> *GUIContainerWindowArea::GetObjectPtrPtr(PointF position) {
        return m_panel->GetObjectPtrPtr(position);
    }

    auto GUIContainerWindowArea::UpdateDerived() -> void {
        GUIScrollableArea::UpdateDerived();
    }

    auto GUIContainerWindowPanel::Initialize() -> void {
        for (auto i = 0; i < k_maxNumSlots; i++) {
            m_renderIDsSlotsBackground[i] =
                Hash("GUIContainerWindowSlotBackground" + std::to_string(i));
            m_renderIDsSlotsObject[i] = Hash("GUIContainerWindowSlotobject" + std::to_string(i));
        }
    }

    std::shared_ptr<Object> *GUIContainerWindowPanel::GetObjectPtrPtr(PointF position) {
        auto bounds{this->GetBounds()};
        auto marginX{k_margin};
        auto marginY{ConvertWidthToHeight(k_margin, Singleton<SDLDevice>().GetWindow())};
        auto xStart{bounds.x + marginX};
        auto yStart{bounds.y + marginY +
                    m_parentWindow->GetGUIWindowTitleBar()->GetBounds().height};

        auto slotWidth{k_slotSize};
        auto slotHeight{ConvertWidthToHeight(k_slotSize, Singleton<SDLDevice>().GetWindow())};

        auto numColumns{static_cast<int>((bounds.width - 2 * marginX) / slotWidth)};
        auto numRows{
            static_cast<int>((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

        auto mousePos{GetNormallizedMousePosition(Singleton<SDLDevice>().GetWindow())};

        auto &objectsContainer{Singleton<Player>().GetObjectsInventoryRef()};

        for (auto y = 0; y < numRows; y++) {
            for (auto x = 0; x < numColumns; x++) {
                auto index{x + y * numColumns};

                auto slotX{xStart + x * (slotWidth + marginX)};
                auto slotY{yStart + y * (slotHeight + marginY)};

                auto slotArea{RectF{slotX, slotY, slotWidth, slotHeight}};

                if (slotArea.Contains(mousePos)) {

                    auto inventoryObject{objectsContainer.GetObject(index)};

                    if (inventoryObject) {
                        return Singleton<Player>().GetObjectsInventoryRef().GetObjectPtrPtr(index);
                    }
                }
            }
        }

        return nullptr;
    }

    auto GUIContainerWindowPanel::RenderDerived() const -> void {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};
        auto marginX{k_margin};
        auto marginY{ConvertWidthToHeight(k_margin, Singleton<SDLDevice>().GetWindow())};
        auto xStart{bounds.x + marginX};
        auto yStart{bounds.y + marginY +
                    m_parentWindow->GetGUIWindowTitleBar()->GetBounds().height};

        auto slotWidth{k_slotSize};
        auto slotHeight{ConvertWidthToHeight(k_slotSize, Singleton<SDLDevice>().GetWindow())};

        auto numColumns{static_cast<int>((bounds.width - 2 * marginX) / slotWidth)};
        auto numRows{
            static_cast<int>((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

        auto &objectsContainer{Singleton<Player>().GetObjectsInventoryRef()};

        auto i{0};

        for (auto y = 0; y < numRows; y++) {
            for (auto x = 0; x < numColumns; x++) {

                if (i >= m_containedObjects.Size())
                    continue;
                ++i;

                auto index{x + y * numColumns};
                int renderIDBackground{0};

                if (m_renderIDsSlotsBackground.contains(index)) {
                    renderIDBackground = m_renderIDsSlotsBackground.at(index);
                } else {
                    PrintLine("GUIContainerWindow: Render ID not "
                              "found for index: " +
                              std::to_string(index));
                    return;
                }

                Singleton<Image2DRenderer>().DrawImageByName(
                    renderIDBackground, k_slotImageName, xStart + x * (slotWidth + marginX),
                    yStart + y * (slotHeight + marginY), slotWidth, slotHeight, true);

                auto inventoryObject{objectsContainer.GetObject(index)};

                if (inventoryObject) {
                    int renderIDObject{0};

                    if (m_renderIDsSlotsObject.contains(index)) {
                        renderIDObject = m_renderIDsSlotsObject.at(index);
                    } else {
                        PrintLine("GUIContainerWindow: "
                                  "Render ID not "
                                  "found for index: " +
                                  std::to_string(index));
                        return;
                    }

                    Singleton<Image2DRenderer>().DrawImageByHash(
                        renderIDObject, inventoryObject->GetType(),
                        xStart + x * (slotWidth + marginX), yStart + y * (slotHeight + marginY),
                        slotWidth, slotHeight, true);
                }
            }
        }
    }
}
