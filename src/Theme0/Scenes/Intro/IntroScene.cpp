#include "IntroScene.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Rendering/ImageRenderer.hpp"

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
    }
}
