/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class game {
   public:
    void start() const;
  };

  class engine {
   public:
    void run();

    void stop();

   private:
    void poll_events();

    bool m_running{true};
  };

  class sdl_device {
   public:
    sdl_device() { init(); }

    void clear_canv() const;

    void present_canv() const;

    auto get_win() const { return m_win; }

    auto get_rend() const { return m_rend; }

   private:
    void init();

    s_ptr<SDL_Window> create_win();

    s_ptr<SDL_Renderer> create_rend();

    s_ptr<SDL_Window> m_win;
    s_ptr<SDL_Renderer> m_rend;
  };

  class fps_counter {
   public:
    void update();

    auto get_fps() const { return m_fps; }

   private:
    int m_fps{0};
    int m_frames_count{0};
    int m_ticks_last_update{0};
    const point_f k_position{0.93f, 0.02f};
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

    auto set_curs_style(cursor_styles val) { m_curs_style = val; }

   private:
    void init();

    void disable_sys_curs();

    constexpr static float k_curs_sz{0.05f};

    cursor_styles m_curs_style{cursor_styles::normal};
  };

  class image_bank {
   public:
    image_bank() { init(); }

    s_ptr<SDL_Texture> get_img(int img_name_hash) const;

    size get_img_sz(int img_name_hash) const;

   private:
    void init();

    void load_imgs();

    s_ptr<SDL_Texture> load_single_img(str_view path);

    inline static const str k_rel_imgs_path{"./Resources/Images/"};

    std::map<int, s_ptr<SDL_Texture>> m_images;
  };
}