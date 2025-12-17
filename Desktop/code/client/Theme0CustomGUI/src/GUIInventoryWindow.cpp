/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIInventoryWindow.hpp"
#include "GUIWindowTitleBar.hpp"
#include "Image2DRenderer.hpp"
#include "Object.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0 {
auto GUIInventoryWindow::Initialize() -> void {
  for (auto i = 0; i < k_maxNumSlots; i++) {
    m_renderIDsSlotsBackground[i] = Hash("GUIInventoryWindowSlotBackground" + std::to_string(i));
    m_renderIDsSlotsObject[i] = Hash("GUIInventoryWindowSlotobject" + std::to_string(i));
  }
}

auto GUIInventoryWindow::RenderDerived() const -> void {
  GUIWindow::RenderDerived();

  auto bounds{this->GetBounds()};
  auto marginX{k_margin};
  auto marginY{ConvertWidthToHeight(k_margin, _<SDLDevice>().GetWindow())};
  auto xStart{bounds.x + marginX};
  auto yStart{bounds.y + marginY + this->GetGUIWindowTitleBar()->GetBounds().height};

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
