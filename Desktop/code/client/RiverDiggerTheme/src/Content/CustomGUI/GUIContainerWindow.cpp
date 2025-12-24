/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIContainerWindow.hpp"
#include "Content/WorldStructure/ContainedObjects.hpp"
#include "GUICore/GUIScrollableArea.hpp"
#include "GUICore/GUIWindowTitleBar.hpp"
#include "Rendering/Images/Image2DRenderer.hpp"
#include "Common/Utilities/MouseUtilities.hpp"
#include "Content/WorldStructure/Object.hpp"
#include "Content/Essentials/Player/Player.hpp"
#include "GraphicsDevices/SDLDevice.hpp"

namespace Forradia::Theme0
{
    auto GUIContainerWindow::initialize(ContainedObjects &containedObjects) -> void
    {
        m_guiContainerWindowArea = std::make_shared<GUIContainerWindowArea>(this, containedObjects);

        this->addChildComponent(m_guiContainerWindowArea);
    }

    std::shared_ptr<std::shared_ptr<Object>>
    GUIContainerWindow::getObjectPtrPtr(PointF position) const
    {
        return m_guiContainerWindowArea->getObjectPtrPtr(position);
    }

    auto GUIContainerWindowArea::initialize(GUIWindow *parentWindow,
                                            ContainedObjects &containedObjects) -> void
    {
        m_panel = std::make_shared<GUIContainerWindowPanel>(parentWindow, containedObjects);

        this->addChildComponent(m_panel);
    }

    std::shared_ptr<std::shared_ptr<Object>>
    GUIContainerWindowArea::getObjectPtrPtr(PointF position) const
    {
        return m_panel->getObjectPtrPtr(position);
    }

    auto GUIContainerWindowArea::updateDerived() -> void
    {
        GUIScrollableArea::updateDerived();
    }

    auto GUIContainerWindowPanel::initialize() -> void
    {
        for (auto i = 0; i < k_maxNumSlots; i++)
        {
            m_renderIDsSlotsBackground[i] =
                hash("GUIContainerWindowSlotBackground" + std::to_string(i));

            m_renderIDsSlotsObject[i] = hash("GUIContainerWindowSlotObject" + std::to_string(i));
        }
    }

    std::shared_ptr<std::shared_ptr<Object>>
    GUIContainerWindowPanel::getObjectPtrPtr(PointF position) const
    {
        auto bounds{this->getBounds()};
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

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numColumns; x++)
            {
                auto index{x + y * numColumns};

                auto slotX{xStart + static_cast<float>(x) * (slotWidth + marginX)};
                auto slotY{yStart + static_cast<float>(y) * (slotHeight + marginY)};

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
        GUIPanel::renderDerived();

        auto bounds{this->getBounds()};
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

        auto i{0};

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numColumns; x++)
            {

                if (i >= m_containedObjects.size())
                {
                    continue;
                }

                ++i;

                auto index{x + y * numColumns};

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
                    xStart + static_cast<float>(x) * (slotWidth + marginX),
                    yStart + static_cast<float>(y) * (slotHeight + marginY), slotWidth, slotHeight,
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
                        xStart + static_cast<float>(x) * (slotWidth + marginX),
                        yStart + static_cast<float>(y) * (slotHeight + marginY), slotWidth,
                        slotHeight, true);
                }
            }
        }
    }
}
