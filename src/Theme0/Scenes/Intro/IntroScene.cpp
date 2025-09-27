/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "IntroScene.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUILabel.hpp"

namespace Forradia
{
    void IntroScene::Initialize()
    {
        m_startText = GetGUI()->AddChildComponent(
            std::make_shared<GUILabel>(
                0.45f,
                0.5f,
                0.1f,
                0.04f,
                "Press to start"));
    }

    void IntroScene::UpdateDerived()
    {
        m_startText->SetVisible((GetTicks() % 800) < 400);

        if (_<KeyboardInput>().AnyKeyIsPressedPickResult() ||
            _<MouseInput>().AnyMouseButtonIsPressedPickResult())
        {
            _<SceneManager>().GoToScene("MainMenuScene");
        }
    }

    void IntroScene::RenderDerived() const
    {
        _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
        _<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.2f, 0.2f, 0.6f);
    }
}
