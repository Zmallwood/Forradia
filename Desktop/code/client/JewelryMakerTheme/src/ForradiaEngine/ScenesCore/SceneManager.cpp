/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "SceneManager.hpp"
    #include "ForradiaEngine/Common/General.hpp"
    #include "IScene.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto SceneManager::addScene(std::string_view sceneName, IScene &scene) -> void
    {
        scene.initialize();

        m_scenes.insert({hash(sceneName), scene});
    }

    auto SceneManager::goToScene(std::string_view sceneName) -> void
    {
        m_currentScene = hash(sceneName);

        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onEnter();
        }
    }

    auto SceneManager::onMouseDownCurrentScene(Uint8 mouseButton) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onMouseDown(mouseButton);
        }
    }

    auto SceneManager::onMouseUpCurrentScene(Uint8 mouseButton, int clickSpeed) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onMouseUp(mouseButton, clickSpeed);
        }
    }

    auto SceneManager::onMouseWheelCurrentScene(int delta) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onMouseWheel(delta);
        }
    }

    auto SceneManager::onKeyDownCurrentScene(SDL_Keycode key) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onKeyDown(key);
        }
    }

    auto SceneManager::onKeyUpCurrentScene(SDL_Keycode key) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onKeyUp(key);
        }
    }

    auto SceneManager::onTextInputCurrentScene(std::string_view text) -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).onTextInput(text);
        }
    }

    auto SceneManager::updateCurrentScene() -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).update();
        }
    }

    auto SceneManager::renderCurrentScene() const -> void
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).render();
        }
    }

    auto SceneManager::getScene(std::string_view sceneName) -> IScene *
    {
        auto sceneHash{hash(sceneName)};

        if (m_scenes.contains(sceneHash))
        {
            return &m_scenes.at(sceneHash);
        }

        return nullptr;
    }
}
