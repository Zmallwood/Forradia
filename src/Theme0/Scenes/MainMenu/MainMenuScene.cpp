/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainMenuScene.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/Engine/Engine.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIPanel.hpp"
#include "Core/GUICore/GUIButton.hpp"

namespace Forradia
{
    void MainMenuScene::Initialize()
    {
        GetGUI()->AddChildComponent(
            std::make_shared<GUIPanel>(0.4f, 0.32f, 0.2f, 0.2f));

        GetGUI()->AddChildComponent(
            std::make_shared<GUIButton>(
                0.45f,
                0.36f,
                0.1f,
                0.04f,
                "Login",
                []
                {
                    _<SceneManager>().GoToScene("WorldGenerationScene");
                }));

        GetGUI()->AddChildComponent(
            std::make_shared<GUIButton>(
                0.45f,
                0.44f,
                0.1f,
                0.04f,
                "Quit",
                []
                {
                    _<Engine>().Stop();
                }));
    }

    void MainMenuScene::UpdateDerived()
    {
    }

    void MainMenuScene::RenderDerived() const
    {
        _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
        _<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.35f, 0.1f, 0.3f);
    }
}
