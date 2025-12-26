/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIContainerWindowPanel.hpp"
    #include "ForradiaEngine/GUICore/GUIComponent.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
    #include "ForradiaEngine/GUICore/GUIWindow.hpp"
    #include "ForradiaEngine/GUICore/GUIWindowTitleBar.hpp"
    #include "Content/WorldStructure/ContainedObjects.hpp"
    #include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
    #include "Content/WorldStructure/Object.hpp"
    #include "ForradiaEngine/Common/Utilities/CanvasUtilities.hpp"
    #include "ForradiaEngine/Common/Utilities/MouseUtilities.hpp"
    #include "ForradiaEngine/Common/Utilities/MessageUtilities.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto GUIContainerWindowPanel::initialize() -> void
    {
        for (auto i = 0; i < k_maxNumSlots; i++)
        {
            m_renderIDsSlotsBackground[i] =
                hash("GUIContainerWindowSlotBackground" + std::to_string(i));

            m_renderIDsSlotsObject[i] = hash("GUIContainerWindowSlotObject" + std::to_string(i));
        }
    }

    auto GUIContainerWindowPanel::getObjectPtrPtr(PointF position) const
        -> std::shared_ptr<std::shared_ptr<Object>>
    {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};
        auto marginX{k_margin};
        auto marginY{convertWidthToHeight(k_margin, SDLDevice::instance().getWindow())};
        auto xStart{bounds.x + marginX};
        auto yStart{bounds.y + marginY +
                    m_parentWindow->getGUIWindowTitleBar()->getBounds().height};

        auto slotWidth{k_slotSize};
        auto slotHeight{convertWidthToHeight(k_slotSize, SDLDevice::instance().getWindow())};

        auto numColumns{static_cast<int>((bounds.width - 2 * marginX) / slotWidth)};
        auto numRows{
            static_cast<int>((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto &objectsContainer{m_containedObjects};

        for (auto yPos = 0; yPos < numRows; yPos++)
        {
            for (auto xPos = 0; xPos < numColumns; xPos++)
            {
                auto index{xPos + yPos * numColumns};

                auto slotX{xStart + static_cast<float>(xPos) * (slotWidth + marginX)};
                auto slotY{yStart + static_cast<float>(yPos) * (slotHeight + marginY)};

                auto slotArea{RectF{slotX, slotY, slotWidth, slotHeight}};

                if (slotArea.contains(mousePos))
                {
                    auto inventoryObject{objectsContainer.getObject(index)};

                    return m_containedObjects.getObjectPtrPtr(index);
                }
            }
        }

        return nullptr;
    }

    auto GUIContainerWindowPanel::renderDerived() const -> void
    {
        dynamic_cast<const GUIPanel *>(this)->GUIPanel::renderDerived();

        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};
        auto marginX{k_margin};
        auto marginY{convertWidthToHeight(k_margin, SDLDevice::instance().getWindow())};
        auto xStart{bounds.x + marginX};
        auto yStart{bounds.y + marginY +
                    m_parentWindow->getGUIWindowTitleBar()->getBounds().height};

        auto slotWidth{k_slotSize};
        auto slotHeight{convertWidthToHeight(k_slotSize, SDLDevice::instance().getWindow())};

        auto numColumns{static_cast<int>((bounds.width - 2 * marginX) / slotWidth)};
        auto numRows{
            static_cast<int>((bounds.height - 2 * marginY - (yStart - bounds.y)) / slotHeight)};

        auto &objectsContainer{m_containedObjects};

        auto index{0};

        for (auto yPos = 0; yPos < numRows; yPos++)
        {
            for (auto xPos = 0; xPos < numColumns; xPos++)
            {

                if (index >= m_containedObjects.size())
                {
                    continue;
                }

                ++index;

                auto index{xPos + yPos * numColumns};

                int renderIDBackground{0};

                if (m_renderIDsSlotsBackground.contains(index))
                {
                    renderIDBackground = m_renderIDsSlotsBackground.at(index);
                }
                else
                {
                    printLine("GUIContainerWindow: Render ID not "
                              "found for index: " +
                              std::to_string(index));
                    return;
                }

                Image2DRenderer::instance().drawImageByName(
                    renderIDBackground, k_slotImageName,
                    xStart + static_cast<float>(xPos) * (slotWidth + marginX),
                    yStart + static_cast<float>(yPos) * (slotHeight + marginY), slotWidth, slotHeight,
                    true);

                if (auto inventoryObject{objectsContainer.getObject(index)})
                {
                    int renderIDObject{0};

                    if (m_renderIDsSlotsObject.contains(index))
                    {
                        renderIDObject = m_renderIDsSlotsObject.at(index);
                    }
                    else
                    {
                        printLine("GUIContainerWindow: "
                                  "Render ID not "
                                  "found for index: " +
                                  std::to_string(index));
                        return;
                    }

                    Image2DRenderer::instance().drawImageByHash(
                        renderIDObject, inventoryObject->getType(),
                        xStart + static_cast<float>(xPos) * (slotWidth + marginX),
                        yStart + static_cast<float>(yPos) * (slotHeight + marginY), slotWidth,
                        slotHeight, true);
                }
            }
        }
    }
}