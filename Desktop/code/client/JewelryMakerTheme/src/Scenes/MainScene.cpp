/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainScene.hpp"
#include "Core/Update/CameraRotator.hpp"
#include "Core/Update/ObjectMoving.hpp"
#include "Core/Update/QuestSystem.hpp"
#include "Core/Update/TileHovering.hpp"
#include "Core/Update/updateEntitiesMovement.hpp"
#include "Core/Update/updateEntitiesDirections.hpp"
#include "Core/Update/updateKeyboardActions.hpp"
#include "Core/Update/updateKeyboardMovement.hpp"
#include "Core/Update/updateMouseMovement.hpp"
#include "Core/Update/updateSetPlayerDestination.hpp"
#include "Core/WorldView.hpp"
#include "CustomGUI/GUIExperienceBar.hpp"
#include "actions.hpp"
#include "CustomGUI/GUIInteractionMenu/GUIInteractionMenu.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "CustomGUI/GUICraftingWindow.hpp"
#include "CustomGUI/GUIPlayerStatusBox/GUIPlayerStatusBox.hpp"
#include "CustomGUI/GUIQuestPanel.hpp"
#include "CustomGUI/GUISystemMenu.hpp"
#include "CustomGUI/GUITimedActionBar.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include "ForradiaEngine/GUICore/GUIButton.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/GUICore/GUIFPSPanel.hpp"
#include "ForradiaEngine/GUICore/GUIPanel.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Base/3D/Camera.hpp"
#include "ForradiaEngine/Assets/Audio/AudioBank.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto MainScene::initializeDerived() -> void
    {
        getGUI()->addChildComponent(std::make_shared<GUIPlayerStatusBox>());

        getGUI()->addChildComponent(GUIChatBox::instancePtr());

        auto btnCraftingWindow{std::make_shared<GUIButton>(
            "MainSceneButtonCraftingWin", 0.78F, 0.89F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()), "",
            [] { GUICraftingWindow::instance().toggleVisibility(); }, "GUIButtonCraftingBackground",
            "GUIButtonCraftingHoveredBackground")};

        getGUI()->addChildComponent(btnCraftingWindow);

        // NOLINTBEGIN(readability-magic-numbers)
        auto btnInventoryWindow{std::make_shared<GUIButton>(
            "MainSceneButtonInventoryWin", 0.85F, 0.89F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()), "",
            [] { GUIInventoryWindow::instance().toggleVisibility(); },
            "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(btnInventoryWindow);

        // NOLINTBEGIN(readability-magic-numbers)
        auto btnSystemMenu{std::make_shared<GUIButton>(
            "MainSceneButtonSystemMenu", 0.92F, 0.89F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()), "",
            [] { GUISystemMenu::instance().toggleVisibility(); }, "GUIButtonSystemMenuBackground",
            "GUIButtonSystemMenuHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(btnSystemMenu);

        getGUI()->addChildComponent(GUICraftingWindow::instancePtr());

        getGUI()->addChildComponent(GUISystemMenu::instancePtr());

        getGUI()->addChildComponent(std::make_shared<GUIFPSPanel>());

        getGUI()->addChildComponent(std::make_shared<GUIQuestPanel>());

        getGUI()->addChildComponent(GUIExperienceBar::instancePtr());

        getGUI()->addChildComponent(GUITimedActionBar::instancePtr());

        // NOLINTBEGIN(readability-magic-numbers)
        auto rightHandSlotPanel{std::make_shared<GUIPanel>(
            "GUIRightHandSlotPanel", 0.5F - 0.03F, 0.02F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()),
            "GUIRightHandSlotBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(rightHandSlotPanel);

        // NOLINTBEGIN(readability-magic-numbers)
        auto leftHandSlotPanel{std::make_shared<GUIPanel>(
            "GUILeftHandSlotPanel", 0.5F + 0.03F, 0.02F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()),
            "GUILeftHandSlotBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(leftHandSlotPanel);

        m_guiInteractionMenu = GUIInteractionMenu::instancePtr();
    }

    auto MainScene::onEnterDerived() -> void
    {
        Player::instance().initialize();

        auto chatBoxHeight{GUIChatBox::instance().getBounds().height};

        auto experienceBarHeight{GUIExperienceBar::instance().getBounds().height};

        GUIChatBox::instance().setPosition({0.0F, 1.0F - chatBoxHeight - experienceBarHeight});

        AudioBank::instance().unmuteMusic();

        AudioBank::instance().playMusic(hash("music1"));

        GUIChatBox::instance().print("You have entered the world.");
    }

    auto MainScene::onMouseDown(Uint8 mouseButton) -> void
    {
        getGUI()->onMouseDown(mouseButton);

        if (ObjectMoving::instance().onMouseDown(mouseButton))
        {
            return;
        }

        if (getGUI()->mouseHoveringGUI())
        {
            return;
        }

        if (GUIInventoryWindow::instance().onMouseDown(mouseButton))
        {
            return;
        }

        if (!GUIInventoryWindow::instance().mouseHoveringGUI())
        {
            CameraRotator::instance().onMouseDown(mouseButton);
        }
    }

    auto MainScene::onMouseUp(Uint8 mouseButton, int clickSpeed) -> void
    {
        CameraRotator::instance().onMouseUp(mouseButton);

        constexpr int k_clickSpeedThreshold{200};

        if (clickSpeed < k_clickSpeedThreshold)
        {
            if (m_guiInteractionMenu->onMouseUp(mouseButton, clickSpeed))
            {
                return;
            }
        }

        if (ObjectMoving::instance().onMouseUp(mouseButton, clickSpeed))
        {
            return;
        }

        getGUI()->onMouseUp(mouseButton, clickSpeed);

        if (getGUI()->mouseHoveringGUI())
        {
            return;
        }

        if (GUIInventoryWindow::instance().onMouseUp(mouseButton, clickSpeed))
        {
            return;
        }

        if (!GUIInventoryWindow::instance().mouseHoveringGUI() && mouseButton == SDL_BUTTON_LEFT)
        {
            updateSetPlayerDestination();
        }
    }

    auto MainScene::onMouseWheel(int delta) -> void
    {
        Camera::instance().addZoomAmountDelta(delta);
    }

    auto MainScene::onKeyDown(SDL_Keycode key) -> void
    {
        getGUI()->onKeyDown(key);

        updateKeyboardMovementStart(key);

        updateKeyboardActions(key);
    }

    auto MainScene::onKeyUp(SDL_Keycode key) -> void
    {
        getGUI()->onKeyUp(key);

        updateKeyboardMovementStop();
    }

    auto MainScene::onTextInput(std::string_view text) -> void
    {
        if (GUIChatBox::instance().getInputActive())
        {
            GUIChatBox::instance().addTextInput(text);
        }
    }

    auto MainScene::updateDerived() -> void
    {
        m_guiInteractionMenu->update();

        GUIInventoryWindow::instance().update();

        updateMouseMovement();

        updateEntitiesMovement();

        updateEntitiesDirections();

        TileHovering::update();

        Player::instance().update();

        CameraRotator::instance().update();

        updateTimedAction();

        QuestSystem::instance().update();

        Camera::update();
    }

    auto MainScene::render() const -> void
    {
        this->renderDerived();

        getGUI()->render();

        GUIInventoryWindow::instance().render();

        ObjectMoving::instance().render();

        m_guiInteractionMenu->render();
    }

    auto MainScene::renderDerived() const -> void
    {
        WorldView::instance().render();
    }
}
