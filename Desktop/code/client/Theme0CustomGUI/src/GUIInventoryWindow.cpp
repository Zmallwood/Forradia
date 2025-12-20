/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIInventoryWindow.hpp"
#include "GUIScrollableArea.hpp"
#include "GUIWindowTitleBar.hpp"
#include "Image2DRenderer.hpp"
#include "Mouse/MouseInput.hpp"
#include "MouseUtilities.hpp"
#include "Object.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0 {
  auto GUIInventoryWindow::Initialize() -> void {
    m_guiInventoryWindowArea = std::make_shared<GUIInventoryWindowArea>(this);
    this->AddChildComponent(m_guiInventoryWindowArea);
  }

  std::shared_ptr<Object> *GUIInventoryWindow::GetObjectPtrPtr(PointF position) {
    return m_guiInventoryWindowArea->GetObjectPtrPtr(position);
  }

  auto GUIInventoryWindowArea::Initialize(GUIWindow *parentWindow) -> void {
    m_panel = std::make_shared<GUIInventoryWindowPanel>(parentWindow);
    this->AddChildComponent(m_panel);
  }

  std::shared_ptr<Object> *GUIInventoryWindowArea::GetObjectPtrPtr(PointF position) {
    return m_panel->GetObjectPtrPtr(position);
  }

  auto GUIInventoryWindowArea::UpdateDerived() -> void {
    // auto rightClick{_<MouseInput>().GetRightMouseButtonRef().HasBeenFired()};

    // auto bounds{this->GetBounds()};
    // auto marginX{k_margin};
    // auto marginY{ConvertWidthToHeight(k_margin, _<SDLDevice>().GetWindow())};
    // auto xStart{bounds.x + marginX};
    // auto yStart{bounds.y + marginY + m_parentWindow->GetGUIWindowTitleBar()->GetBounds().height};

    // auto slotWidth{k_slotSize};
    // auto slotHeight{ConvertWidthToHeight(k_slotSize, _<SDLDevice>().GetWindow())};

    // auto numColumns{CInt((bounds.width - 2 * marginX) / slotWidth)};
    // auto numRows{CInt((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

    // auto &objectsInventory{_<Player>().GetObjectsInventoryRef()};

    // for (auto y = 0; y < numRows; y++) {
    //   for (auto x = 0; x < numColumns; x++) {
    //     auto index{x + y * numColumns};
    //     int renderIDBackground{0};

    //    if (m_renderIDsSlotsBackground.contains(index)) {
    //      renderIDBackground = m_renderIDsSlotsBackground.at(index);
    //    } else {
    //      PrintLine("GUIInventoryWindow: Render ID not "
    //                "found for index: " +
    //                std::to_string(index));
    //      return;
    //    }

    //    _<Image2DRenderer>().DrawImageByName(
    //        renderIDBackground, k_slotImageName, xStart + x * (slotWidth + marginX),
    //        yStart + y * (slotHeight + marginY), slotWidth, slotHeight, true);

    //    auto inventoryObject{objectsInventory.GetObject(index)};

    //    if (inventoryObject) {
    //      int renderIDObject{0};

    //      if (m_renderIDsSlotsObject.contains(index)) {
    //        renderIDObject = m_renderIDsSlotsObject.at(index);
    //      } else {
    //        PrintLine("GUIInventoryWindow: "
    //                  "Render ID not "
    //                  "found for index: " +
    //                  std::to_string(index));
    //        return;
    //      }

    //      _<Image2DRenderer>().DrawImageByHash(
    //          renderIDObject, inventoryObject->GetType(), xStart + x * (slotWidth + marginX),
    //          yStart + y * (slotHeight + marginY), slotWidth, slotHeight, true);
    //    }
    //  }
    //}

    GUIScrollableArea::UpdateDerived();
  }

  auto GUIInventoryWindowArea::GetBounds() const -> RectF {
    auto baseBounds{GUIScrollableArea::GetBounds()};
    auto bounds{m_parentWindow->GetBounds()};
    baseBounds.height = bounds.height / 2.0f;
    // baseBounds.y += m_parentWindow->GetGUIWindowTitleBar()->GetHeight();
    // baseBounds.height -= m_parentWindow->GetGUIWindowTitleBar()->GetHeight();
    //  bounds = {0.0f, 0.0f, 1.0f, 1.0f};
    return baseBounds;
  }

  auto GUIInventoryWindowPanel::Initialize() -> void {
    for (auto i = 0; i < k_maxNumSlots; i++) {
      m_renderIDsSlotsBackground[i] = Hash("GUIInventoryWindowSlotBackground" + std::to_string(i));
      m_renderIDsSlotsObject[i] = Hash("GUIInventoryWindowSlotobject" + std::to_string(i));
    }
  }

  std::shared_ptr<Object> *GUIInventoryWindowPanel::GetObjectPtrPtr(PointF position) {
    auto bounds{this->GetBounds()};
    auto marginX{k_margin};
    auto marginY{ConvertWidthToHeight(k_margin, _<SDLDevice>().GetWindow())};
    auto xStart{bounds.x + marginX};
    auto yStart{bounds.y + marginY + m_parentWindow->GetGUIWindowTitleBar()->GetBounds().height};

    auto slotWidth{k_slotSize};
    auto slotHeight{ConvertWidthToHeight(k_slotSize, _<SDLDevice>().GetWindow())};

    auto numColumns{CInt((bounds.width - 2 * marginX) / slotWidth)};
    auto numRows{CInt((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

    auto mousePos{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

    auto &objectsInventory{_<Player>().GetObjectsInventoryRef()};

    for (auto y = 0; y < numRows; y++) {
      for (auto x = 0; x < numColumns; x++) {
        auto index{x + y * numColumns};

        auto slotX{xStart + x * (slotWidth + marginX)};
        auto slotY{yStart + y * (slotHeight + marginY)};

        auto slotArea{RectF{slotX, slotY, slotWidth, slotHeight}};

        if (slotArea.Contains(mousePos)) {

          auto inventoryObject{objectsInventory.GetObject(index)};

          if (inventoryObject) {
            return _<Player>().GetObjectsInventoryRef().GetObjectPtrPtr(index);
          }
        }
      }
    }

    return nullptr;
  }

  auto GUIInventoryWindowPanel::RenderDerived() const -> void {
    GUIPanel::RenderDerived();

    auto bounds{this->GetBounds()};
    auto marginX{k_margin};
    auto marginY{ConvertWidthToHeight(k_margin, _<SDLDevice>().GetWindow())};
    auto xStart{bounds.x + marginX};
    auto yStart{bounds.y + marginY + m_parentWindow->GetGUIWindowTitleBar()->GetBounds().height};

    auto slotWidth{k_slotSize};
    auto slotHeight{ConvertWidthToHeight(k_slotSize, _<SDLDevice>().GetWindow())};

    auto numColumns{CInt((bounds.width - 2 * marginX) / slotWidth)};
    auto numRows{CInt((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

    auto &objectsInventory{_<Player>().GetObjectsInventoryRef()};

    for (auto y = 0; y < numRows; y++) {
      for (auto x = 0; x < numColumns; x++) {
        auto index{x + y * numColumns};
        int renderIDBackground{0};

        if (m_renderIDsSlotsBackground.contains(index)) {
          renderIDBackground = m_renderIDsSlotsBackground.at(index);
        } else {
          PrintLine("GUIInventoryWindow: Render ID not "
                    "found for index: " +
                    std::to_string(index));
          return;
        }

        _<Image2DRenderer>().DrawImageByName(
            renderIDBackground, k_slotImageName, xStart + x * (slotWidth + marginX),
            yStart + y * (slotHeight + marginY), slotWidth, slotHeight, true);

        auto inventoryObject{objectsInventory.GetObject(index)};

        if (inventoryObject) {
          int renderIDObject{0};

          if (m_renderIDsSlotsObject.contains(index)) {
            renderIDObject = m_renderIDsSlotsObject.at(index);
          } else {
            PrintLine("GUIInventoryWindow: "
                      "Render ID not "
                      "found for index: " +
                      std::to_string(index));
            return;
          }

          _<Image2DRenderer>().DrawImageByHash(
              renderIDObject, inventoryObject->GetType(), xStart + x * (slotWidth + marginX),
              yStart + y * (slotHeight + marginY), slotWidth, slotHeight, true);
        }
      }
    }
  }
}
