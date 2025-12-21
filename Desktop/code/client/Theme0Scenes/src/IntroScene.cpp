/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "IntroScene.hpp"
#include "Cursor.hpp"
#include "GUI.hpp"
#include "GUIChatBox.hpp"
#include "GUILabel.hpp"
#include "Image2DRenderer.hpp"
#include "SceneManager.hpp"

namespace Forradia::Theme0 {
    auto IntroScene::InitializeDerived() -> void {
        auto lbl{std::make_shared<GUILabel>("GUILabelIntroSceneStartText", 0.45f, 0.5f, 0.1f, 0.04f,
                                            "Press to start", true)};
        m_startText = GetGUI()->AddChildComponent(lbl);
    }

    auto IntroScene::OnEnterDerived() -> void {
        _<GUIChatBox>().Print("Game started.");
    }

    auto IntroScene::OnMouseDown(Uint8 mouseButton) -> void {
        _<SceneManager>().GoToScene("MainMenuScene");
    }

    auto IntroScene::OnKeyDown(SDL_Keycode key) -> void {
        _<SceneManager>().GoToScene("MainMenuScene");
    }

    auto IntroScene::UpdateDerived() -> void {
        m_startText->SetVisible(GetTicks() % 800 < 400);
        _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
    }

    auto IntroScene::RenderDerived() const -> void {
        _<Image2DRenderer>().DrawImageByName(Hash("IntroSceneBackground"), "DefaultSceneBackground",
                                             0.0f, 0.0f, 1.0f, 1.0f);
        _<Image2DRenderer>().DrawImageAutoHeight(Hash("IntroSceneLogo"), "ForradiaLogo", 0.25f,
                                                 0.2f, 0.5f);
    }
}
