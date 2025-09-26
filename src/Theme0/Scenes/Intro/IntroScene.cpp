/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "IntroScene.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    void IntroScene::UpdateDerived()
    {
        if (_<KeyboardInput>().AnyKeyIsPressedPickResult())
        {
            _<SceneManager>().GoToScene("MainMenuScene");
        }
    }

    void IntroScene::RenderDerived() const
    {
        _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
        _<ImageRenderer>().DrawImage("ForradiaLogo", 0.2f, 0.2f, 0.6f);
    }
}
