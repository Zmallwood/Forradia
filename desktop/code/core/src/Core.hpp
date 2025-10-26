//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUI.hpp"

#include "Rendering.hpp"

namespace Forradia
{
    class Engine
    {
      public:
        class ScenesCore
        {
          public:
            class IScene
            {
              public:
                class ScenesGUI
                {
                  public:
                    class GUIRoot : public GUIComponent
                    {
                      public:
                        GUIRoot()
                            : GUIComponent(0.0f, 0.0f, 1.0f,
                                           1.0f)
                        {
                        }
                    };
                };

                void Initialize();

                void Update();

                void Render() const;

                void OnEnter();

                void
                SetInitializeDerived(Function<void()> value)
                {
                    m_initializeDerived = value;
                }

                void
                SetOnEnterDerived(Function<void()> value)
                {
                    m_onEnterDerived = value;
                }

                void
                SetUpdateDerived(Function<void()> value)
                {
                    m_updateDerived = value;
                }

                void
                SetRenderDerived(Function<void()> value)
                {
                    m_renderDerived = value;
                }

              protected:
                auto GetGUI() const
                {
                    return m_gui;
                }

              private:
                SharedPtr<ScenesGUI::GUIRoot> m_gui;

                Function<void()> m_initializeDerived{[] {}};

                Function<void()> m_onEnterDerived{[] {}};

                Function<void()> m_updateDerived{[] {}};

                Function<void()> m_renderDerived{[] {}};
            };

            class SceneManager
            {
              public:
                void AddScene(StringView sceneName,
                              IScene &scene);

                void GoToScene(StringView sceneName);

                void UpdateCurrentScene();

                void RenderCurrentScene() const;

              private:
                std::map<int, IScene &> m_scenes;
                int m_currentScene{0};
            };
        };
        class Input
        {
          public:
            class KeyboardInput
            {
              public:
                void Reset();

                void RegisterKeyPress(SDL_Keycode key);

                void RegisterKeyRelease(SDL_Keycode key);

                bool KeyIsPressed(SDL_Keycode key) const;

                bool
                KeyIsPressedPickResult(SDL_Keycode key);

                bool AnyKeyIsPressedPickResult();

              private:
                std::set<SDL_Keycode> m_pressed;
            };

            class MouseInput
            {
              public:
                class MouseButton
                {
                  public:
                    void Reset();

                    void RegisterPress();

                    void RegisterRelease();

                    bool IsPressedPickResult();

                    bool HasBeenFiredPickResult();

                    bool HasBeenFired();

                    bool HasBeenReleasedPickResult();

                    bool HasBeenReleased();

                  private:
                    bool m_pressed{false};

                    bool m_hasBeenFired{false};

                    bool m_hasBeenReleased{false};
                };

                class LeftMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::Reset;

                    using MouseButton::RegisterPress;

                    using MouseButton::RegisterRelease;

                    using MouseButton::IsPressedPickResult;

                    using MouseButton::
                        HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::
                        HasBeenReleasedPickResult;

                    using MouseButton::HasBeenReleased;
                };

                class RightMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::Reset;

                    using MouseButton::RegisterPress;

                    using MouseButton::RegisterRelease;

                    using MouseButton::IsPressedPickResult;

                    using MouseButton::
                        HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::
                        HasBeenReleasedPickResult;

                    using MouseButton::HasBeenReleased;
                };

                void Reset();

                void RegisterMouseButtonDown(Uint8 button);

                void RegisterMouseButtonUp(Uint8 button);

                bool AnyMouseButtonIsPressedPickResult();
            };
        };
        class Renderers : public RenderersCollection
        {
          public:
            using RenderersCollection::FontSizes;

            using RenderersCollection::GroundRenderer;

            using RenderersCollection::Image2DRenderer;

            using RenderersCollection::ModelRenderer;

            using RenderersCollection::TextRenderer;
        };

        void Initialize(StringView gameWindowTitle,
                        Color clearColor) const;

        void Run();

        void Stop();

      private:
        void PollEvents();

        bool m_running{true};
    };
}