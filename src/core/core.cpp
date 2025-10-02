/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  void game::start() const { get_singleton<engine>().run(); }

  void engine::run() {
    randomize();
    get_singleton<sdl_device>(); 
    while (m_running) {
      get_singleton<keyboard_input>().reset();
      get_singleton<mouse_input>().reset();
      get_singleton<cursor>().reset_style_to_default();
      poll_events();
      get_singleton<scene_manager>().update_current_scene();
      get_singleton<fps_counter>().update();
      get_singleton<sdl_device>().clear_canvas();
      get_singleton<scene_manager>().render_current_scene();
      get_singleton<cursor>().render();
      get_singleton<sdl_device>().present_canvas();
    }
  }

  void engine::stop() { m_running = false; }

  void engine::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        m_running = false;
        break;
      case SDL_KEYDOWN:
        get_singleton<keyboard_input>().register_key_press(
            event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        get_singleton<keyboard_input>().register_key_release(
            event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        get_singleton<mouse_input>().register_mouse_button_down(
            event.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        get_singleton<mouse_input>().register_mouse_button_up(
            event.button.button);
        break;
      }
    }
  }

  void sdl_device::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = create_window();
    if (m_window) {
      m_renderer = create_renderer();
    }
  }

  void sdl_device::clear_canvas() const {
    SDL_Color clear_color{
        get_singleton<game_properties>().k_clear_color.to_sdl_color()};
    SDL_SetRenderDrawColor(m_renderer.get(), clear_color.r, clear_color.g,
                           clear_color.b, 255);
    SDL_RenderClear(m_renderer.get());
  }

  void sdl_device::present_canvas() const {
    SDL_RenderPresent(m_renderer.get());
  }

  s_ptr<SDL_Window> sdl_device::create_window() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP};
    auto window_result{s_ptr<SDL_Window>(
        SDL_CreateWindow(
            get_singleton<game_properties>().k_game_window_title.data(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 660, 660, flags),
        sdl_deleter())};
    if (!window_result) {
      print_line("Window could not be created. SDL Error: " +
                 str(SDL_GetError()));
    }
    return window_result;
  }

  s_ptr<SDL_Renderer> sdl_device::create_renderer() {
    auto renderer_result{s_ptr<SDL_Renderer>(
        SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED),
        sdl_deleter())};
    if (!renderer_result) {
      print_line("Renderer could not be created. SDL Error: " +
                 std::string(SDL_GetError()));
    }
    return renderer_result;
  }

  void fps_counter::update() {
    auto now{get_ticks()};
    if (now > m_ticks_last_update + k_one_second_millis) {
      m_fps = m_frames_count;
      m_frames_count = 0;
      m_ticks_last_update = now;
    }
    ++m_frames_count;
  }

  void cursor::initialize() { disable_system_cursor(); }

  void cursor::disable_system_cursor() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::reset_style_to_default() {
    m_cursor_style = cursor_styles::normal;
  }

  void cursor::render() {
    auto mouse_position{get_normalized_mouse_position()};
    auto width{k_cursor_size};
    auto height{convert_width_to_height(k_cursor_size)};
    str cursor_image;
    switch (m_cursor_style) {
    case cursor_styles::normal:
      cursor_image = "CursorDefault";
      break;
    case cursor_styles::hovering_clickable_gui:
      cursor_image = "CursorHoveringClickableGUI";
      break;
    }
    get_singleton<image_renderer>().draw_image(
        cursor_image, mouse_position.x - width / 2,
        mouse_position.y - height / 2, width, height);
  }
}