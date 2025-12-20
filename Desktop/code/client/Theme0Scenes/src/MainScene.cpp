/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainScene.hpp"
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
#include "SDLDevice.hpp"
#include "Update/CameraRotator.hpp"
#include "Update/Quests/QuestSystem.hpp"
#include "Update/TileHovering.hpp"
// #include "Update/UpdateCameraZoom.hpp"
#include "Update/UpdateEntitiesMovement.hpp"
#include "Update/UpdateKeyboardActions.hpp"
#include "Update/UpdateKeyboardMovement.hpp"
// #include "Update/UpdateMouseActions.hpp"
#include "3D/Camera.hpp"
#include "Update/UpdateMouseMovement.hpp"
#include "Update/UpdateSetPlayerDestination.hpp"
#include "WorldView.hpp"

namespace Forradia::Theme0 {
    auto MainScene::InitializeDerived() -> void {
        GetGUI()->AddChildComponent(std::make_shared<GUIPlayerStatusBox>());
        GetGUI()->AddChildComponent(__<GUIChatBox>());

        auto btnGUIPlayerBodyWindow{std::make_shared<GUIButton>(
            "MainSceneButtonPlayerBodyWin", 0.78f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, _<SDLDevice>().GetWindow()), "",
            [] { _<GUIPlayerBodyWindow>().ToggleVisibility(); }, "GUIButtonPlayerBodyBackground",
            "GUIButtonPlayerBodyHoveredBackground")};
        GetGUI()->AddChildComponent(btnGUIPlayerBodyWindow);

        auto btnInventoryWindow{std::make_shared<GUIButton>(
            "MainSceneButtonInventoryWin", 0.85f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, _<SDLDevice>().GetWindow()), "",
            [] { _<GUIInventoryWindow>().ToggleVisibility(); }, "GUIButtonInventoryBackground",
            "GUIButtonInventoryHoveredBackground")};
        GetGUI()->AddChildComponent(btnInventoryWindow);

        auto btnSystemMenu{std::make_shared<GUIButton>(
            "MainSceneButtonSystemMenu", 0.92f, 0.9f, 0.05f,
            ConvertWidthToHeight(0.05f, _<SDLDevice>().GetWindow()), "",
            [] { _<GUISystemMenu>().ToggleVisibility(); }, "GUIButtonSystemMenuBackground",
            "GUIButtonSystemMenuHoveredBackground")};
        GetGUI()->AddChildComponent(btnSystemMenu);
        // GetGUI()->AddChildComponent(__<GUIPlayerBodyWindow>());
        //  GetGUI()->AddChildComponent(__<GUIInventoryWindow>());
        GetGUI()->AddChildComponent(__<GUISystemMenu>());
        GetGUI()->AddChildComponent(std::make_shared<GUIFPSPanel>());
        GetGUI()->AddChildComponent(std::make_shared<GUIQuestPanel>());
        // GetGUI()->AddChildComponent(__<GUIInteractionMenu>());
        GetGUI()->AddChildComponent(__<GUIExperienceBar>());

        m_guiInventoryWindow = __<GUIInventoryWindow>();
        m_guiInteractionMenu = __<GUIInteractionMenu>();
        m_guiPlayerBodyWindow = __<GUIPlayerBodyWindow>();
    }

    auto MainScene::OnEnterDerived() -> void {
        auto chatBoxHeight{_<GUIChatBox>().GetBounds().height};
        auto experienceBarHeight{_<GUIExperienceBar>().GetBounds().height};
        _<GUIChatBox>().SetPosition({0.0f, 1.0f - chatBoxHeight - experienceBarHeight});
        _<GUIChatBox>().Print("You have entered the world.");
    }

    auto MainScene::OnMouseDown(Uint8 mouseButton) -> void {
        if (GetGUI()->MouseHoveringGUI())
            return;
        if (m_guiPlayerBodyWindow->OnMouseDown(mouseButton))
            return;
        if (m_guiInventoryWindow->OnMouseDown(mouseButton))
            return;
        if (!m_guiInventoryWindow->MouseHoveringGUI())
            _<CameraRotator>().OnMouseDown(mouseButton);
    }

    auto MainScene::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void {
        _<CameraRotator>().OnMouseUp(mouseButton);
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
        _<Camera>().AddZoomAmountDelta(delta);
    }

    auto MainScene::UpdateDerived() -> void {
        m_guiInteractionMenu->Update();
        m_guiInventoryWindow->Update();
        m_guiPlayerBodyWindow->Update();
        UpdateMouseMovement();
        UpdateKeyboardActions();
        UpdateEntitiesMovement();
        // UpdateCameraZoom();
        UpdateKeyboardMovement();
        _<TileHovering>().Update();
        _<CameraRotator>().Update();
        UpdateActions();
        _<QuestSystem>().Update();
    }

    auto MainScene::Render() const -> void {
        this->RenderDerived();

        GetGUI()->Render();
        m_guiInventoryWindow->Render();
        m_guiInteractionMenu->Render();
        m_guiPlayerBodyWindow->Render();
    }

    auto MainScene::RenderDerived() const -> void {
        _<WorldView>().Render();
    }
}
