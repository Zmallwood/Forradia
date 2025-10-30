//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIInventoryWindow.hpp"

#include "SDLDevice.hpp"

#include "Images2D/Image2DRenderer.hpp"

#include "PlayerCharacter.hpp"

#include "ObjectsInventory.hpp"

#include "Object.hpp"

namespace Forradia::Theme0
{
    void GUIInventoryWindow::RenderDerived() const
    {
        GUIWindow::RenderDerived();

        auto bounds{this->GetBounds()};

        auto marginX{k_margin};

        auto marginY{ConvertWidthToHeight(
            k_margin, _<SDLDevice>().GetWindow())};

        auto xStart{bounds.x + marginX};

        auto yStart{bounds.y + marginY +
                    this->GetGUIWindowTitleBar()
                        ->GetBounds()
                        .height};

        auto slotWidth{k_slotSize};

        auto slotHeight{ConvertWidthToHeight(
            k_slotSize, _<SDLDevice>().GetWindow())};

        auto numColumns{
            CInt((bounds.width - 2 * marginX) / slotWidth)};

        auto numRows{CInt((bounds.height - 2 * marginY -
                           (yStart - bounds.y)) /
                          slotHeight)};

        auto &objectsInventory{
            _<GameplayCore::PlayerCharacter>()
                .GetObjectsInventoryRef()};

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numColumns; x++)
            {
                _<Image2DRenderer>().DrawImage(
                    k_slotImageName,
                    xStart + x * (slotWidth + marginX),
                    yStart + y * (slotHeight + marginY),
                    slotWidth, slotHeight);

                auto index{x + y * numColumns};

                auto inventoryObject{
                    objectsInventory.GetObject(index)};

                if (inventoryObject)
                {
                    _<Image2DRenderer>().DrawImage(
                        inventoryObject->GetType(),
                        xStart + x * (slotWidth + marginX),
                        yStart + y * (slotHeight + marginY),
                        slotWidth, slotHeight);
                }
            }
        }
    }
}