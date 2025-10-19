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

// virtualInclude 'src_comm/comm.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#define _NS_START_                                                             \
    namespace Forradia                                                         \
    {                                                                          \
        namespace gui_test                                                     \
        {                                                                      \
        }
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
        using str = std::string;
        using str_view = std::string_view;
        template <class T> using s_ptr = std::shared_ptr<T>;
        template <class T> using vec = std::vector<T>;
        template <class T> using func = std::function<T>;
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
        template <class T> s_ptr<T> __()
        {
            // Create singleton instance only once.
            static s_ptr<T> inst = std::make_shared<T>();
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
        class sdl_del
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
        class pt
        {
          public:
            /**
             * Equality operator between two Points.
             *
             * \param p Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const pt &p) const;

            int x{0};
            int y{0};
        };

        /**
         * Point in 2D space using dimensions of float type.
         */
        class pt_f
        {
          public:
            /**
             * Summing operator for the two points.
             *
             * \param p The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            pt_f operator+(const pt_f &p) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param p The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            pt_f operator-(const pt_f &p) const;

            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
        };

        /**
         * Point in 3D space using dimensions of float type.
         */
        class pt3_f
        {
          public:
            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
            float z{0.0f}; ///< The z dimension.
        };

        /**
         * Size in 2D space, with the dimensions as int values.
         */
        class sz
        {
          public:
            int w{0}; ///< Width.
            int h{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class sz_f
        {
          public:
            float w{0.0f}; ///< Width.
            float h{0.0f}; ///< Height.
        };

        /**
         * A rectangle in 2D space using dimensions of float type.
         */
        class rect_f
        {
          public:
            /**
             * Check if this rectangle contains a certian point.
             *
             * \param p Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool contains(pt_f p);

            /**
             * Returns only the position of this rectangle.
             *
             * \return The position.
             */
            pt_f pos() const;

            /**
             * Adds an offset to this rectangle, with the dimensions altered
             * separately.
             *
             * \param offs The offset to add.
             */
            void offs(pt_f offs);

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
            class color
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
                constexpr color black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr color wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr color wheat_transp{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr color yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr color yellow_transp{
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
            sz get_canv_sz(s_ptr<SDL_Window> win);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param win Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float calc_aspect_ratio(s_ptr<SDL_Window> win);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param w Width to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float conv_w_to_h(float w, s_ptr<SDL_Window> win);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param h Height to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float conv_h_to_w(float h, s_ptr<SDL_Window> win);
        }
        using namespace CanvasUtilities;
        namespace FilePathUtilities
        {
            // File path util functions
            str file_ext(str_view path);

            str file_name_no_ext(str_view path);
        }
        using namespace FilePathUtilities;
        namespace MouseUtilities
        {
            // Mouse util functions
            pt_f norm_mouse_pos(s_ptr<SDL_Window> win);
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
            str repl(str_view text, char repl, char repl_with);
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
            int hash(str_view text);
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
            void print(str_view text);

            /**
             * Print out a string of text, with an added line break at the end.
             *
             * \param text Text to print.
             */
            void print_ln(str_view text);
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
            constexpr int c_int(auto val) { return static_cast<int>(val); }

            /**
             * Cast a value to float.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            float c_float(auto val) { return static_cast<float>(val); }

            /**
             * Cast a value to Uint8.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            Uint8 c_uint8(auto val) { return static_cast<Uint8>(val); }
        }
        using namespace CastUtilities;
    }
    using namespace Utilities;
}
using namespace Common;
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_core/core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

#include "gui.hpp"

_NS_START_

// #define _HIDE_FROM_OUTLINER_ \
//     namespace GUICore \
//     { \
//         class gui; \
//     }
// _HIDE_FROM_OUTLINER_

namespace Core
{
    class engine
    {
      public:
        class sdl_device
        {
          public:
            ~sdl_device();

            void init(str_view game_win_title, color clear_color);

            void clear_canv() const;

            void present_canv() const;

            auto win() const { return win_; }

            auto rend() const { return rend_; }

          private:
            s_ptr<SDL_Window> create_win();

            sz get_screen_sz() const;

            s_ptr<SDL_Window> win_;
            s_ptr<SDL_GLContext> context_;
            s_ptr<SDL_Renderer> rend_;
            str game_win_title_;
            color clear_color_;
        };

        class fps_counter
        {
          public:
            void update();

            auto fps() const { return fps_; }

          private:
            int fps_{0};
            int frames_count_{0};
            int ticks_last_update_{0};
            const pt_f k_position{0.93f, 0.02f};
        };

        class cursor
        {
          public:
            enum class curs_styles
            {
                normal,
                hovering_clickable_gui,
                hovering_creature
            };

            cursor() { init(); }

            void reset_style_to_normal();

            void render();

            auto set_curs_style(curs_styles val) { curs_style_ = val; }

          private:
            void init();

            void disable_sys_curs();

            constexpr static float k_curs_sz{0.05f};

            curs_styles curs_style_{curs_styles::normal};
        };

        class Assets
        {
          public:
            class Images
            {
              public:
                class image_bank
                {
                  public:
                    image_bank() { init(); }

                    ~image_bank() { cleanup(); }

                    s_ptr<SDL_Texture> get_img(int img_name_hash) const;

                    GLuint get_tex(int img_name_hash) const;

                    sz get_img_sz(int img_name_hash) const;

                    bool text_tex_exists(float x, float y, int unique_id) const;

                    GLuint obtain_text_tex(float x, float y, int text_hash);

                  private:
                    void init();

                    void cleanup();

                    void load_imgs();

                    s_ptr<SDL_Texture> load_single_img(s_ptr<SDL_Surface> surf);

                    GLuint load_single_tex(s_ptr<SDL_Surface> surf);

                    inline static const str k_rel_imgs_path{"./res/images/"};

                    std::map<int, s_ptr<SDL_Texture>> images_;
                    std::map<int, GLuint> textures_;
                    std::map<int, sz> tex_sizes_;
                    std::map<float, std::map<float, std::map<int, GLuint>>>
                        text_texes_;
                };
            };
            class Models
            {
              public:
                class model_bank
                {
                  public:
                    class vertex
                    {
                      public:
                        glm::vec3 position;
                        glm::vec3 normal;
                        glm::vec2 tex_coord;
                        glm::vec3 tangent;
                        glm::vec3 bitangent;
                    };

                    class texture
                    {
                      public:
                        str path_;
                    };

                    class mesh
                    {
                      public:
                        vec<vertex> vertices;
                        vec<unsigned int> indices;
                        vec<texture> textures;
                        glm::vec3 extents;
                        glm::vec3 origin;
                        aiString name;
                    };

                    class model
                    {
                      public:
                        model(str_view file_path) { init(file_path); };

                        auto &meshes_ref() const { return meshes_; }

                      private:
                        void init(str_view file_path);

                        void process_node(aiNode *node, const aiScene *scene,
                                          aiMatrix4x4 transform);

                        mesh process_mesh(aiMesh *mesh, const aiScene *scene,
                                          aiMatrix4x4 transformation);

                        vec<vertex> get_vertices(aiMesh *mesh,
                                                 glm::vec3 &extents,
                                                 glm::vec3 &origin,
                                                 aiMatrix4x4 transformation);

                        vec<unsigned int> get_indices(aiMesh *mesh);

                        vec<texture> get_textures(aiMesh *mesh,
                                                  const aiScene *scene);

                        vec<mesh> meshes_;
                    };

                  public:
                    model_bank() { init(); }

                    s_ptr<model> get_model(int model_name_hash) const;

                  private:
                    void init();

                    s_ptr<model> load_single_model(str_view file_path);

                    inline static const str k_rel_models_path{"./res/models/"};

                    std::map<int, s_ptr<model>> models_;
                };
            };
        };
        class GUICore : public GUICoreBase
        {
          public:
            class gui : public GUICoreBase::gui
            {
              public:
                using GUICoreBase::gui::render;
                using GUICoreBase::gui::update;
            };
        };
        class ScenesCore
        {
          public:
            class i_scene
            {
              public:
                void init();

                void update();

                void render() const;

                void on_enter();

                void set_init_derived(func<void()> value)
                {
                    init_derived_ = value;
                }

                void set_on_enter_derived(func<void()> value)
                {
                    on_enter_derived_ = value;
                }

                void set_update_derived(func<void()> value)
                {
                    update_derived_ = value;
                }

                void set_render_derived(func<void()> value)
                {
                    render_derived_ = value;
                }

              protected:
                auto gui() const { return gui_; }

              private:
                s_ptr<GUICoreBase::gui> gui_;
                func<void()> init_derived_{[] {}};
                func<void()> on_enter_derived_{[] {}};
                func<void()> update_derived_{[] {}};
                func<void()> render_derived_{[] {}};
            };

            class scene_mngr
            {
              public:
                void add_scene(str_view scene_name, i_scene &scene);

                void go_to_scene(str_view scene_name);

                void update_curr_scene();

                void render_curr_scene() const;

              private:
                std::map<int, i_scene &> scenes_;
                int curr_scene_{0};
            };
        };
        class Input
        {
          public:
            ////////////////////
            // Keyboard
            ////////////////////
            class kb_inp
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
            class mouse_inp
            {
              public:
                class mouse_btn
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

                class left_mouse_btn : public mouse_btn
                {
                  public:
                    using mouse_btn::reset;

                    using mouse_btn::reg_press;

                    using mouse_btn::reg_release;

                    using mouse_btn::pressed_pick_res;

                    using mouse_btn::been_fired_pick_res;

                    using mouse_btn::been_fired_no_pick_res;

                    using mouse_btn::been_released_pick_res;

                    using mouse_btn::been_released_no_pick_res;
                };

                class right_mouse_btn : public mouse_btn
                {
                  public:
                    using mouse_btn::reset;

                    using mouse_btn::reg_press;

                    using mouse_btn::reg_release;

                    using mouse_btn::pressed_pick_res;

                    using mouse_btn::been_fired_pick_res;

                    using mouse_btn::been_fired_no_pick_res;

                    using mouse_btn::been_released_pick_res;

                    using mouse_btn::been_released_no_pick_res;
                };

                void reset();

                void reg_mouse_btn_down(Uint8 btn);

                void reg_mouse_btn_up(Uint8 btn);

                bool any_mouse_btn_pressed_pick_res();
            };
        };

        void init(str_view game_win_title, color clear_color) const;

        void run();

        void stop();

      private:
        void poll_events();

        bool running_{true};
    };
}
using namespace Core;
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_core/gui.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
class GUICoreBase
{
  public:
    class gui_comp
    {
      public:
        gui_comp(float x, float y, float w, float h) : bounds_({x, y, w, h}) {}

        s_ptr<gui_comp> add_child_comp(s_ptr<gui_comp> comp);

        void update();

        void render() const;

        virtual rect_f bounds() const;

        void set_pos(pt_f new_pos);

        void toggle_visible();

        auto visible() const { return visible_; }

        void set_visible(bool val) { visible_ = val; }

        void set_parent_comp(gui_comp *value) { parent_comp_ = value; }

      protected:
        virtual void update_derived() {}

        virtual void render_derived() const {}

      private:
        rect_f bounds_;
        vec<s_ptr<gui_comp>> children_;
        bool visible_{true};
        bool enabled_{true};
        gui_comp *parent_comp_{nullptr};
    };

    class gui : public gui_comp
    {
      public:
        gui() : gui_comp(0.0f, 0.0f, 1.0f, 1.0f) {}
    };

    class gui_label : public gui_comp
    {
      public:
        gui_label(float x, float y, float w, float h, str_view text = "",
                  bool cent_align = false, color color = colors::wheat_transp)
            : gui_comp(x, y, w, h), text_(text), cent_align_(cent_align),
              color_(color)
        {
        }

        void set_text(str_view val) { text_ = val; }

      protected:
        virtual void render_derived() const override;

      private:
        str text_;
        bool cent_align_{false};
        color color_;
    };

    class gui_panel : public gui_comp
    {
      public:
        gui_panel(float x, float y, float w, float h,
                  str_view bg_img = k_default_bg_img)
            : gui_comp(x, y, w, h), bg_img_(bg_img)
        {
        }

      protected:
        virtual void render_derived() const override;

        void set_bg_img(str_view val) { bg_img_ = val; }

      private:
        inline static const str k_default_bg_img{"gui_panel_bg"};

        str bg_img_;
    };

    class gui_button : public gui_panel
    {
      public:
        gui_button(float x, float y, float w, float h, str_view text,
                   func<void()> action, str_view bg_img = k_bg_img,
                   str_view hovered_bg_img = k_hovered_bg_img)
            : gui_panel(x, y, w, h), text_(text), action_(action),
              bg_img_(bg_img), hovered_bg_img_(hovered_bg_img)
        {
        }

      protected:
        virtual void update_derived() override;

        virtual void render_derived() const override;

      private:
        inline static const str k_bg_img{"gui_button_bg"};
        inline static const str k_hovered_bg_img{"gui_button_hovered_bg"};

        str text_;
        func<void()> action_;
        str bg_img_;
        str hovered_bg_img_;
    };

    class gui_movable_panel : public gui_panel
    {
      public:
        gui_movable_panel(float x, float y, float w, float h)
            : gui_panel(x, y, w, h)
        {
        }

      protected:
        void update_derived() override;

        void start_move();

        void stop_move();

        virtual rect_f get_drag_area();

        auto being_moved() const { return being_moved_; }

        auto move_start_pos() const { return move_start_pos_; }

        auto move_start_mouse_pos() const { return move_start_mouse_pos_; }

      private:
        bool being_moved_{false};
        pt_f move_start_pos_{-1, -1};
        pt_f move_start_mouse_pos_{-1, -1};
    };

    class gui_win : public gui_movable_panel
    {
      public:
        gui_win(float x, float y, float w, float h, str_view win_title)
            : gui_movable_panel(x, y, w, h)
        {
            init(win_title);
        }

      protected:
        void render_derived() const override;

        rect_f get_drag_area() override;

        auto get_win_title_bar() const { return gui_win_title_bar_; }

      private:
        void init(str_view win_title);

        class gui_win_title_bar : public gui_panel
        {
          public:
            gui_win_title_bar(gui_win &parent_win, str_view win_title)
                : parent_win_(parent_win), k_win_title(win_title),
                  gui_panel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
            {
                init();
            }

            void render_derived() const override;

            rect_f bounds() const override;

          private:
            void init();

            inline static const float k_h{0.04f};
            const str k_win_title;

            gui_win &parent_win_;
        };

        s_ptr<gui_win_title_bar> gui_win_title_bar_;
    };

    class gui_fps_panel : public gui_movable_panel
    {
      public:
        gui_fps_panel() : gui_movable_panel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            init();
        }

      protected:
        void update_derived() override;

      private:
        void init();

        s_ptr<gui_label> fps_text_pnl_;
    };

    class gui_chat_box : public gui_panel
    {
      public:
        gui_chat_box()
            : gui_panel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived)
        {
        }

        void render_derived() const override;

        void print(str_view text);

      private:
        constexpr static str_view k_default_bg_img_derived{"gui_chat_box_bg"};
        inline static const float k_line_h{0.025f};
        inline static const float k_sep_h{0.003f};
        inline static const float k_marg{0.008f};

        vec<str> lines_;
    };
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 




// virtualInclude 'src_core/rend.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
class shader_program
{
  public:
    shader_program(str_view vert_src, str_view frag_src)
    {
        init(vert_src, frag_src);
    }

    ~shader_program() { cleanup(); }

    auto program() const { return program_; }

  private:
    void init(str_view vert_src, str_view frag_src);

    void cleanup();

    GLuint program_;
};

class img_2d_rend
{
  public:
    img_2d_rend() { init(); };

    ~img_2d_rend() { cleanup(); }

    void reset_counter();

    void draw_img(str_view img_name, float x, float y, float w, float h);

    void draw_img(int img_name_hash, float x, float y, float w, float h);

    void draw_tex(GLuint tex_id, float x, float y, float w, float h);

    void draw_img_auto_h(str_view img_name, float x, float y, float w);

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

    s_ptr<shader_program> shader_program_;
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
    ground_rend() { init(); };

    ~ground_rend() { cleanup(); }

    void draw_tile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                   pt3_f camera_pos, vec<float> &elevs, float elev_h);

    void draw_tex(GLuint tex_id, vec<float> &verts, pt3_f camera_pos);

  private:
    void init();

    void cleanup();

    glm::vec3 compute_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

    s_ptr<shader_program> shader_program_;
    std::map<float, std::map<float, entry>> imgs_;
};

class model_rend
{
  public:
    model_rend() { init(); }

    void draw_model(int model_name_hash, float x, float y, float elev,
                    pt3_f camera_pos, float elev_h);

  private:
    void init();

    s_ptr<shader_program> shader_program_;
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
    text_rend() { init(); }

    void draw_str(str_view text, float x, float y,
                  font_szs font_sz = font_szs::_20, bool cent_align = false,
                  color text_color = colors::wheat_transp) const;

  private:
    void init();

    void add_fonts();

    const str k_default_font_path{"./res/fonts/PixeloidSans.ttf"};

    std::map<font_szs, s_ptr<TTF_Font>> fonts_;
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/theme_0_core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

_NS_START_
namespace Theme0
{
    sz_f calc_tl_sz();

    float calc_tl_sz_new();

    sz calc_grid_sz();

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
        auto str() const { return str_; }
        auto curr_energy() const { return curr_energy_; }
        auto max_energy() const { return max_energy_; }
        auto temp() const { return temp_; }

      private:
        float str_{0.1f};
        float curr_energy_{1.0f};
        float max_energy_{1.0f};
        float temp_{37.0f};
    };

    class player_body
    {
      public:
        player_body() { init(); }

        body_part *body_part_ptr(body_part_types type);

      private:
        void init();

        std::map<body_part_types, body_part> parts_;
    };

    class player
    {
      public:
        player() { init(); }

        void move_n();

        void move_e();

        void move_s();

        void move_w();

        auto name() const { return name_; }

        auto pos() const { return pos_; }

        auto movem_spd() const { return movem_spd_; }

        auto ticks_last_move() const { return ticks_last_move_; }

        void set_ticks_last_move(int val) { ticks_last_move_ = val; }

        auto dest() const { return dest_; }

        void set_dest(pt val) { dest_ = val; }

        auto &body_ref() { return body_; }

        auto money() const { return money_; }

      private:
        void init();

        void move_to_suitable_pos();

        str name_{"Unnamed Player"};
        pt pos_{60, 50};
        float movem_spd_{5.0f};
        int ticks_last_move_{0};
        pt dest_{-1, -1};
        player_body body_;
        int money_{0};
    };
}
using namespace Theme0;
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/game_props.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

_NS_START_
class game_props
{
  public:
    static constexpr str k_game_win_title{"Forradia"};
    static constexpr color k_clear_color{colors::black};
    static constexpr int k_num_grid_rows{15};
    static constexpr sz k_w_area_sz{120, 100};
    static constexpr float k_world_scaling{5.0f};
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/gui_spec.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

_NS_START_
class gui_player_status_box : public GUICoreBase::gui_panel
{
  public:
    gui_player_status_box() : gui_panel(0.0f, 0.0f, 0.2f, 0.14f) {}

  protected:
    virtual void render_derived() const override;
};

class gui_sys_menu : public GUICoreBase::gui_comp
{
  public:
    gui_sys_menu() : gui_comp(0.0f, 0.0f, 1.0f, 1.0f) { init(); }

  protected:
    void init();

    virtual void update_derived() override;

    virtual void render_derived() const override;
};

class gui_inventory_win : public GUICoreBase::gui_win
{
  public:
    gui_inventory_win() : gui_win(0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {}

  protected:
    void render_derived() const override;

  private:
    static constexpr float k_margin{0.005f};
    static constexpr float k_slot_size{0.04f};
    inline static const str k_slot_img_name{"gui_inventory_win_slot_bg"};
};

class gui_player_body_win : public GUICoreBase::gui_win
{
  public:
    gui_player_body_win() : gui_win(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
    {
        init();
    }

  protected:
    void init();

  private:
    void sel_body_part(int type);

    void update_body_part_info_lbls();

    int sel_body_part_{0};
    s_ptr<GUICoreBase::gui_label> lbl_body_part_name_;
    s_ptr<GUICoreBase::gui_label> lbl_body_part_str_;
    s_ptr<GUICoreBase::gui_label> lbl_body_part_energy_;
    s_ptr<GUICoreBase::gui_label> lbl_body_part_temp_;
};

class gui_interact_menu : public GUICoreBase::gui_panel
{
  public:
    gui_interact_menu() : gui_panel(0.0f, 0.0f, 0.2f, 0.14f) { init(); }

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
        gui_interact_menu_entry(str_view label, func<void()> action)
            : label_(label), action_(action)
        {
        }

        auto label() const { return label_; }

        auto action() const { return action_; }

      private:
        str label_;
        func<void()> action_;
    };

    vec<gui_interact_menu_entry> entries_;
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/scripts.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
class script_engine
{
  public:
    void init();

    void load_scripts();
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/update.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

_NS_START_
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

    auto hovered_coord() const { return hovered_coord_; }

  private:
    pt hovered_coord_{-1, -1};
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/world_grator.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

_NS_START_
class world_area;

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

    s_ptr<world_area> w_area_;
    float scale_;
    sz sz_;
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0/world_view.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
class world_view
{
  public:
    void render() const;

    void render_new() const;
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'src_theme_0_world_struct/world_struct.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
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
    creature(str_view type_name) : type_{hash(type_name)} { init(); }

    auto type() const { return type_; }

    auto ticks_last_move() const { return ticks_last_move_; }

    void set_ticks_last_move(int value) { ticks_last_move_ = value; }

    auto movem_spd() const { return movem_spd_; }

    auto dest() const { return dest_; }

    void set_dest(pt val) { dest_ = val; }

  private:
    void init();

    int type_{0};
    int ticks_last_move_{0};
    float movem_spd_{2.0f};
    pt dest_{-1, -1};
};

class npc
{
  public:
    npc(str_view type_name) : type_{hash(type_name)} { init(); }

    auto type() const { return type_; }

    auto name() const { return name_; }

    auto ticks_last_move() const { return ticks_last_move_; }

    void set_ticks_last_move(int value) { ticks_last_move_ = value; }

    auto movem_spd() const { return movem_spd_; }

    auto dest() const { return dest_; }

    void set_dest(pt val) { dest_ = val; }

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
    str name_;
    int ticks_last_move_{0};
    float movem_spd_{2.0f};
    pt dest_{-1, -1};
    int ticks_next_spontaneous_speech_{0};
};

class object
{
  public:
    object(str_view object_type_name) : type_(hash(object_type_name)) {}

    auto type() const { return type_; }

  private:
    int type_{0};
};

class tree_object : public object
{
  public:
    tree_object(str_view obj_type_name) : object(obj_type_name)
    {
        init(obj_type_name);
    }

    auto trunk_parts() const { return trunk_parts_; }

    auto needle_types() const { return needle_types_; }

    auto w_factor() const { return w_factor_; }

  private:
    void init(str_view obj_type_name);

    vec<pt_f> trunk_parts_;
    vec<int> needle_types_;
    float w_factor_{1.0f};
};

class objects_stack
{
  public:
    void clear_objs();

    void add_obj(str_view obj_type_name);

    void add_tree_obj(str_view obj_type_name);

    int get_sz() const;

    auto objects() const { return objects_; }

  private:
    vec<s_ptr<object>> objects_;
};

class tile
{
  public:
    tile() { init(); }

    auto ground() const { return ground_; }

    void set_ground(str_view ground_name);

    auto objects_stack() const { return objects_stack_; }

    auto creature() const { return creature_; }

    void set_creature(s_ptr<Forradia::creature> val) { creature_ = val; }

    auto npc() const { return npc_; }

    void set_npc(s_ptr<Forradia::npc> val) { npc_ = val; }

    auto elev() const { return elev_; }

    void set_elev(int val) { elev_ = val; }

    auto water_depth() const { return water_depth_; }

    void set_water_depth(int val) { water_depth_ = val; }

    auto river_dir_1() const { return river_dir_1_; }

    void set_river_dir_1(dirs val) { river_dir_1_ = val; }

    auto river_dir_2() const { return river_dir_2_; }

    void set_river_dir_2(dirs val) { river_dir_2_ = val; }

  private:
    void init();

    int ground_{0};
    s_ptr<Forradia::objects_stack> objects_stack_;
    s_ptr<Forradia::creature> creature_;
    s_ptr<Forradia::npc> npc_;
    int elev_{0};
    int water_depth_{0};
    dirs river_dir_1_{dirs::none};
    dirs river_dir_2_{dirs::none};
};

class world_area
{
  public:
    world_area(sz w_area_sz, float world_scaling)
    {
        init(w_area_sz, world_scaling);
    }

    sz get_sz() const;

    bool is_valid_coord(int x, int y) const;

    bool is_valid_coord(pt coord) const;

    s_ptr<tile> get_tl(int x, int y) const;

    s_ptr<tile> get_tl(pt coord) const;

    auto &creatures_mirror_ref() { return creatures_mirror_; }

    auto &npcs_mirror_ref() { return npcs_mirror_; }

  private:
    void init(sz w_area_sz, float world_scaling);

    vec<vec<s_ptr<tile>>> tiles_;
    std::map<s_ptr<creature>, pt> creatures_mirror_;
    std::map<s_ptr<npc>, pt> npcs_mirror_;
};

class world
{
  public:
    void init(sz w_area_sz, float world_scaling);

    auto curr_w_area() const { return curr_w_area_; }

  private:
    s_ptr<world_area> curr_w_area_;
};
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


