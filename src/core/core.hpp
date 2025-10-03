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
    sdl_device() { initialize(); }

    void clear_canvas() const;

    void present_canvas() const;

    auto get_window() const { return m_win; }

    auto get_renderer() const { return m_rend; }

   private:
    void initialize();

    s_ptr<SDL_Window> create_window();

    s_ptr<SDL_Renderer> create_renderer();

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
    cursor() { initialize(); }

    void reset_style_to_default();

    void render();

    auto set_cursor_style(cursor_styles val) { m_curs_style = val; }

   private:
    void initialize();

    void disable_system_cursor();

    constexpr static float k_curs_sz{0.05f};

    cursor_styles m_curs_style{cursor_styles::normal};
  };

  class image_bank {
   public:
    image_bank() { initialize(); }

    s_ptr<SDL_Texture> get_image(int img_name_hash) const;

    size get_image_size(int img_name_hash) const;

   private:
    void initialize();

    void load_images();

    s_ptr<SDL_Texture> load_single_image(str_view path);

    inline static const str k_rel_imgs_path{"./Resources/Images/"};

    std::map<int, s_ptr<SDL_Texture>> m_images;
  };
}