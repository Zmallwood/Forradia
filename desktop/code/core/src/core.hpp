/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

#include "gui.hpp"
#include "render.hpp"

_NS_START_

namespace Core
{
    class Engine
    {
      public:
        class SDLDevice
        {
          public:
            ~SDLDevice();

            void Initialize(StringView game_win_title, Color clear_color);

            void ClearCanvas() const;

            void PresentCanvas() const;

            auto GetWindow() const
            {
                return window_;
            }

          private:
            SharedPtr<SDL_Window> CreateWindow();

            Size GetScreenSize() const;

            SharedPtr<SDL_Window> window_;
            SharedPtr<SDL_GLContext> context_;
            String game_win_title_;
            Color clear_color_;
        };

        class FPSCounter
        {
          public:
            void Update();

            auto GetFPS() const
            {
                return fps_;
            }

          private:
            const PointF k_position{0.93f, 0.02f};

            int fps_{0};
            int frames_count_{0};
            int ticks_last_update_{0};
        };

        class Cursor
        {
          public:
            enum class CursorStyles
            {
                normal,
                hovering_clickable_gui,
                hovering_creature
            };

            Cursor()
            {
                Initialize();
            }

            void ResetStyleToNormal();

            void Render();

            auto SetCursorStyle(CursorStyles value)
            {
                cursor_style_ = value;
            }

          private:
            void Initialize();

            void DisableSystemCursor();

            constexpr static float k_curs_sz{0.05f};

            CursorStyles cursor_style_{CursorStyles::normal};
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

                    GLuint GetTexture(int img_name_hash) const;

                    Size GetImageSize(int img_name_hash) const;

                    bool TextTextureExists(float x, float y, int unique_id) const;

                    GLuint ObtainTextTexture(float x, float y, int text_hash);

                  private:
                    void Initialize();

                    void Cleanup();

                    void LoadImages();

                    GLuint LoadSingleTexture(SharedPtr<SDL_Surface> surf);

                    inline static const String k_rel_imgs_path{"./res/images/"};

                    std::map<int, GLuint> textures_;
                    std::map<int, Size> tex_sizes_;
                    std::map<float, std::map<float, std::map<int, GLuint>>>
                        text_texes_;
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
                        glm::vec2 tex_coord;
                        glm::vec3 tangent;
                        glm::vec3 bitangent;
                    };

                    class Texture
                    {
                      public:
                        String path_;
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
                        Model(StringView file_path)
                        {
                            Initialize(file_path);
                        };

                        auto &GetMeshesRef() const
                        {
                            return meshes_;
                        }

                      private:
                        void Initialize(StringView file_path);

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

                        Vector<Mesh> meshes_;
                    };

                  public:
                    ModelBank()
                    {
                        Initialize();
                    }

                    SharedPtr<Model> GetModel(int model_name_hash) const;

                  private:
                    void Initialize();

                    SharedPtr<Model> LoadSingleModel(StringView file_path);

                    inline static const String k_rel_models_path{"./res/models/"};

                    std::map<int, SharedPtr<Model>> models_;
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
                    initialize_derived_ = value;
                }

                void SetOnEnterDerived(Function<void()> value)
                {
                    on_enter_derived_ = value;
                }

                void SetUpdateDerived(Function<void()> value)
                {
                    update_derived_ = value;
                }

                void SetRenderDerived(Function<void()> value)
                {
                    render_derived_ = value;
                }

              protected:
                auto GetGUI() const
                {
                    return gui_;
                }

              private:
                SharedPtr<ScenesGUI::GUIRoot> gui_;
                Function<void()> initialize_derived_{[] {}};
                Function<void()> on_enter_derived_{[] {}};
                Function<void()> update_derived_{[] {}};
                Function<void()> render_derived_{[] {}};
            };

            class SceneManager
            {
              public:
                void AddScene(StringView scene_name, IScene &scene);

                void GoToScene(StringView scene_name);

                void UpdateCurrentScene();

                void RenderCurrentScene() const;

              private:
                std::map<int, IScene &> scenes_;
                int curr_scene_{0};
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
                std::set<SDL_Keycode> pressed_;
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
                    bool pressed_{false};
                    bool been_fired_{false};
                    bool been_released_{false};
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

                void RegisterMouseButtonDown(Uint8 btn);

                void RegisterMouseButtonUp(Uint8 btn);

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

        void Initialize(StringView game_win_title, Color clear_color) const;

        void Run();

        void Stop();

      private:
        void PollEvents();

        bool running_{true};
    };
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
    _HIDE_FROM_OUTLINER_CORE_BOTTOM_
    using namespace Core;
    _NS_END_