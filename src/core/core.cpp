/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"
#include "core/input.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "core/scenes_core.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"

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
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        m_running = false;
        break;
      case SDL_KEYDOWN:
        get_singleton<keyboard_input>().register_key_press(ev.key.keysym.sym);
        break;
      case SDL_KEYUP:
        get_singleton<keyboard_input>().register_key_release(ev.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        get_singleton<mouse_input>().register_mouse_button_down(
            ev.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        get_singleton<mouse_input>().register_mouse_button_up(ev.button.button);
        break;
      }
    }
  }

  void sdl_device::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_win = create_window();
    if (m_win) {
      m_rend = create_renderer();
    }
  }

  void sdl_device::clear_canvas() const {
    SDL_Color clear_color{
        get_singleton<game_properties>().k_clear_color.to_sdl_color()};
    SDL_SetRenderDrawColor(m_rend.get(), clear_color.r, clear_color.g,
                           clear_color.b, 255);
    SDL_RenderClear(m_rend.get());
  }

  void sdl_device::present_canvas() const { SDL_RenderPresent(m_rend.get()); }

  s_ptr<SDL_Window> sdl_device::create_window() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP};
    auto win_res{s_ptr<SDL_Window>(
        SDL_CreateWindow(
            get_singleton<game_properties>().k_game_win_title.data(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 660, 660, flags),
        sdl_deleter())};
    if (!win_res) {
      print_line("Window could not be created. SDL Error: " +
                 str(SDL_GetError()));
    }
    return win_res;
  }

  s_ptr<SDL_Renderer> sdl_device::create_renderer() {
    auto rend_res{s_ptr<SDL_Renderer>(
        SDL_CreateRenderer(m_win.get(), -1, SDL_RENDERER_ACCELERATED),
        sdl_deleter())};
    if (!rend_res) {
      print_line("Renderer could not be created. SDL Error: " +
                 std::string(SDL_GetError()));
    }
    return rend_res;
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
    m_curs_style = cursor_styles::normal;
  }

  void cursor::render() {
    auto mouse_pos{get_normalized_mouse_position()};
    auto w{k_curs_sz};
    auto h{convert_width_to_height(k_curs_sz)};
    str curs_img;
    switch (m_curs_style) {
    case cursor_styles::normal:
      curs_img = "CursorDefault";
      break;
    case cursor_styles::hovering_clickable_gui:
      curs_img = "CursorHoveringClickableGUI";
      break;
    }
    get_singleton<image_renderer>().draw_image(curs_img, mouse_pos.x - w / 2,
                                               mouse_pos.y - h / 2, w, h);
  }

  void image_bank::initialize() { load_images(); }

  void image_bank::load_images() {
    auto base_path{str(SDL_GetBasePath())};
    auto imgs_path{base_path + k_rel_imgs_path.data()};
    if (!std::filesystem::exists(imgs_path)) {
      return;
    }
    std::filesystem::recursive_directory_iterator rdi{imgs_path};
    for (auto it : rdi) {
      auto file_path{replace(it.path().string(), '\\', '/')};
      if (get_file_extension(file_path) == "png") {
        auto file_name{get_file_name_no_extension(file_path)};
        auto hash{forr::hash(file_name)};
        auto img{load_single_image(file_path)};
        m_images.insert({hash, img});
      }
    }
  }

  s_ptr<SDL_Texture> image_bank::get_image(int img_name_hash) const {
    if (m_images.contains(img_name_hash)) {
      return m_images.at(img_name_hash);
    }
    return nullptr;
  }

  size image_bank::get_image_size(int img_name_hash) const {
    if (m_images.contains(img_name_hash)) {
      auto tex{m_images.at(img_name_hash)};
      size size;
      if (tex) {
        SDL_QueryTexture(tex.get(), nullptr, nullptr, &size.w, &size.h);
      }
      return size;
    }
    return {0, 0};
  }

  s_ptr<SDL_Texture> image_bank::load_single_image(str_view path) {
    auto surf{s_ptr<SDL_Surface>(IMG_Load(path.data()), sdl_deleter())};
    if (surf) {
      auto rend{get_singleton<sdl_device>().get_renderer().get()};
      auto tex{s_ptr<SDL_Texture>(
          SDL_CreateTextureFromSurface(rend, surf.get()), sdl_deleter())};
      return tex;
    }
    return nullptr;
  }
}