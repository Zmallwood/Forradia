/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class engine {
   public:
    void init(str_view game_win_title, color clear_color) const;

    void run();

    void stop();

   private:
    void poll_events();

    bool running_{true};
  };

  class sdl_device {
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

  class fps_counter {
   public:
    void update();

    auto fps() const { return fps_; }

   private:
    int fps_{0};
    int frames_count_{0};
    int ticks_last_update_{0};
    const pt_f k_position{0.93f, 0.02f};
  };

  enum class curs_styles { normal, hovering_clickable_gui, hovering_creature };

  class cursor {
   public:
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

  class image_bank {
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
    std::map<float, std::map<float, std::map<int, GLuint>>> text_texes_;
  };

  class gui;

  class i_scene {
   public:
    void init();

    void update();

    void render() const;

    void on_enter();

    void set_init_derived(func<void()> value) { init_derived_ = value; }

    void set_on_enter_derived(func<void()> value) { on_enter_derived_ = value; }

    void set_update_derived(func<void()> value) { update_derived_ = value; }

    void set_render_derived(func<void()> value) { render_derived_ = value; }

   protected:
    auto gui() const { return gui_; }

   private:
    s_ptr<forr::gui> gui_;
    func<void()> init_derived_{[] {}};
    func<void()> on_enter_derived_{[] {}};
    func<void()> update_derived_{[] {}};
    func<void()> render_derived_{[] {}};
  };

  class scene_mngr {
   public:
    void add_scene(str_view scene_name, i_scene &scene);

    void go_to_scene(str_view scene_name);

    void update_curr_scene();

    void render_curr_scene() const;

   private:
    std::map<int, i_scene &> scenes_;
    int curr_scene_{0};
  };
}