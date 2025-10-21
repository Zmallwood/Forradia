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

            void init(StringView game_win_title, Color clear_color);

            void clear_canv() const;

            void present_canv() const;

            auto win() const
            {
                return win_;
            }

            auto rend() const
            {
                return rend_;
            }

          private:
            SharedPtr<SDL_Window> create_win();

            Size get_screen_sz() const;

            SharedPtr<SDL_Window> win_;
            SharedPtr<SDL_GLContext> context_;
            SharedPtr<SDL_Renderer> rend_;
            String game_win_title_;
            Color clear_color_;
        };

        class FPSCounter
        {
          public:
            void update();

            auto fps() const
            {
                return fps_;
            }

          private:
            int fps_{0};
            int frames_count_{0};
            int ticks_last_update_{0};
            const PointF k_position{0.93f, 0.02f};
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
                init();
            }

            void reset_style_to_normal();

            void render();

            auto set_curs_style(CursorStyles val)
            {
                curs_style_ = val;
            }

          private:
            void init();

            void disable_sys_curs();

            constexpr static float k_curs_sz{0.05f};

            CursorStyles curs_style_{CursorStyles::normal};
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
                        init();
                    }

                    ~ImageBank()
                    {
                        cleanup();
                    }

                    GLuint get_tex(int img_name_hash) const;

                    Size get_img_sz(int img_name_hash) const;

                    bool text_tex_exists(float x, float y, int unique_id) const;

                    GLuint obtain_text_tex(float x, float y, int text_hash);

                  private:
                    void init();

                    void cleanup();

                    void load_imgs();

                    GLuint load_single_tex(SharedPtr<SDL_Surface> surf);

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
                            init(file_path);
                        };

                        auto &meshes_ref() const
                        {
                            return meshes_;
                        }

                      private:
                        void init(StringView file_path);

                        void process_node(aiNode *node, const aiScene *scene,
                                          aiMatrix4x4 transform);

                        Mesh process_mesh(aiMesh *mesh, const aiScene *scene,
                                          aiMatrix4x4 transformation);

                        Vector<Vertex> get_vertices(aiMesh *mesh,
                                                 glm::vec3 &extents,
                                                 glm::vec3 &origin,
                                                 aiMatrix4x4 transformation);

                        Vector<unsigned int> get_indices(aiMesh *mesh);

                        Vector<Texture> get_textures(aiMesh *mesh,
                                                  const aiScene *scene);

                        Vector<Mesh> meshes_;
                    };

                  public:
                    ModelBank()
                    {
                        init();
                    }

                    SharedPtr<Model> get_model(int model_name_hash) const;

                  private:
                    void init();

                    SharedPtr<Model> load_single_model(StringView file_path);

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

                void init();

                void update();

                void render() const;

                void on_enter();

                void set_init_derived(Function<void()> value)
                {
                    init_derived_ = value;
                }

                void set_on_enter_derived(Function<void()> value)
                {
                    on_enter_derived_ = value;
                }

                void set_update_derived(Function<void()> value)
                {
                    update_derived_ = value;
                }

                void set_render_derived(Function<void()> value)
                {
                    render_derived_ = value;
                }

              protected:
                auto gui() const
                {
                    return gui_;
                }

              private:
                SharedPtr<ScenesGUI::GUIRoot> gui_;
                Function<void()> init_derived_{[] {}};
                Function<void()> on_enter_derived_{[] {}};
                Function<void()> update_derived_{[] {}};
                Function<void()> render_derived_{[] {}};
            };

            class SceneManager
            {
              public:
                void add_scene(StringView scene_name, IScene &scene);

                void go_to_scene(StringView scene_name);

                void update_curr_scene();

                void render_curr_scene() const;

              private:
                std::map<int, IScene &> scenes_;
                int curr_scene_{0};
            };
        };
        class Input
        {
          public:
            ////////////////////
            // Keyboard
            ////////////////////
            class KeyboardInput
            {
              public:
                void reset();

                void reg_key_press(SDL_Keycode key);

                void reg_key_release(SDL_Keycode key);

                bool key_pressed(SDL_Keycode key) const;

                bool key_pressed_pick_res(SDL_Keycode key);

                bool any_key_pressed_pick_res();

              private:
                std::set<SDL_Keycode> pressed_;
            };

            ////////////////////
            // Mouse
            ////////////////////
            class MouseInput
            {
              public:
                class MouseButton
                {
                  public:
                    void reset();

                    void reg_press();

                    void reg_release();

                    bool pressed_pick_res();

                    bool been_fired_pick_res();

                    bool been_fired_no_pick_res();

                    bool been_released_pick_res();

                    bool been_released_no_pick_res();

                  private:
                    bool pressed_{false};
                    bool been_fired_{false};
                    bool been_released_{false};
                };

                class LeftMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::reset;

                    using MouseButton::reg_press;

                    using MouseButton::reg_release;

                    using MouseButton::pressed_pick_res;

                    using MouseButton::been_fired_pick_res;

                    using MouseButton::been_fired_no_pick_res;

                    using MouseButton::been_released_pick_res;

                    using MouseButton::been_released_no_pick_res;
                };

                class RightMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::reset;

                    using MouseButton::reg_press;

                    using MouseButton::reg_release;

                    using MouseButton::pressed_pick_res;

                    using MouseButton::been_fired_pick_res;

                    using MouseButton::been_fired_no_pick_res;

                    using MouseButton::been_released_pick_res;

                    using MouseButton::been_released_no_pick_res;
                };

                void reset();

                void reg_mouse_btn_down(Uint8 btn);

                void reg_mouse_btn_up(Uint8 btn);

                bool any_mouse_btn_pressed_pick_res();
            };
        };
        class Renderers : public RenderersCollection
        {
          public:
            using RenderersCollection::font_szs;
            using RenderersCollection::ground_rend;
            using RenderersCollection::img_2d_rend;
            using RenderersCollection::model_rend;
            using RenderersCollection::text_rend;
        };

        void init(StringView game_win_title, Color clear_color) const;

        void run();

        void stop();

      private:
        void poll_events();

        bool running_{true};
    };
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
    _HIDE_FROM_OUTLINER_CORE_BOTTOM_
    using namespace Core;
    _NS_END_