/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "rend.hpp"

namespace forr {
  void engine::init(str_view game_win_title, color clear_color) const {
    randomize();
    _<sdl_device>().init(game_win_title, clear_color);
  }

  void engine::run() {
    while (running_) {
      _<kb_inp>().reset();
      _<mouse_inp>().reset();
      _<cursor>().reset_style_to_normal();
      poll_events();
      _<scene_mngr>().update_curr_scene();
      _<fps_counter>().update();
      _<sdl_device>().clear_canv();
      _<scene_mngr>().render_curr_scene();
      _<cursor>().render();
      _<sdl_device>().present_canv();
    }
  }

  void engine::stop() { running_ = false; }

  void engine::poll_events() {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        running_ = false;
        break;
      case SDL_KEYDOWN:
        _<kb_inp>().reg_key_press(ev.key.keysym.sym);
        break;
      case SDL_KEYUP:
        _<kb_inp>().reg_key_release(ev.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        _<mouse_inp>().reg_mouse_btn_down(ev.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        _<mouse_inp>().reg_mouse_btn_up(ev.button.button);
        break;
      }
    }
  }

  void sdl_device::init(str_view game_win_title, color clear_color) {
    game_win_title_ = game_win_title;
    clear_color_ = clear_color;
    SDL_Init(SDL_INIT_EVERYTHING);
    win_ = create_win();
    if (win_)
      rend_ = create_rend();
  }

  void sdl_device::clear_canv() const {
    SDL_Color clear_color{clear_color_.to_sdl_color()};
    SDL_SetRenderDrawColor(rend_.get(), clear_color.r, clear_color.g,
                           clear_color.b, 255);
    SDL_RenderClear(rend_.get());
  }

  void sdl_device::present_canv() const { SDL_RenderPresent(rend_.get()); }

  s_ptr<SDL_Window> sdl_device::create_win() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP};
    auto win_res{s_ptr<SDL_Window>(
        SDL_CreateWindow(game_win_title_.data(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 660, 660, flags),
        sdl_del())};
    if (!win_res)
      print_ln("Window could not be created. SDL Error: " +
               str(SDL_GetError()));
    return win_res;
  }

  s_ptr<SDL_Renderer> sdl_device::create_rend() {
    auto rend_res{s_ptr<SDL_Renderer>(
        SDL_CreateRenderer(win_.get(), -1, SDL_RENDERER_ACCELERATED),
        sdl_del())};
    if (!rend_res) {
      print_ln("Renderer could not be created. SDL Error: " +
               std::string(SDL_GetError()));
    }
    return rend_res;
  }

  void fps_counter::update() {
    auto now{ticks()};
    if (now > ticks_last_update_ + k_one_sec_millis) {
      fps_ = frames_count_;
      frames_count_ = 0;
      ticks_last_update_ = now;
    }
    ++frames_count_;
  }

  void cursor::init() { disable_sys_curs(); }

  void cursor::disable_sys_curs() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::reset_style_to_normal() { curs_style_ = curs_styles::normal; }

  void cursor::render() {
    auto mouse_pos{norm_mouse_pos(_<sdl_device>().win())};
    auto w{k_curs_sz};
    auto h{conv_w_to_h(k_curs_sz, _<sdl_device>().win())};
    str curs_img;
    switch (curs_style_) {
    case curs_styles::normal:
      curs_img = "curs_normal";
      break;
    case curs_styles::hovering_clickable_gui:
      curs_img = "curs_hovering_clickable_gui";
      break;
    }
    _<img_rend>().draw_img(curs_img, mouse_pos.x - w / 2, mouse_pos.y - h / 2,
                             w, h);
  }

  void image_bank::init() { load_imgs(); }

  void image_bank::load_imgs() {
    auto base_path{str(SDL_GetBasePath())};
    auto imgs_path{base_path + k_rel_imgs_path.data()};
    if (!std::filesystem::exists(imgs_path))
      return;
    std::filesystem::recursive_directory_iterator rdi{imgs_path};
    for (auto it : rdi) {
      auto file_path{repl(it.path().string(), '\\', '/')};
      if (file_ext(file_path) == "png") {
        auto file_name{file_name_no_ext(file_path)};
        auto hash{forr::hash(file_name)};
        auto img{load_single_img(file_path)};
        images_.insert({hash, img});
      }
    }
  }

  s_ptr<SDL_Texture> image_bank::get_img(int img_name_hash) const {
    if (images_.contains(img_name_hash))
      return images_.at(img_name_hash);
    return nullptr;
  }

  sz image_bank::get_img_sz(int img_name_hash) const {
    if (images_.contains(img_name_hash)) {
      auto tex{images_.at(img_name_hash)};
      sz size;
      if (tex)
        SDL_QueryTexture(tex.get(), nullptr, nullptr, &size.w, &size.h);
      return size;
    }
    return {0, 0};
  }

  s_ptr<SDL_Texture> image_bank::load_single_img(str_view path) {
    auto surf{s_ptr<SDL_Surface>(IMG_Load(path.data()), sdl_del())};
    if (surf) {
      auto rend{_<sdl_device>().rend().get()};
      auto tex{s_ptr<SDL_Texture>(
          SDL_CreateTextureFromSurface(rend, surf.get()), sdl_del())};
      return tex;
    }
    return nullptr;
  }

  void i_scene::init() {
    gui_ = std::make_shared<forr::gui>();
    init_derived_();
  }

  void i_scene::on_enter() { on_enter_derived_(); }

  void i_scene::update() {
    gui_->update();
    update_derived_();
  }

  void i_scene::render() const {
    render_derived_();
    gui_->render();
  }

  void scene_mngr::add_scene(str_view scene_name, i_scene &scene) {
    scene.init();
    scenes_.insert({hash(scene_name), scene});
  }

  void scene_mngr::go_to_scene(str_view scene_name) {
    curr_scene_ = hash(scene_name);
    if (scenes_.contains(curr_scene_))
      scenes_.at(curr_scene_).on_enter();
  }

  void scene_mngr::update_curr_scene() {
    if (scenes_.contains(curr_scene_))
      scenes_.at(curr_scene_).update();
  }

  void scene_mngr::render_curr_scene() const {
    if (scenes_.contains(curr_scene_))
      scenes_.at(curr_scene_).render();
  }
}