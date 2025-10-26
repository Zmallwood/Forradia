//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Core.hpp"

#include "GLDevice.hpp"

#include "MinorComponents/Cursor.hpp"

#include "MinorComponents/FPSCounter.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void Engine::Initialize(StringView gameWindowTitle,
                            Color clearColor) const
    {
        Randomize();

        _<SDLDevice>().Initialize(gameWindowTitle,
                                  clearColor);

        _<GLDevice>().Initialize();
    }

    void Engine::Run()
    {
        try
        {
            while (m_running)
            {
                _<Input::MouseInput>().Reset();

                _<Cursor>().ResetStyleToNormal();

                this->PollEvents();

                _<ScenesCore::SceneManager>()
                    .UpdateCurrentScene();

                _<FPSCounter>().Update();

                _<SDLDevice>().ClearCanvas();

                _<ScenesCore::SceneManager>()
                    .RenderCurrentScene();

                _<Cursor>().Render();

                _<SDLDevice>().PresentCanvas();
            }
        }
        catch (std::exception &e)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                     "Error", e.what(),
                                     nullptr);
        }
    }

    void Engine::Stop()
    {
        m_running = false;
    }

    void Engine::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                this->Stop();

                break;

            case SDL_KEYDOWN:

                _<Input::KeyboardInput>().RegisterKeyPress(
                    event.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<Input::KeyboardInput>()
                    .RegisterKeyRelease(
                        event.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<Input::MouseInput>()
                    .RegisterMouseButtonDown(
                        event.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<Input::MouseInput>()
                    .RegisterMouseButtonUp(
                        event.button.button);

                break;
            }
        }
    }

    void Engine::ScenesCore::IScene::Initialize()
    {
        m_gui =
            std::make_shared<Engine::ScenesCore::IScene::
                                 ScenesGUI::GUIRoot>();

        m_initializeDerived();
    }

    void Engine::ScenesCore::IScene::OnEnter()
    {
        m_onEnterDerived();
    }

    void Engine::ScenesCore::IScene::Update()
    {
        m_gui->Update();

        m_updateDerived();
    }

    void Engine::ScenesCore::IScene::Render() const
    {
        m_renderDerived();

        m_gui->Render();
    }

    void Engine::ScenesCore::SceneManager::AddScene(
        StringView sceneName, IScene &scene)
    {
        scene.Initialize();

        m_scenes.insert({Hash(sceneName), scene});
    }

    void Engine::ScenesCore::SceneManager::GoToScene(
        StringView sceneName)
    {
        m_currentScene = Hash(sceneName);

        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).OnEnter();
        }
    }

    void
    Engine::ScenesCore::SceneManager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Update();
        }
    }

    void
    Engine::ScenesCore::SceneManager::RenderCurrentScene()
        const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Render();
        }
    }

    void Engine::Input::KeyboardInput::Reset()
    {
        m_pressed.clear();
    }

    void Engine::Input::KeyboardInput::RegisterKeyPress(
        SDL_Keycode key)
    {
        m_pressed.insert(key);
    }

    void Engine::Input::KeyboardInput::RegisterKeyRelease(
        SDL_Keycode key)
    {
        m_pressed.erase(key);
    }

    bool Engine::Input::KeyboardInput::KeyIsPressed(
        SDL_Keycode key) const
    {
        return m_pressed.contains(key);
    }

    bool
    Engine::Input::KeyboardInput::KeyIsPressedPickResult(
        SDL_Keycode key)
    {
        auto result{m_pressed.contains(key)};

        m_pressed.erase(key);

        return result;
    }

    bool Engine::Input::KeyboardInput::
        AnyKeyIsPressedPickResult()
    {
        auto result{m_pressed.size() > 0};

        m_pressed.clear();

        return result;
    }

    void Engine::Input::MouseInput::MouseButton::Reset()
    {
        m_pressed = false;

        m_hasBeenFired = false;

        m_hasBeenReleased = false;
    }

    void
    Engine::Input::MouseInput::MouseButton::RegisterPress()
    {
        m_pressed = true;

        m_hasBeenFired = true;
    }

    void Engine::Input::MouseInput::MouseButton::
        RegisterRelease()
    {
        m_pressed = false;

        m_hasBeenReleased = true;
    }

    bool Engine::Input::MouseInput::MouseButton::
        IsPressedPickResult()
    {
        auto result{m_pressed};

        m_pressed = false;

        return result;
    }

    bool Engine::Input::MouseInput::MouseButton::
        HasBeenFiredPickResult()
    {
        auto result{m_hasBeenFired};

        m_hasBeenFired = false;

        return result;
    }

    bool
    Engine::Input::MouseInput::MouseButton::HasBeenFired()
    {
        return m_hasBeenFired;
    }

    bool Engine::Input::MouseInput::MouseButton::
        HasBeenReleasedPickResult()
    {
        auto result{m_hasBeenReleased};

        m_hasBeenReleased = false;

        return result;
    }

    bool Engine::Input::MouseInput::MouseButton::
        HasBeenReleased()
    {
        return m_hasBeenReleased;
    }

    void Engine::Input::MouseInput::Reset()
    {
        _<LeftMouseButton>().Reset();

        _<RightMouseButton>().Reset();
    }

    void Engine::Input::MouseInput::RegisterMouseButtonDown(
        Uint8 button)
    {
        switch (button)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().RegisterPress();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().RegisterPress();

            break;
        }
    }

    void Engine::Input::MouseInput::RegisterMouseButtonUp(
        Uint8 button)
    {
        switch (button)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().RegisterRelease();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().RegisterRelease();

            break;
        }
    }

    bool Engine::Input::MouseInput::
        AnyMouseButtonIsPressedPickResult()
    {
        auto result{
            _<LeftMouseButton>().IsPressedPickResult()};

        result |=
            _<RightMouseButton>().IsPressedPickResult();

        return result;
    }
}