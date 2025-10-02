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

    auto get_window() const { return m_window; }

    auto get_renderer() const { return m_renderer; }

   private:
    void initialize();

    s_ptr<SDL_Window> create_window();

    s_ptr<SDL_Renderer> create_renderer();

    s_ptr<SDL_Window> m_window;
    s_ptr<SDL_Renderer> m_renderer;
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

    auto set_cursor_style(cursor_styles value) { m_cursor_style = value; }

   private:
    void initialize();

    void disable_system_cursor();

    constexpr static float k_cursor_size{0.05f};

    cursor_styles m_cursor_style{cursor_styles::normal};
  };
}