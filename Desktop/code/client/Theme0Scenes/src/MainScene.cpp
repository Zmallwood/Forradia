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
#include "GUIPlayerBodyWindow.hpp"
#include "GUIPlayerStatusBox/GUIPlayerStatusBox.hpp"
#include "GUIQuestPanel.hpp"
#include "GUISystemMenu.hpp"
#include "Player/Player.hpp"
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

        auto btnGUIPlayerBodyWindow{std::make_shared<GUIButton>(
            "MainSceneButtonPlayerBodyWin", 0.78f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, Singleton<SDLDevice>().GetWindow()), "",
            [] { Singleton<GUIPlayerBodyWindow>().ToggleVisibility(); },
            "GUIButtonPlayerBodyBackground", "GUIButtonPlayerBodyHoveredBackground")};
        GetGUI()->AddChildComponent(btnGUIPlayerBodyWindow);

        auto btnInventoryWindow{std::make_shared<GUIButton>(
            "MainSceneButtonInventoryWin", 0.85f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, Singleton<SDLDevice>().GetWindow()), "",
            [] { Singleton<GUIInventoryWindow>().ToggleVisibility(); },
            "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground")};
        GetGUI()->AddChildComponent(btnInventoryWindow);

        auto btnSystemMenu{std::make_shared<GUIButton>(
            "MainSceneButtonSystemMenu", 0.92f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, Singleton<SDLDevice>().GetWindow()), "",
            [] { Singleton<GUISystemMenu>().ToggleVisibility(); }, "GUIButtonSystemMenuBackground",
            "GUIButtonSystemMenuHoveredBackground")};
        GetGUI()->AddChildComponent(btnSystemMenu);
        // GetGUI()->AddChildComponent(SingletonPtr<GUIPlayerBodyWindow>());
        //  GetGUI()->AddChildComponent(SingletonPtr<GUIInventoryWindow>());
        GetGUI()->AddChildComponent(SingletonPtr<GUISystemMenu>());
        GetGUI()->AddChildComponent(std::make_shared<GUIFPSPanel>());
        GetGUI()->AddChildComponent(std::make_shared<GUIQuestPanel>());
        // GetGUI()->AddChildComponent(SingletonPtr<GUIInteractionMenu>());
        GetGUI()->AddChildComponent(SingletonPtr<GUIExperienceBar>());

        m_guiInventoryWindow = SingletonPtr<GUIInventoryWindow>();
        m_guiInteractionMenu = SingletonPtr<GUIInteractionMenu>();
        m_guiPlayerBodyWindow = SingletonPtr<GUIPlayerBodyWindow>();
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
        if (m_guiPlayerBodyWindow->OnMouseDown(mouseButton))
            return;
        if (m_guiInventoryWindow->OnMouseDown(mouseButton))
            return;
        if (!m_guiInventoryWindow->MouseHoveringGUI())
            Singleton<CameraRotator>().OnMouseDown(mouseButton);
    }

    auto MainScene::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void {
        Singleton<CameraRotator>().OnMouseUp(mouseButton);
        GetGUI()->OnMouseUp(mouseButton, clickSpeed);
        if (GetGUI()->MouseHoveringGUI())
            return;
        if (m_guiPlayerBodyWindow->OnMouseUp(mouseButton, clickSpeed))
            return;
        if (clickSpeed < 200)
            if (m_guiInteractionMenu->OnMouseUp(mouseButton, clickSpeed))
                return;
        if (m_guiInventoryWindow->OnMouseUp(mouseButton, clickSpeed))
            return;
        if (!m_guiInventoryWindow->MouseHoveringGUI() &&
            !m_guiPlayerBodyWindow->MouseHoveringGUI() && mouseButton == SDL_BUTTON_LEFT)
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
        m_guiInventoryWindow->Update();
        m_guiPlayerBodyWindow->Update();
        UpdateMouseMovement();
        UpdateEntitiesMovement();
        // UpdateCameraZoom();
        // UpdateKeyboardMovement();
        Singleton<TileHovering>().Update();
        Singleton<Player>().Update();
        Singleton<CameraRotator>().Update();
        UpdateActions();
        Singleton<QuestSystem>().Update();
    }

    auto MainScene::Render() const -> void {
        this->RenderDerived();

        GetGUI()->Render();
        m_guiInventoryWindow->Render();
        m_guiInteractionMenu->Render();
        m_guiPlayerBodyWindow->Render();
    }

    auto MainScene::RenderDerived() const -> void {
        Singleton<WorldView>().Render();
    }
}
