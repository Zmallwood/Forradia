#include "SceneManager.hpp"
#include "IScene.hpp"
#include "Theme0/Scenes/Intro/IntroScene.hpp"
#include "Theme0/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme0/Scenes/WorldGeneration/WorldGenerationScene.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace Forradia
{
    SceneManager::SceneManager()
    {
        AddScene("IntroScene", _<IntroScene>());
        AddScene("MainMenuScene", _<MainMenuScene>());
        AddScene("WorldGenerationScene", _<WorldGenerationScene>());
        AddScene("MainScene", _<MainScene>());

        GoToScene("IntroScene");
    }

    void SceneManager::AddScene(std::string_view sceneName,
                                IScene &scene)
    {
        scene.Initialize();

        m_scenes.insert({Hash(sceneName), scene});
    }

    void SceneManager::GoToScene(std::string_view sceneName)
    {
        m_currentScene = Hash(sceneName);

        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).OnEnter();
        }
    }

    void SceneManager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Update();
        }
    }

    void SceneManager::RenderCurrentScene() const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Render();
        }
    }
}
