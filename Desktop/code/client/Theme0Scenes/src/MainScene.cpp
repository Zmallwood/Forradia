/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainScene.hpp"
#include "3D/Camera.hpp"
#include "CanvasUtilities.hpp"
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUIChatBox.hpp"
#include "GUIExperienceBar.hpp"
#include "GUIFPSPanel.hpp"
#include "GUIInteractionMenu/Actions.hpp"
#include "GUIInteractionMenu/GUIInteractionMenu.hpp"
#include "GUIInventoryWindow.hpp"
#include "GUIPanel.hpp"
#include "GUIPlayerStatusBox/GUIPlayerStatusBox.hpp"
#include "GUIQuestPanel.hpp"
#include "GUISystemMenu.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SDLDevice.hpp"
#include "Update/CameraRotator.hpp"
#include "Update/Quests/QuestSystem.hpp"
#include "Update/TileHovering.hpp"
#include "Update/UpdateEntitiesMovement.hpp"
#include "Update/UpdateKeyboardActions.hpp"
#include "Update/UpdateKeyboardMovement.hpp"
#include "Update/UpdateMouseMovement.hpp"
#include "Update/UpdateSetPlayerDestination.hpp"
#include "WorldView.hpp"

namespace Forradia::Theme0 {
    auto MainScene::InitializeDerived() -> void {
        GetGUI()->AddChildComponent(std::make_shared<GUIPlayerStatusBox>());
        GetGUI()->AddChildComponent(SingletonPtr<GUIChatBox>());

        auto btnInventoryWindow{std::make_shared<GUIButton>(
            "MainSceneButtonInventoryWin", 0.85f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, Singleton<SDLDevice>().GetWindow()), "",
            [] { GUIInventoryWindow::Instance().ToggleVisibility(); },
            "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground")};
        GetGUI()->AddChildComponent(btnInventoryWindow);

        auto btnSystemMenu{std::make_shared<GUIButton>(
            "MainSceneButtonSystemMenu", 0.92f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, Singleton<SDLDevice>().GetWindow()), "",
            [] { Singleton<GUISystemMenu>().ToggleVisibility(); }, "GUIButtonSystemMenuBackground",
            "GUIButtonSystemMenuHoveredBackground")};
        GetGUI()->AddChildComponent(btnSystemMenu);
        //  GetGUI()->AddChildComponent(SingletonPtr<GUIInventoryWindow>());
        GetGUI()->AddChildComponent(SingletonPtr<GUISystemMenu>());
        GetGUI()->AddChildComponent(std::make_shared<GUIFPSPanel>());
        GetGUI()->AddChildComponent(std::make_shared<GUIQuestPanel>());
        // GetGUI()->AddChildComponent(SingletonPtr<GUIInteractionMenu>());
        GetGUI()->AddChildComponent(SingletonPtr<GUIExperienceBar>());

        auto rightHandSlotPanel{std::make_shared<GUIPanel>(
            "GUIRightHandSlotPanel", 0.5F - 0.03F, 0.02F, 0.05F,
            ConvertWidthToHeight(0.05F, Singleton<SDLDevice>().GetWindow()),
            "GUIRightHandSlotBackground")};

        auto leftHandSlotPanel{std::make_shared<GUIPanel>(
            "GUILeftHandSlotPanel", 0.5F + 0.03F, 0.02F, 0.05F,
            ConvertWidthToHeight(0.05F, Singleton<SDLDevice>().GetWindow()),
            "GUILeftHandSlotBackground")};

        GetGUI()->AddChildComponent(rightHandSlotPanel);
        GetGUI()->AddChildComponent(leftHandSlotPanel);

        // m_guiInventoryWindow =
        //     std::make_shared<GUIInventoryWindow>(Singleton<Player>().GetObjectsInventoryRef());
        m_guiInteractionMenu = SingletonPtr<GUIInteractionMenu>();
    }

    auto MainScene::OnEnterDerived() -> void {
        auto chatBoxHeight{Singleton<GUIChatBox>().GetBounds().height};
        auto experienceBarHeight{Singleton<GUIExperienceBar>().GetBounds().height};
        Singleton<GUIChatBox>().SetPosition({0.0f, 1.0f - chatBoxHeight - experienceBarHeight});
        Singleton<GUIChatBox>().Print("You have entered the world.");
    }

    auto MainScene::OnMouseDown(Uint8 mouseButton) -> void {
        GetGUI()->OnMouseDown(mouseButton);
        if (GetGUI()->MouseHoveringGUI())
            return;
        if (GUIInventoryWindow::Instance().OnMouseDown(mouseButton))
            return;
        if (!GUIInventoryWindow::Instance().MouseHoveringGUI())
            Singleton<CameraRotator>().OnMouseDown(mouseButton);
    }

    auto MainScene::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void {
        Singleton<CameraRotator>().OnMouseUp(mouseButton);
        GetGUI()->OnMouseUp(mouseButton, clickSpeed);
        if (GetGUI()->MouseHoveringGUI())
            return;
        if (clickSpeed < 200)
            if (m_guiInteractionMenu->OnMouseUp(mouseButton, clickSpeed))
                return;
        if (GUIInventoryWindow::Instance().OnMouseUp(mouseButton, clickSpeed))
            return;
        if (!GUIInventoryWindow::Instance().MouseHoveringGUI() && mouseButton == SDL_BUTTON_LEFT)
            UpdateSetPlayerDestination();
    }

    auto MainScene::OnMouseWheel(int delta) -> void {
        Singleton<Camera>().AddZoomAmountDelta(delta);
    }

    auto MainScene::OnKeyDown(SDL_Keycode key) -> void {
        GetGUI()->OnKeyDown(key);
        UpdateKeyboardMovementStart(key);
        UpdateKeyboardActions(key);
    }

    auto MainScene::OnKeyUp(SDL_Keycode key) -> void {
        GetGUI()->OnKeyUp(key);
        UpdateKeyboardMovementStop();
    }

    auto MainScene::OnTextInput(std::string_view text) -> void {
        if (Singleton<GUIChatBox>().GetInputActive())
            Singleton<GUIChatBox>().AddTextInput(text);
    }

    auto MainScene::UpdateDerived() -> void {
        m_guiInteractionMenu->Update();
        GUIInventoryWindow::Instance().Update();
        UpdateMouseMovement();
        UpdateEntitiesMovement();
        Singleton<TileHovering>().Update();
        Singleton<Player>().Update();
        Singleton<CameraRotator>().Update();
        UpdateActions();
        Singleton<QuestSystem>().Update();
    }

    auto MainScene::Render() const -> void {
        this->RenderDerived();

        GetGUI()->Render();
        GUIInventoryWindow::Instance().Render();
        m_guiInteractionMenu->Render();
    }

    auto MainScene::RenderDerived() const -> void {
        Singleton<WorldView>().Render();
    }
}
