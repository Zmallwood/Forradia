/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SceneManager.hpp"
#include "IScene.hpp"

namespace Forradia
{
    auto SceneManager::AddScene(std::string_view sceneName, IScene &scene) -> void
    {
        scene.Initialize();

        m_scenes.insert({Hash(sceneName), scene});
    }

    auto SceneManager::GoToScene(std::string_view sceneName) -> void
    {
        m_currentScene = Hash(sceneName);

        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnEnter();
    }

    auto SceneManager::OnMouseDownCurrentScene(Uint8 mouseButton) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnMouseDown(mouseButton);
    }

    auto SceneManager::OnMouseUpCurrentScene(Uint8 mouseButton, int clickSpeed) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnMouseUp(mouseButton, clickSpeed);
    }

    auto SceneManager::OnMouseWheelCurrentScene(int delta) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnMouseWheel(delta);
    }

    auto SceneManager::OnKeyDownCurrentScene(SDL_Keycode key) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnKeyDown(key);
    }

    auto SceneManager::OnKeyUpCurrentScene(SDL_Keycode key) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnKeyUp(key);
    }

    auto SceneManager::OnTextInputCurrentScene(std::string_view text) -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnTextInput(text);
    }

    auto SceneManager::UpdateCurrentScene() -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Update();
    }

    auto SceneManager::RenderCurrentScene() const -> void
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Render();
    }

    auto SceneManager::GetScene(std::string_view sceneName) -> IScene *
    {
        auto sceneHash{Hash(sceneName)};
        if (m_scenes.contains(sceneHash))
            return &m_scenes.at(sceneHash);
        return nullptr;
    }
}
