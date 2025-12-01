//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SceneManager.hpp"
#include "IScene.hpp"

namespace AAK
{
    namespace Forradia
    {
        void SceneManager::AddScene(StringView sceneName, IScene &scene)
        {
            // Initialize the scene.

            scene.Initialize();

            // Add the scene to the map.

            m_scenes.insert({Hash(sceneName), scene});
        }

        void SceneManager::GoToScene(StringView sceneName)
        {
            // Calculate hash.

            m_currentScene = Hash(sceneName);

            // Check if the scene is in the map.

            if (m_scenes.contains(m_currentScene))
            {
                // Call the OnEnter function of the scene.

                m_scenes.at(m_currentScene).OnEnter();
            }
        }

        void SceneManager::UpdateCurrentScene()
        {
            // Check if the scene is in the map.

            if (m_scenes.contains(m_currentScene))
            {
                // Call the Update function of the scene.

                m_scenes.at(m_currentScene).Update();
            }
        }

        void SceneManager::RenderCurrentScene() const
        {
            // Check if the scene is in the map.

            if (m_scenes.contains(m_currentScene))
            {
                // Call the Render function of the scene.

                m_scenes.at(m_currentScene).Render();
            }
        }
    }
}