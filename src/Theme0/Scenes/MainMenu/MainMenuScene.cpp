/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainMenuScene.hpp"
#include "AddMainMenuSceneGUIComponents/AddMainMenuSceneGUIComponents.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    void MainMenuScene::InitializeDerived()
    {
        AddMainMenuSceneGUIComponents(GetGUI());
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
