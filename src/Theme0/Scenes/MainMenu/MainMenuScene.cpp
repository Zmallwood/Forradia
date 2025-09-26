#include "MainMenuScene.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    void MainMenuScene::UpdateDerived()
    {
        if (_<KeyboardInput>().AnyKeyIsPressedPickResult())
        {
            _<SceneManager>().GoToScene("WorldGenerationScene");
        }
    }

    void MainMenuScene::RenderDerived() const
    {
        _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
    }
}
