#pragma diag_suppress 266
#pragma diag_suppress 311
#pragma diag_suppress 20
#pragma diag_suppress 283
#pragma diag_suppress 65
#pragma diag_suppress 77
#pragma diag_suppress 146
#pragma diag_suppress 281
#pragma diag_suppress 18
#pragma diag_suppress 28

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_ }
    _HIDE_FROM_OUTLINER_

// virtualInclude 'code/common/src/common.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#define _NS_START_                                                             \
    namespace Forradia                                                         \
    {
#define _NS_END_ }

#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
typedef struct _TTF_Font TTF_Font;
struct SDL_Color;
typedef uint8_t Uint8;

_NS_START_
namespace Common
{
    ////////////////////
    // Convenience
    ////////////////////
    namespace Aliases
    {
        // A set of aliases for commonly used types.
        using String = std::string;
        using StringView = std::string_view;
        template <class T> using SharedPtr = std::shared_ptr<T>;
        template <class T> using Vector = std::vector<T>;
        template <class T> using Function = std::function<T>;
    }
    using namespace Aliases;
    namespace Constants
    {
        // Constants that may be used throughout the project.
        static constexpr int k_one_sec_millis{
            1000}; ///< Number of milliseconds in one second.
    }
    using namespace Constants;
    namespace Singletons
    {
        // Singleton functions
        /**
         * Returns a singleton of an object of type T, in the
         * form of a SharedPtr.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a SharedPtr.
         */
        template <class T> SharedPtr<T> __()
        {
            // Create singleton instance only once.
            static SharedPtr<T> inst = std::make_shared<T>();
            return inst;
        }

        /**
         * Returns a singleton of an object of type T, in the
         * form of a reference.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a reference.
         */
        template <class T> T &_()
        {
            // Use the SharedPtr singleton function to obtain
            // the singleton, but return a reference to it.
            return *__<T>();
        }
    }
    using namespace Singletons;
    namespace HelperClasses
    {
        // Convenience classes
        /**
         * Class used for SharedPtrs of SDL objects,
         * which handles automaticallyfreeing up resources at object deletion.
         */
        class SDLDeleter
        {
          public:
            /**
             * Operator overloading for SDL_Window objects.
             *
             * \param win SDL window pointer to free resources for.
             */
            void operator()(SDL_Window *win) const;

            /**
             * Operator overloading for SDL_Renderer objects.
             *
             * \param rend SDL renderer pointer to free resources for.
             */
            void operator()(SDL_Renderer *rend) const;

            /**
             * Operator overloading for SDL_Surface objects.
             *
             * \param surf SDL surface pointer to free resources for.
             */
            void operator()(SDL_Surface *surf) const;

            /**
             * Operator overloading for SDL_Texture objects.
             *
             * \param tex SDL texture pointer to free resources for.
             */
            void operator()(SDL_Texture *tex) const;

            /**
             * Operator overloading for TTF_Font objects.
             *
             * \param font SDL font pointer to free resources for.
             */
            void operator()(TTF_Font *font) const;
        };
    }
    using namespace HelperClasses;
    ////////////////////
    // Matter
    ////////////////////
    namespace Matter
    {
        /**
         * Point in 2D space, using dimensions of int type.
         */
        class Point
        {
          public:
            /**
             * Equality operator between two Points.
             *
             * \param p Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const Point &p) const;

            int x{0};
            int y{0};
        };

        /**
         * Point in 2D space using dimensions of float type.
         */
        class PointF
        {
          public:
            /**
             * Summing operator for the two points.
             *
             * \param p The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            PointF operator+(const PointF &p) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param p The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            PointF operator-(const PointF &p) const;

            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
        };

        /**
         * Point in 3D space using dimensions of float type.
         */
        class Point3F
        {
          public:
            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
            float z{0.0f}; ///< The z dimension.
        };

        /**
         * Size in 2D space, with the dimensions as int values.
         */
        class Size
        {
          public:
            int w{0}; ///< Width.
            int h{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class SizeF
        {
          public:
            float w{0.0f}; ///< Width.
            float h{0.0f}; ///< Height.
        };

        /**
         * A rectangle in 2D space using dimensions of float type.
         */
        class RectF
        {
          public:
            /**
             * Check if this rectangle contains a certian point.
             *
             * \param p Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool contains(PointF p);

            /**
             * Returns only the position of this rectangle.
             *
             * \return The position.
             */
            PointF pos() const;

            /**
             * Adds an offset to this rectangle, with the dimensions altered
             * separately.
             *
             * \param offs The offset to add.
             */
            void offs(PointF offs);

            float x{0.0f}; ///< The x coordinate.
            float y{0.0f}; ///< The y coordinate.
            float w{0.0f}; ///< The width, in the x dimension.
            float h{0.0f}; ///< The height, in the y dimension.
        };
        namespace Coloring
        {
            /**
             * A RGBA color with components defined with float values.
             */
            class Color
            {
              public:
                /**
                 * Convert this color to a corresponding SDL_Color object.
                 *
                 * \return Corresponding SDL_Color object.
                 */
                SDL_Color to_sdl_color() const;

                float r{0.0f};
                float g{0.0f};
                float b{0.0f};
                float a{0.0f};
            };

            /**
             * Contains a palette of colors.
             */
            namespace colors
            {
                constexpr Color black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr Color wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr Color wheat_transp{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr Color yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr Color yellow_transp{
                    1.0f, 1.0f, 0.0f, 0.7f}; ///< Transparent yellow color.
            }
        }
        using namespace Coloring;
    }
    using namespace Matter;
    namespace Utilities
    {
        ////////////////////
        // Utils
        ////////////////////
        namespace CanvasUtilities
        {
            // Canvas util functions
            Size get_canv_sz(SharedPtr<SDL_Window> win);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param win Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float calc_aspect_ratio(SharedPtr<SDL_Window> win);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param w Width to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float conv_w_to_h(float w, SharedPtr<SDL_Window> win);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param h Height to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float conv_h_to_w(float h, SharedPtr<SDL_Window> win);
        }
        using namespace CanvasUtilities;
        namespace FilePathUtilities
        {
            // File path util functions
            String file_ext(StringView path);

            String file_name_no_ext(StringView path);
        }
        using namespace FilePathUtilities;
        namespace MouseUtilities
        {
            // Mouse util functions
            PointF norm_mouse_pos(SharedPtr<SDL_Window> win);
        }
        using namespace MouseUtilities;
        namespace NumbersUtilities
        {
            // Numbers util functions
            float inv_movem_spd(float num);

            int normalize(int val);

            float ceil(float num, float k);
        }
        using namespace NumbersUtilities;
        namespace RandomizationUtilities
        {
            // Randomization util functions
            void randomize();

            int rand_int(int upper_lim);
        }
        using namespace RandomizationUtilities;
        namespace StringUtilities
        {
            // String util functions
            String repl(StringView text, char repl, char repl_with);
        }
        using namespace StringUtilities;
        namespace TimeUtilities
        {
            // Time util functions
            int ticks();
        }
        using namespace TimeUtilities;
        namespace HashUtilities
        {
            // Hash util functions
            /**
             * Compute hash code from a given input text, which
             * gets computed the same every game start.
             *
             * \param text Text to compute hash code for.
             * \return Computed hash code.
             */
            int hash(StringView text);
        }
        using namespace HashUtilities;
        namespace PrintUtilities
        {
            // Print util functions
            /**
             * Print out a string of text, without a following line break.
             *
             * \param text Text to print.
             */
            void print(StringView text);

            /**
             * Print out a string of text, with an added line break at the end.
             *
             * \param text Text to print.
             */
            void print_ln(StringView text);
        }
        using namespace PrintUtilities;
        namespace CastUtilities
        {
            // Cast util functions
            /**
             * Cast a value to int.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            constexpr int c_int(auto val)
            {
                return static_cast<int>(val);
            }

            /**
             * Cast a value to float.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            float c_float(auto val)
            {
                return static_cast<float>(val);
            }

            /**
             * Cast a value to Uint8.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            Uint8 c_uint8(auto val)
            {
                return static_cast<Uint8>(val);
            }
        }
        using namespace CastUtilities;
    }
    using namespace Utilities;
}
using namespace Common;
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
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
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/gui.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_TOP_                                           \
    namespace Core                                                             \
    {
_HIDE_FROM_OUTLINER_GUI_TOP_
namespace GUIComponentsLibrary
{
    class GUIComponent
    {
      public:
        GUIComponent(float x, float y, float w, float h) : bounds_({x, y, w, h})
        {
        }

        SharedPtr<GUIComponent> add_child_comp(SharedPtr<GUIComponent> comp);

        void update();

        void render() const;

        virtual RectF bounds() const;

        void set_pos(PointF new_pos);

        void toggle_visible();

        auto visible() const
        {
            return visible_;
        }

        void set_visible(bool val)
        {
            visible_ = val;
        }

        void set_parent_comp(GUIComponent *value)
        {
            parent_comp_ = value;
        }

      protected:
        virtual void update_derived()
        {
        }

        virtual void render_derived() const
        {
        }

      private:
        RectF bounds_;
        Vector<SharedPtr<GUIComponent>> children_;
        bool visible_{true};
        bool enabled_{true};
        GUIComponent *parent_comp_{nullptr};
    };

    class GUILabel : public GUIComponent
    {
      public:
        GUILabel(float x, float y, float w, float h, StringView text = "",
                  bool cent_align = false, Color color = colors::wheat_transp)
            : GUIComponent(x, y, w, h), text_(text), cent_align_(cent_align),
              color_(color)
        {
        }

        void set_text(StringView val)
        {
            text_ = val;
        }

      protected:
        virtual void render_derived() const override;

      private:
        String text_;
        bool cent_align_{false};
        Color color_;
    };

    class GUIPanel : public GUIComponent
    {
      public:
        GUIPanel(float x, float y, float w, float h,
                  StringView bg_img = k_default_bg_img)
            : GUIComponent(x, y, w, h), bg_img_(bg_img)
        {
        }

      protected:
        virtual void render_derived() const override;

        void set_bg_img(StringView val)
        {
            bg_img_ = val;
        }

      private:
        inline static const String k_default_bg_img{"gui_panel_bg"};

        String bg_img_;
    };

    class GUIButton : public GUIPanel
    {
      public:
        GUIButton(float x, float y, float w, float h, StringView text,
                   Function<void()> action, StringView bg_img = k_bg_img,
                   StringView hovered_bg_img = k_hovered_bg_img)
            : GUIPanel(x, y, w, h), text_(text), action_(action),
              bg_img_(bg_img), hovered_bg_img_(hovered_bg_img)
        {
        }

      protected:
        virtual void update_derived() override;

        virtual void render_derived() const override;

      private:
        inline static const String k_bg_img{"gui_button_bg"};
        inline static const String k_hovered_bg_img{"gui_button_hovered_bg"};

        String text_;
        Function<void()> action_;
        String bg_img_;
        String hovered_bg_img_;
    };

    class GUIMovablePanel : public GUIPanel
    {
      public:
        GUIMovablePanel(float x, float y, float w, float h)
            : GUIPanel(x, y, w, h)
        {
        }

      protected:
        void update_derived() override;

        void start_move();

        void stop_move();

        virtual RectF get_drag_area();

        auto being_moved() const
        {
            return being_moved_;
        }

        auto move_start_pos() const
        {
            return move_start_pos_;
        }

        auto move_start_mouse_pos() const
        {
            return move_start_mouse_pos_;
        }

      private:
        bool being_moved_{false};
        PointF move_start_pos_{-1, -1};
        PointF move_start_mouse_pos_{-1, -1};
    };

    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(float x, float y, float w, float h, StringView win_title)
            : GUIMovablePanel(x, y, w, h)
        {
            init(win_title);
        }

      protected:
        void render_derived() const override;

        RectF get_drag_area() override;

        auto get_win_title_bar() const
        {
            return gui_win_title_bar_;
        }

      private:
        void init(StringView win_title);

        class gui_win_title_bar : public GUIPanel
        {
          public:
            gui_win_title_bar(GUIWindow &parent_win, StringView win_title)
                : parent_win_(parent_win), k_win_title(win_title),
                  GUIPanel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
            {
                init();
            }

            void render_derived() const override;

            RectF bounds() const override;

          private:
            void init();

            inline static const float k_h{0.04f};
            const String k_win_title;

            GUIWindow &parent_win_;
        };

        SharedPtr<gui_win_title_bar> gui_win_title_bar_;
    };

    class GUIFPSPanel : public GUIMovablePanel
    {
      public:
        GUIFPSPanel() : GUIMovablePanel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            init();
        }

      protected:
        void update_derived() override;

      private:
        void init();

        SharedPtr<GUILabel> fps_text_pnl_;
    };

    class GUIChatBox : public GUIPanel
    {
      public:
        GUIChatBox()
            : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived)
        {
        }

        void render_derived() const override;

        void print(StringView text);

      private:
        constexpr static StringView k_default_bg_img_derived{"gui_chat_box_bg"};
        inline static const float k_line_h{0.025f};
        inline static const float k_sep_h{0.003f};
        inline static const float k_marg{0.008f};

        Vector<String> lines_;
    };
}
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
_HIDE_FROM_OUTLINER_CORE_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/render.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_TOP_                                           \
    namespace Core                                                             \
    {
_HIDE_FROM_OUTLINER_GUI_TOP_
class RenderersCollection
{
  protected:
    class shader_program
    {
      public:
        shader_program(StringView vert_src, StringView frag_src)
        {
            init(vert_src, frag_src);
        }

        ~shader_program()
        {
            cleanup();
        }

        auto program() const
        {
            return program_;
        }

      private:
        void init(StringView vert_src, StringView frag_src);

        void cleanup();

        GLuint program_;
    };

    class img_2d_rend
    {
      public:
        img_2d_rend()
        {
            init();
        };

        ~img_2d_rend()
        {
            cleanup();
        }

        void reset_counter();

        void draw_img(StringView img_name, float x, float y, float w, float h);

        void draw_img(int img_name_hash, float x, float y, float w, float h);

        void draw_tex(GLuint tex_id, float x, float y, float w, float h);

        void draw_img_auto_h(StringView img_name, float x, float y, float w);

      private:
        void init();

        void cleanup();

        class entry
        {
          public:
            GLuint vao;
            GLuint ibo;
            GLuint vbo;
            float x;
            float y;
            float w;
            float h;
        };

        SharedPtr<shader_program> shader_program_;
        std::map<int, std::map<int, entry>> imgs_;
        int counter_{0};
    };

    class entry
    {
      public:
        GLuint vao;
        GLuint ibo;
        GLuint vbo;
        float x;
        float y;
        float z;
    };

    class ground_rend
    {
      public:
        ground_rend()
        {
            init();
        };

        ~ground_rend()
        {
            cleanup();
        }

        void draw_tile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                       Point3F camera_pos, Vector<float> &elevs, float elev_h);

        void draw_tex(GLuint tex_id, Vector<float> &verts, Point3F camera_pos);

      private:
        void init();

        void cleanup();

        glm::vec3 compute_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        SharedPtr<shader_program> shader_program_;
        std::map<float, std::map<float, entry>> imgs_;
    };

    class model_rend
    {
      public:
        model_rend()
        {
            init();
        }

        void draw_model(int model_name_hash, float x, float y, float elev,
                        Point3F camera_pos, float elev_h);

      private:
        void init();

        SharedPtr<shader_program> shader_program_;
        std::map<float, std::map<float, std::map<float, std::map<int, entry>>>>
            models_;
        static constexpr float k_mdl_scale{0.08f};
    };

    enum struct font_szs
    {
        _20 = 20,
        _26 = 26
    };

    class text_rend
    {
      public:
        text_rend()
        {
            init();
        }

        void draw_str(StringView text, float x, float y,
                      font_szs font_sz = font_szs::_20, bool cent_align = false,
                      Color text_color = colors::wheat_transp) const;

      private:
        void init();

        void add_fonts();

        const String k_default_font_path{"./res/fonts/PixeloidSans.ttf"};

        std::map<font_szs, SharedPtr<TTF_Font>> fonts_;
    };
};
}
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/theme_0_core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
namespace Theme0
{
    namespace TileGridMath
    {
        SizeF calc_tl_sz();

        float calc_tl_sz_new();

        Size calc_grid_sz();
    }
    using namespace TileGridMath;

    namespace GameplayCore
    {
        namespace Player
        {
            enum class body_part_types
            {
                none,
                overall_body,
                right_arm,
                left_arm,
                legs
            };

            class body_part
            {
              public:
                auto str() const
                {
                    return str_;
                }
                auto curr_energy() const
                {
                    return curr_energy_;
                }
                auto max_energy() const
                {
                    return max_energy_;
                }
                auto temp() const
                {
                    return temp_;
                }

              private:
                float str_{0.1f};
                float curr_energy_{1.0f};
                float max_energy_{1.0f};
                float temp_{37.0f};
            };

            class player_body
            {
              public:
                player_body()
                {
                    init();
                }

                body_part *body_part_ptr(body_part_types type);

              private:
                void init();

                std::map<body_part_types, body_part> parts_;
            };

            class player
            {
              public:
                player()
                {
                    init();
                }

                void move_n();

                void move_e();

                void move_s();

                void move_w();

                auto name() const
                {
                    return name_;
                }

                auto pos() const
                {
                    return pos_;
                }

                auto movem_spd() const
                {
                    return movem_spd_;
                }

                auto ticks_last_move() const
                {
                    return ticks_last_move_;
                }

                void set_ticks_last_move(int val)
                {
                    ticks_last_move_ = val;
                }

                auto dest() const
                {
                    return dest_;
                }

                void set_dest(Point val)
                {
                    dest_ = val;
                }

                auto &body_ref()
                {
                    return body_;
                }

                auto money() const
                {
                    return money_;
                }

              private:
                void init();

                void move_to_suitable_pos();

                String name_{"Unnamed Player"};
                Point pos_{60, 50};
                float movem_spd_{5.0f};
                int ticks_last_move_{0};
                Point dest_{-1, -1};
                player_body body_;
                int money_{0};
            };
        }
        using namespace Player;
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_                             \
    }                                                                          \
    using namespace GameplayCore;
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_ }
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_
        using namespace Theme0;
        _NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 




// virtualInclude 'code/theme_0/src/update.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_1_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_1_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_2_                                      \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_2_
void update_kb_actions();

void update_mouse_actions();

void update_kb_movem();

void update_mouse_movem();

void update_crea_movem();

void update_npcs();

class tl_hovering
{
  public:
    void update();

    auto hovered_coord() const
    {
        return hovered_coord_;
    }

  private:
    Point hovered_coord_{-1, -1};
};
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 





// virtualInclude 'code/theme_0/src/world_view.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_                                  \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_
class world_view
{
  public:
    void render() const;
};
}
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 




// virtualInclude 'code/theme_0_world_struct/src/world_struct.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_
namespace WorldStructure
{
    enum class dirs
    {
        none,
        n,
        e,
        s,
        w,
        ne,
        se,
        sw,
        nw
    };

    class creature
    {
      public:
        creature(StringView type_name) : type_{hash(type_name)}
        {
            init();
        }

        auto type() const
        {
            return type_;
        }

        auto ticks_last_move() const
        {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value)
        {
            ticks_last_move_ = value;
        }

        auto movem_spd() const
        {
            return movem_spd_;
        }

        auto dest() const
        {
            return dest_;
        }

        void set_dest(Point val)
        {
            dest_ = val;
        }

      private:
        void init();

        int type_{0};
        int ticks_last_move_{0};
        float movem_spd_{2.0f};
        Point dest_{-1, -1};
    };

    class npc
    {
      public:
        npc(StringView type_name) : type_{hash(type_name)}
        {
            init();
        }

        auto type() const
        {
            return type_;
        }

        auto name() const
        {
            return name_;
        }

        auto ticks_last_move() const
        {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value)
        {
            ticks_last_move_ = value;
        }

        auto movem_spd() const
        {
            return movem_spd_;
        }

        auto dest() const
        {
            return dest_;
        }

        void set_dest(Point val)
        {
            dest_ = val;
        }

        auto ticks_next_spontaneous_speech() const
        {
            return ticks_next_spontaneous_speech_;
        }

        void set_ticks_next_spontaneous_speech(int value)
        {
            ticks_next_spontaneous_speech_ = value;
        }

      private:
        void init();

        void gen_name();

        int type_{0};
        String name_;
        int ticks_last_move_{0};
        float movem_spd_{2.0f};
        Point dest_{-1, -1};
        int ticks_next_spontaneous_speech_{0};
    };

    class object
    {
      public:
        object(StringView object_type_name) : type_(hash(object_type_name))
        {
        }

        auto type() const
        {
            return type_;
        }

      private:
        int type_{0};
    };

    class tree_object : public object
    {
      public:
        tree_object(StringView obj_type_name) : object(obj_type_name)
        {
            init(obj_type_name);
        }

        auto trunk_parts() const
        {
            return trunk_parts_;
        }

        auto needle_types() const
        {
            return needle_types_;
        }

        auto w_factor() const
        {
            return w_factor_;
        }

      private:
        void init(StringView obj_type_name);

        Vector<PointF> trunk_parts_;
        Vector<int> needle_types_;
        float w_factor_{1.0f};
    };

    class objects_stack
    {
      public:
        void clear_objs();

        void add_obj(StringView obj_type_name);

        void add_tree_obj(StringView obj_type_name);

        int get_sz() const;

        auto objects() const
        {
            return objects_;
        }

      private:
        Vector<SharedPtr<object>> objects_;
    };

    class tile
    {
      public:
        tile()
        {
            init();
        }

        auto ground() const
        {
            return ground_;
        }

        void set_ground(StringView ground_name);

        auto objects_stack() const
        {
            return objects_stack_;
        }

        auto creature() const
        {
            return creature_;
        }

        void set_creature(SharedPtr<Forradia::Theme0::WorldStructure::creature> val)
        {
            creature_ = val;
        }

        auto npc() const
        {
            return npc_;
        }

        void set_npc(SharedPtr<Forradia::Theme0::WorldStructure::npc> val)
        {
            npc_ = val;
        }

        auto elev() const
        {
            return elev_;
        }

        void set_elev(int val)
        {
            elev_ = val;
        }

        auto water_depth() const
        {
            return water_depth_;
        }

        void set_water_depth(int val)
        {
            water_depth_ = val;
        }

        auto river_dir_1() const
        {
            return river_dir_1_;
        }

        void set_river_dir_1(dirs val)
        {
            river_dir_1_ = val;
        }

        auto river_dir_2() const
        {
            return river_dir_2_;
        }

        void set_river_dir_2(dirs val)
        {
            river_dir_2_ = val;
        }

      private:
        void init();

        int ground_{0};
        SharedPtr<Forradia::Theme0::WorldStructure::objects_stack> objects_stack_;
        SharedPtr<Forradia::Theme0::WorldStructure::creature> creature_;
        SharedPtr<Forradia::Theme0::WorldStructure::npc> npc_;
        int elev_{0};
        int water_depth_{0};
        dirs river_dir_1_{dirs::none};
        dirs river_dir_2_{dirs::none};
    };

    class world_area
    {
      public:
        world_area(Size w_area_sz, float world_scaling)
        {
            init(w_area_sz, world_scaling);
        }

        Size get_sz() const;

        bool is_valid_coord(int x, int y) const;

        bool is_valid_coord(Point coord) const;

        SharedPtr<tile> get_tl(int x, int y) const;

        SharedPtr<tile> get_tl(Point coord) const;

        auto &creatures_mirror_ref()
        {
            return creatures_mirror_;
        }

        auto &npcs_mirror_ref()
        {
            return npcs_mirror_;
        }

      private:
        void init(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<tile>>> tiles_;
        std::map<SharedPtr<creature>, Point> creatures_mirror_;
        std::map<SharedPtr<npc>, Point> npcs_mirror_;
    };

    class world
    {
      public:
        void init(Size w_area_sz, float world_scaling);

        auto curr_w_area() const
        {
            return curr_w_area_;
        }

      private:
        SharedPtr<world_area> curr_w_area_;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/game_props.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GAME_PROPS_TOP_                                    \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GAME_PROPS_TOP_
namespace Configuration
{
    class game_props
    {
      public:
        static constexpr String k_game_win_title{"Forradia"};
        static constexpr Color k_clear_color{colors::black};
        static constexpr int k_num_grid_rows{15};
        static constexpr Size k_w_area_sz{120, 100};
        static constexpr float k_world_scaling{5.0f};
    };
}
using namespace Configuration;
#define _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_ }
_HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/theme_0/src/gui_spec.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_SPEC_TOP_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GUI_SPEC_TOP_
namespace SpecializedGUI
{
    class gui_player_status_box : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        gui_player_status_box() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
        }

      protected:
        virtual void render_derived() const override;
    };

    class gui_sys_menu : public Core::GUIComponentsLibrary::GUIComponent
    {
      public:
        gui_sys_menu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
        {
            init();
        }

      protected:
        void init();

        virtual void update_derived() override;

        virtual void render_derived() const override;
    };

    class gui_inventory_win : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        gui_inventory_win() : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f, "Inventory")
        {
        }

      protected:
        void render_derived() const override;

      private:
        static constexpr float k_margin{0.005f};
        static constexpr float k_slot_size{0.04f};
        inline static const String k_slot_img_name{"gui_inventory_win_slot_bg"};
    };

    class gui_player_body_win : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        gui_player_body_win() : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
        {
            init();
        }

      protected:
        void init();

      private:
        void sel_body_part(int type);

        void update_body_part_info_lbls();

        int sel_body_part_{0};
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_name_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_str_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_energy_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_temp_;
    };

    class gui_interact_menu : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        gui_interact_menu() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
            init();
        }

        void build_menu();

      protected:
        void init();

        virtual void update_derived() override;

        virtual void render_derived() const override;

      private:
        static constexpr float k_indent_w{0.01f};
        static constexpr float k_line_h{0.025f};

        class gui_interact_menu_entry
        {
          public:
            gui_interact_menu_entry(StringView label, Function<void()> action)
                : label_(label), action_(action)
            {
            }

            auto label() const
            {
                return label_;
            }

            auto action() const
            {
                return action_;
            }

          private:
            String label_;
            Function<void()> action_;
        };

        Vector<gui_interact_menu_entry> entries_;
    };
}
using namespace SpecializedGUI;
#define _HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_ }
_HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 



// virtualInclude 'code/theme_0/src/world_grator.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_                     \
    namespace Theme0                                                           \
    {                                                                          \
        namespace WorldStructure                                               \
        {                                                                      \
            class world_area;                                                  \
        }                                                                      \
    }
_HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_
namespace WorldGeneration
{
    class world_grator
    {
      public:
        void gen_new_world();

      private:
        void prep();
        void clear_with_dirt() const;
        void gen_grass() const;
        void gen_lakes() const;
        void gen_single_lake(int min_x, int min_y, int max_x, int max_y,
                             int recurs) const;
        void gen_elev() const;
        void gen_rock() const;
        void gen_rivers() const;
        void gen_objs() const;
        void gen_creas() const;
        void gen_npcs() const;

        SharedPtr<Theme0::WorldStructure::world_area> w_area_;
        float scale_;
        Size sz_;
    };
}
using namespace WorldGeneration;
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/scripts.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_SCRIPTS_TOP_                                       \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_SCRIPTS_TOP_
namespace Scripting
{
    class script_engine
    {
      public:
        void init();

        void load_scripts();
    };
}
using namespace Scripting;
}
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 









#define _HIDE_FROM_OUTLINER_ namespace Forradia {
_HIDE_FROM_OUTLINER_
}