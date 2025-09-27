/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainMenuScene.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    void MainMenuScene::UpdateDerived()
    {
        if (_<KeyboardInput>().AnyKeyIsPressedPickResult() ||
            _<MouseInput>().AnyMouseButtonIsPressedPickResult())
        {
            _<SceneManager>().GoToScene("WorldGenerationScene");
        }
    }

    void MainMenuScene::RenderDerived() const
    {
        _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
        _<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.35f, 0.1f, 0.3f);
    }
}
