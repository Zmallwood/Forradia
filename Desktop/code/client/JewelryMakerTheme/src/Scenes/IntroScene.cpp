/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "IntroScene.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/GUICore/GUILabel.hpp"
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto IntroScene::initializeDerived() -> void
    {
        constexpr RectF k_defaultLabelBounds{0.45F, 0.5F, 0.1F, 0.04F};

        auto label{std::make_shared<GUILabel>("GUILabelIntroSceneStartText", k_defaultLabelBounds.x,
                                              k_defaultLabelBounds.y, k_defaultLabelBounds.width,
                                              k_defaultLabelBounds.height, "Press to start", true)};

        m_startText = getGUI()->addChildComponent(label);
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
        constexpr int k_blinkInterval{800};
        constexpr int k_blinkIntervalHalf{k_blinkInterval / 2};

        m_startText->setVisible(getTicks() % k_blinkInterval < k_blinkIntervalHalf);

        Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
    }

    auto IntroScene::renderDerived() const -> void
    {
        constexpr RectF k_defaultBackgroundBounds{0.0F, 0.0F, 1.0F, 1.0F};

        Image2DRenderer::instance().drawImageByName(
            hash("IntroSceneBackground"), "DefaultSceneBackground", k_defaultBackgroundBounds.x,
            k_defaultBackgroundBounds.y, k_defaultBackgroundBounds.width,
            k_defaultBackgroundBounds.height);

        constexpr RectF k_defaultLogoBounds{0.25F, 0.2F, 0.5F};

        Image2DRenderer::instance().drawImageAutoHeight(
            hash("IntroSceneLogo"), "JewelryMakerLogo", k_defaultLogoBounds.x,
            k_defaultLogoBounds.y, k_defaultLogoBounds.width);
    }
}
