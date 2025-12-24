/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainScene.hpp"
#include "Rendering/Base/3D/Camera.hpp"
#include "Common/Utilities/CanvasUtilities.hpp"
#include "GUICore/GUI.hpp"
#include "GUICore/GUIButton.hpp"
#include "GUICore/GUIChatBox.hpp"
#include "Content/CustomGUI/GUIExperienceBar.hpp"
#include "GUICore/GUIFPSPanel.hpp"
#include "Content/CustomGUI/GUIInteractionMenu/Actions.hpp"
#include "Content/CustomGUI/GUIInteractionMenu/GUIInteractionMenu.hpp"
#include "Content/CustomGUI/GUIInventoryWindow.hpp"
#include "GUICore/GUIPanel.hpp"
#include "Content/CustomGUI/GUIPlayerStatusBox/GUIPlayerStatusBox.hpp"
#include "Content/CustomGUI/GUIQuestPanel.hpp"
#include "Content/CustomGUI/GUISystemMenu.hpp"
#include "Content/Essentials/Player/Player.hpp"
#include "Content/Essentials/Player/PlayerObjectsInventory.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Content/Core/Update/CameraRotator.hpp"
#include "Content/Core/Update/ObjectMoving.hpp"
#include "Content/Core/Update/Quests/QuestSystem.hpp"
#include "Content/Core/Update/TileHovering.hpp"
#include "Content/Core/Update/UpdateEntitiesMovement.hpp"
#include "Content/Core/Update/UpdateKeyboardActions.hpp"
#include "Content/Core/Update/UpdateKeyboardMovement.hpp"
#include "Content/Core/Update/UpdateMouseMovement.hpp"
#include "Content/Core/Update/UpdateSetPlayerDestination.hpp"
#include "Content/Core/WorldView.hpp"

namespace Forradia::Theme0
{
    auto MainScene::initializeDerived() -> void
    {
        getGUI()->addChildComponent(std::make_shared<GUIPlayerStatusBox>());

        getGUI()->addChildComponent(GUIChatBox::instancePtr());

        auto btnInventoryWindow{std::make_shared<GUIButton>(
            "MainSceneButtonInventoryWin", 0.85f, 0.9f, 0.05f,
            convertWidthToHeight(0.05f, SDLDevice::instance().getWindow()), "",
            [] { GUIInventoryWindow::instance().toggleVisibility(); },
            "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground")};

        getGUI()->addChildComponent(btnInventoryWindow);

        auto btnSystemMenu{std::make_shared<GUIButton>(
            "MainSceneButtonSystemMenu", 0.92f, 0.9f, 0.05f,
            convertWidthToHeight(0.05f, SDLDevice::instance().getWindow()), "",
            [] { GUISystemMenu::instance().toggleVisibility(); }, "GUIButtonSystemMenuBackground",
            "GUIButtonSystemMenuHoveredBackground")};

        getGUI()->addChildComponent(btnSystemMenu);

        getGUI()->addChildComponent(GUISystemMenu::instancePtr());

        getGUI()->addChildComponent(std::make_shared<GUIFPSPanel>());

        getGUI()->addChildComponent(std::make_shared<GUIQuestPanel>());

        getGUI()->addChildComponent(GUIExperienceBar::instancePtr());

        auto rightHandSlotPanel{std::make_shared<GUIPanel>(
            "GUIRightHandSlotPanel", 0.5F - 0.03F, 0.02F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()),
            "GUIRightHandSlotBackground")};

        auto leftHandSlotPanel{std::make_shared<GUIPanel>(
            "GUILeftHandSlotPanel", 0.5F + 0.03F, 0.02F, 0.05F,
            convertWidthToHeight(0.05F, SDLDevice::instance().getWindow()),
            "GUILeftHandSlotBackground")};

        getGUI()->addChildComponent(rightHandSlotPanel);

        getGUI()->addChildComponent(leftHandSlotPanel);

        m_guiInteractionMenu = GUIInteractionMenu::instancePtr();
    }

    auto MainScene::onEnterDerived() -> void
    {
        auto chatBoxHeight{GUIChatBox::instance().getBounds().height};

        auto experienceBarHeight{GUIExperienceBar::instance().getBounds().height};

        GUIChatBox::instance().setPosition({0.0f, 1.0f - chatBoxHeight - experienceBarHeight});

        GUIChatBox::instance().print("You have entered the world.");
    }

    auto MainScene::onMouseDown(Uint8 mouseButton) -> void
    {
        getGUI()->onMouseDown(mouseButton);

        if (getGUI()->mouseHoveringGUI())
        {
            return;
        }

        if (ObjectMoving::instance().onMouseDown(mouseButton))
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

        getGUI()->onMouseUp(mouseButton, clickSpeed);

        if (getGUI()->mouseHoveringGUI())
        {
            return;
        }

        if (clickSpeed < 200)
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

        TileHovering::instance().update();

        Player::instance().update();

        CameraRotator::instance().update();

        updateActions();

        QuestSystem::instance().update();
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
