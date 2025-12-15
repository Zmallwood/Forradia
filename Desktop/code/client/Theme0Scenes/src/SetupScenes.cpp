//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SetupScenes.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "MainScene.hpp"
#include "PlayScene.hpp"
#include "SceneManager.hpp"
#include "WorldGenerationScene.hpp"

namespace Forradia::Theme0
{
    void SetupScenes()
    {
        _<SceneManager>().AddScene("IntroScene", _<IntroScene>());
        _<SceneManager>().AddScene("MainMenuScene", _<MainMenuScene>());
        _<SceneManager>().AddScene("PlayScene", _<PlayScene>());
        _<SceneManager>().AddScene("WorldGenerationScene", _<WorldGenerationScene>());
        _<SceneManager>().AddScene("MainScene", _<MainScene>());

        _<SceneManager>().GoToScene("IntroScene");
    }
}