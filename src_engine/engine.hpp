/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  class engine {
   public:
    void run(str_view game_win_title, color clear_color);

    void stop();

   private:
    void poll_events();

    bool running_{true};
  };

  class sdl_device {
   public:
    void init(str_view game_win_title, color clear_color);

    void clear_canv() const;

    void present_canv() const;

    auto get_win() const { return win_; }

    auto get_rend() const { return rend_; }

   private:
    s_ptr<SDL_Window> create_win();

    s_ptr<SDL_Renderer> create_rend();

    s_ptr<SDL_Window> win_;
    s_ptr<SDL_Renderer> rend_;
    str game_win_title_;
    color clear_color_;
  };

  class fps_counter {
   public:
    void update();

    auto get_fps() const { return fps_; }

   private:
    int fps_{0};
    int frames_count_{0};
    int ticks_last_update_{0};
    const pt_f k_position{0.93f, 0.02f};
  };

  enum class cursor_styles {
    normal,
    hovering_clickable_gui,
    hovering_creature
  };

  class cursor {
   public:
    cursor() { init(); }

    void reset_style_to_default();

    void render();

    auto set_curs_style(cursor_styles val) { curs_style_ = val; }

   private:
    void init();

    void disable_sys_curs();

    constexpr static float k_curs_sz{0.05f};

    cursor_styles curs_style_{cursor_styles::normal};
  };

  class image_bank {
   public:
    image_bank() { init(); }

    s_ptr<SDL_Texture> get_img(int img_name_hash) const;

    sz get_img_sz(int img_name_hash) const;

   private:
    void init();

    void load_imgs();

    s_ptr<SDL_Texture> load_single_img(str_view path);

    inline static const str k_rel_imgs_path{"./Resources/Images/"};

    std::map<int, s_ptr<SDL_Texture>> images_;
  };

  class gui;

  class i_scene {
   public:
    void init();

    void update();

    void render() const;

    void on_enter();

   protected:
    virtual void init_derived() {}

    virtual void on_enter_derived() {}

    virtual void update_derived() {}

    virtual void render_derived() const {}

    auto get_gui() const { return gui_; }

   private:
    s_ptr<gui> gui_;
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