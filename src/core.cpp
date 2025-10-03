/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "rend.hpp"
#include "theme_0/func/conf/game_props.hpp"

namespace forr {
  void game::start() const { _<engine>().run(); }

  void engine::run() {
    randomize();
    _<sdl_device>();
    while (m_running) {
      _<kb_input>().reset();
      _<mouse_input>().reset();
      _<cursor>().reset_style_to_default();
      poll_events();
      _<scene_mngr>().update_curr_scene();
      _<fps_counter>().update();
      _<sdl_device>().clear_canv();
      _<scene_mngr>().render_curr_scene();
      _<cursor>().render();
      _<sdl_device>().present_canv();
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
        _<kb_input>().reg_key_press(ev.key.keysym.sym);
        break;
      case SDL_KEYUP:
        _<kb_input>().reg_key_release(ev.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        _<mouse_input>().reg_mouse_button_down(ev.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        _<mouse_input>().reg_mouse_button_up(ev.button.button);
        break;
      }
    }
  }

  void sdl_device::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_win = create_win();
    if (m_win) {
      m_rend = create_rend();
    }
  }

  void sdl_device::clear_canv() const {
    SDL_Color clear_color{_<game_props>().k_clear_color.to_sdl_color()};
    SDL_SetRenderDrawColor(m_rend.get(), clear_color.r, clear_color.g,
                           clear_color.b, 255);
    SDL_RenderClear(m_rend.get());
  }

  void sdl_device::present_canv() const { SDL_RenderPresent(m_rend.get()); }

  s_ptr<SDL_Window> sdl_device::create_win() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP};
    auto win_res{s_ptr<SDL_Window>(
        SDL_CreateWindow(_<game_props>().k_game_win_title.data(),
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 660,
                         660, flags),
        sdl_del())};
    if (!win_res) {
      print_ln("Window could not be created. SDL Error: " +
               str(SDL_GetError()));
    }
    return win_res;
  }

  s_ptr<SDL_Renderer> sdl_device::create_rend() {
    auto rend_res{s_ptr<SDL_Renderer>(
        SDL_CreateRenderer(m_win.get(), -1, SDL_RENDERER_ACCELERATED),
        sdl_del())};
    if (!rend_res) {
      print_ln("Renderer could not be created. SDL Error: " +
               std::string(SDL_GetError()));
    }
    return rend_res;
  }

  void fps_counter::update() {
    auto now{get_ticks()};
    if (now > m_ticks_last_update + k_one_sec_millis) {
      m_fps = m_frames_count;
      m_frames_count = 0;
      m_ticks_last_update = now;
    }
    ++m_frames_count;
  }

  void cursor::init() { disable_sys_curs(); }

  void cursor::disable_sys_curs() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::reset_style_to_default() {
    m_curs_style = cursor_styles::normal;
  }

  void cursor::render() {
    auto mouse_pos{get_norm_mouse_pos()};
    auto w{k_curs_sz};
    auto h{conv_w_to_h(k_curs_sz)};
    str curs_img;
    switch (m_curs_style) {
    case cursor_styles::normal:
      curs_img = "CursorDefault";
      break;
    case cursor_styles::hovering_clickable_gui:
      curs_img = "CursorHoveringClickableGUI";
      break;
    }
    _<image_renderer>().draw_img(curs_img, mouse_pos.x - w / 2,
                                 mouse_pos.y - h / 2, w, h);
  }

  void image_bank::init() { load_imgs(); }

  void image_bank::load_imgs() {
    auto base_path{str(SDL_GetBasePath())};
    auto imgs_path{base_path + k_rel_imgs_path.data()};
    if (!std::filesystem::exists(imgs_path)) {
      return;
    }
    std::filesystem::recursive_directory_iterator rdi{imgs_path};
    for (auto it : rdi) {
      auto file_path{repl(it.path().string(), '\\', '/')};
      if (get_file_ext(file_path) == "png") {
        auto file_name{get_file_name_no_ext(file_path)};
        auto hash{forr::hash(file_name)};
        auto img{load_single_img(file_path)};
        m_images.insert({hash, img});
      }
    }
  }

  s_ptr<SDL_Texture> image_bank::get_img(int img_name_hash) const {
    if (m_images.contains(img_name_hash)) {
      return m_images.at(img_name_hash);
    }
    return nullptr;
  }

  size image_bank::get_img_sz(int img_name_hash) const {
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

  s_ptr<SDL_Texture> image_bank::load_single_img(str_view path) {
    auto surf{s_ptr<SDL_Surface>(IMG_Load(path.data()), sdl_del())};
    if (surf) {
      auto rend{_<sdl_device>().get_rend().get()};
      auto tex{s_ptr<SDL_Texture>(
          SDL_CreateTextureFromSurface(rend, surf.get()), sdl_del())};
      return tex;
    }
    return nullptr;
  }

  void i_scene::init() {
    m_gui = std::make_shared<gui>();
    init_derived();
  }

  void i_scene::on_enter() { on_enter_derived(); }

  void i_scene::update() {
    m_gui->update();
    update_derived();
  }

  void i_scene::render() const {
    render_derived();
    m_gui->render();
  }

  void scene_mngr::add_scene(str_view scene_name, i_scene &scene) {
    scene.init();
    m_scenes.insert({hash(scene_name), scene});
  }

  void scene_mngr::go_to_scene(str_view scene_name) {
    m_curr_scene = hash(scene_name);
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).on_enter();
    }
  }

  void scene_mngr::update_curr_scene() {
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).update();
    }
  }

  void scene_mngr::render_curr_scene() const {
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).render();
    }
  }
}