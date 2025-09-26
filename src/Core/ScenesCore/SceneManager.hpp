#pragma once

namespace Forradia
{
    class IScene;

    class SceneManager
    {
    public:
        SceneManager();

        void GoToScene(std::string_view sceneName);

        void UpdateCurrentScene();

        void RenderCurrentScene() const;

    private:
        void AddScene(std::string_view sceneName,
                      IScene &scene);

        std::map<int, IScene &> m_scenes;
        int m_currentScene{0};
    };
}
