//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//

#pragma once

#include "GUI.hpp"
#include "Render.hpp"

namespace Forradia
{
namespace Core
{
    class Engine
    {
      public:
        class SDLDevice
        {
          public:
            ~SDLDevice();

            void Initialize(StringView gameWindowTitle, Color clearColor);

            void ClearCanvas() const;

            void PresentCanvas() const;

            auto GetWindow() const
            {
                return m_window;
            }

          private:
            SharedPtr<SDL_Window> CreateWindow();

            Size GetScreenSize() const;

            SharedPtr<SDL_Window> m_window;
            SharedPtr<SDL_GLContext> m_context;
            String m_gameWindowTitle;
            Color m_clearColor;
        };

        class FPSCounter
        {
          public:
            void Update();

            auto GetFPS() const
            {
                return m_fps;
            }

          private:
            const PointF k_position{0.93f, 0.02f};

            int m_fps{0};
            int m_framesCount{0};
            int m_ticksLastUpdate{0};
        };

        class Cursor
        {
          public:
            enum class CursorStyles
            {
                Normal,
                HoveringClickableGUI,
                HoveringCreature
            };

            Cursor()
            {
                Initialize();
            }

            void ResetStyleToNormal();

            void Render();

            auto SetCursorStyle(CursorStyles value)
            {
                m_cursorStyle = value;
            }

          private:
            void Initialize();

            void DisableSystemCursor();

            constexpr static float k_cursorSize{0.05f};

            CursorStyles m_cursorStyle{CursorStyles::Normal};
        };

        class Assets
        {
          public:
            class Images
            {
              public:
                class ImageBank
                {
                  public:
                    ImageBank()
                    {
                        Initialize();
                    }

                    ~ImageBank()
                    {
                        Cleanup();
                    }

                    GLuint GetTexture(int imageNameHash) const;

                    Size GetImageSize(int imageNameHash) const;

                    bool TextTextureExists(float x, float y,
                                           int uniqueID) const;

                    GLuint ObtainTextTexture(float x, float y, int textHash);

                  private:
                    void Initialize();

                    void Cleanup();

                    void LoadImages();

                    GLuint LoadSingleTexture(SharedPtr<SDL_Surface> surface);

                    inline static const String k_relativeImagesPath{
                        "./res/images/"};

                    std::map<int, GLuint> m_textures;
                    std::map<int, Size> m_textureSizes;
                    std::map<float, std::map<float, std::map<int, GLuint>>>
                        m_textTextures;
                };
            };
            class Models
            {
              public:
                class ModelBank
                {
                  public:
                    class Vertex
                    {
                      public:
                        glm::vec3 position;
                        glm::vec3 normal;
                        glm::vec2 uv;
                        glm::vec3 tangent;
                        glm::vec3 bitangent;
                    };

                    class Texture
                    {
                      public:
                        String path;
                    };

                    class Mesh
                    {
                      public:
                        Vector<Vertex> vertices;
                        Vector<unsigned int> indices;
                        Vector<Texture> textures;
                        glm::vec3 extents;
                        glm::vec3 origin;
                        aiString name;
                    };

                    class Model
                    {
                      public:
                        Model(StringView filePath)
                        {
                            Initialize(filePath);
                        };

                        auto &GetMeshesRef() const
                        {
                            return m_meshes;
                        }

                      private:
                        void Initialize(StringView filePath);

                        void ProcessNode(aiNode *node, const aiScene *scene,
                                         aiMatrix4x4 transform);

                        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene,
                                         aiMatrix4x4 transformation);

                        Vector<Vertex> GetVertices(aiMesh *mesh,
                                                   glm::vec3 &extents,
                                                   glm::vec3 &origin,
                                                   aiMatrix4x4 transformation);

                        Vector<unsigned int> GetIndices(aiMesh *mesh);

                        Vector<Texture> GetTextures(aiMesh *mesh,
                                                    const aiScene *scene);

                        Vector<Mesh> m_meshes;
                    };

                  public:
                    ModelBank()
                    {
                        Initialize();
                    }

                    SharedPtr<Model> GetModel(int modelNameHash) const;

                  private:
                    void Initialize();

                    SharedPtr<Model> LoadSingleModel(StringView filePath);

                    inline static const String k_relativeModelsPath{
                        "./res/models/"};

                    std::map<int, SharedPtr<Model>> m_models;
                };
            };
        };
        class ScenesCore
        {
          public:
            class IScene
            {
              public:
                class ScenesGUI
                {
                  public:
                    class GUIRoot : public GUIComponentsLibrary::GUIComponent
                    {
                      public:
                        GUIRoot() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
                        {
                        }
                    };
                };

                void Initialize();

                void Update();

                void Render() const;

                void OnEnter();

                void SetInitializeDerived(Function<void()> value)
                {
                    m_initializeDerived = value;
                }

                void SetOnEnterDerived(Function<void()> value)
                {
                    m_onEnterDerived = value;
                }

                void SetUpdateDerived(Function<void()> value)
                {
                    m_updateDerived = value;
                }

                void SetRenderDerived(Function<void()> value)
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
                void AddScene(StringView sceneName, IScene &scene);

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

                bool KeyIsPressedPickResult(SDL_Keycode key);

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

                    using MouseButton::HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::HasBeenReleasedPickResult;

                    using MouseButton::HasBeenReleased;
                };

                class RightMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::Reset;

                    using MouseButton::RegisterPress;

                    using MouseButton::RegisterRelease;

                    using MouseButton::IsPressedPickResult;

                    using MouseButton::HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::HasBeenReleasedPickResult;

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

        void Initialize(StringView gameWindowTitle, Color clearColor) const;

        void Run();

        void Stop();

      private:
        void PollEvents();

        bool m_running{true};
    };
}
using namespace Core;
}