/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "IntroScene.hpp"
#include "MinorComponents/Cursor.hpp"
#include "GUICore/GUI.hpp"
#include "GUICore/GUIChatBox.hpp"
#include "GUICore/GUILabel.hpp"
#include "Rendering/Images/Image2DRenderer.hpp"
#include "ScenesCore/SceneManager.hpp"

namespace Forradia::Theme0
{
    auto IntroScene::initializeDerived() -> void
    {
        auto lbl{std::make_shared<GUILabel>("GUILabelIntroSceneStartText", 0.45f, 0.5f, 0.1f, 0.04f,
                                            "Press to start", true)};

        m_startText = getGUI()->addChildComponent(lbl);
    }

    auto IntroScene::onEnterDerived() -> void
    {
        GUIChatBox::instance().print("Game started.");
    }

    auto IntroScene::onMouseDown(Uint8 mouseButton) -> void
    {
        SceneManager::instance().goToScene("MainMenuScene");
    }

    auto IntroScene::onKeyDown(SDL_Keycode key) -> void
    {
        SceneManager::instance().goToScene("MainMenuScene");
    }

    auto IntroScene::updateDerived() -> void
    {
        m_startText->setVisible(getTicks() % 800 < 400);
        Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
    }

    auto IntroScene::renderDerived() const -> void
    {
        Image2DRenderer::instance().drawImageByName(
            hash("IntroSceneBackground"), "DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);

        Image2DRenderer::instance().drawImageAutoHeight(hash("IntroSceneLogo"), "ForradiaLogo",
                                                        0.25f, 0.2f, 0.5f);
    }
}
