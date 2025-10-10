/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "models.hpp"
#include "rend.hpp"

namespace forr {
  void engine::init(str_view game_win_title, color clear_color) const {
    randomize();
    _<sdl_device>().init(game_win_title, clear_color);
  }

  void engine::run() {
    try {
      while (running_) {
        _<mouse_inp>().reset();
        _<cursor>().reset_style_to_normal();
        _<img_2d_rend>().reset_counter();
        poll_events();
        _<scene_mngr>().update_curr_scene();
        _<fps_counter>().update();
        _<sdl_device>().clear_canv();
        _<scene_mngr>().render_curr_scene();
        _<cursor>().render();
        _<sdl_device>().present_canv();
      }
    } catch (std::exception &e) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(),
                               nullptr);
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

  sdl_device::~sdl_device() { SDL_GL_DeleteContext(*context_); }

  void sdl_device::init(str_view game_win_title, color clear_color) {
    game_win_title_ = game_win_title;
    clear_color_ = clear_color;
    SDL_Init(SDL_INIT_EVERYTHING);
    win_ = create_win();
    context_ =
        std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(win_.get()));
    SDL_GL_MakeCurrent(win_.get(), *context_);
    GLenum status = glewInit();
    if (GLEW_OK != status)
      printf("GLEW Error: ", glewGetErrorString(status));
    SDL_GL_SetSwapInterval(0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
  }

  void sdl_device::clear_canv() const {
    SDL_Color clear_color{clear_color_.to_sdl_color()};
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void sdl_device::present_canv() const { SDL_GL_SwapWindow(win_.get()); }

  s_ptr<SDL_Window> sdl_device::create_win() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL};
    auto screen_sz{get_screen_sz()};
    auto win_res{s_ptr<SDL_Window>(
        SDL_CreateWindow(game_win_title_.data(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, screen_sz.w, screen_sz.h,
                         flags),
        sdl_del())};
    if (!win_res)
      print_ln("Window could not be created. SDL Error: " +
               str(SDL_GetError()));
    return win_res;
  }

  sz sdl_device::get_screen_sz() const {
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    auto w = dm.w;
    auto h = dm.h;
    return {w, h};
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
    _<img_2d_rend>().draw_img(curs_img, mouse_pos.x - w / 2,
                              mouse_pos.y - h / 2, w, h);
  }

  void image_bank::init() { load_imgs(); }

  void image_bank::cleanup() {
    for (auto entry : textures_)
      glDeleteTextures(1, &entry.second);
    for (auto entry1 : text_texes_)
      for (auto entry2 : entry1.second)
        for (auto tex : entry2.second)
          glDeleteTextures(1, &tex.second);
  }

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
        auto surf{s_ptr<SDL_Surface>(IMG_Load(file_path.data()), sdl_del())};
        auto img_sz{sz{surf->w, surf->h}};
        tex_sizes_.insert({hash, img_sz});
        // auto img{load_single_img(surf)};
        // images_.insert({hash, img});
        auto tex{load_single_tex(surf)};
        textures_.insert({hash, tex});
      }
    }
  }

  void model_bank::init() {
    auto base_path{str(SDL_GetBasePath())};
    auto imgs_path{base_path + k_rel_models_path.data()};
    if (!std::filesystem::exists(imgs_path))
      return;
    std::filesystem::recursive_directory_iterator rdi{imgs_path};
    for (auto it : rdi) {
      auto file_path{repl(it.path().string(), '\\', '/')};
      std::cout << file_path << std::endl;
      if (file_ext(file_path) == "dae") {
        auto file_name{file_name_no_ext(file_path)};
        auto hash{forr::hash(file_name)};
        auto model{load_single_model(file_path)};
        models_.insert({hash, model});
      }
    }
  }

  s_ptr<model> model_bank::get_model(int model_name_hash) const {
    if (models_.contains(model_name_hash))
      return models_.at(model_name_hash);
    return nullptr;
  }

  s_ptr<model> model_bank::load_single_model(str_view file_path) {
    auto model_res{std::make_shared<model>(file_path)};
    return model_res;
  }

  s_ptr<SDL_Texture> image_bank::get_img(int img_name_hash) const {
    if (images_.contains(img_name_hash))
      return images_.at(img_name_hash);
    return nullptr;
  }
  GLuint image_bank::get_tex(int img_name_hash) const {
    return textures_.at(img_name_hash);
  }

  sz image_bank::get_img_sz(int img_name_hash) const {
    if (tex_sizes_.contains(img_name_hash))
      return tex_sizes_.at(img_name_hash);
    return {-1, -1};
  }

  s_ptr<SDL_Texture> image_bank::load_single_img(s_ptr<SDL_Surface> surf) {
    //if (surf) {
      //auto rend{_<sdl_device>().rend().get()};
      //auto tex{s_ptr<SDL_Texture>(
          //SDL_CreateTextureFromSurface(rend, surf.get()), sdl_del())};
      //return tex;
    //}
    return nullptr;
  }

  GLuint image_bank::load_single_tex(s_ptr<SDL_Surface> surf) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
  }

  bool image_bank::text_tex_exists(float x, float y, int text_hash) const {
    return text_texes_.contains(x) && text_texes_.at(x).contains(y) &&
           text_texes_.at(x).at(y).contains(text_hash);
  }

  GLuint image_bank::obtain_text_tex(float x, float y, int text_hash) {
    if (text_tex_exists(x, y, text_hash))
      return text_texes_.at(x).at(y).at(text_hash);
    GLuint tex;
    glGenTextures(1, &tex);
    text_texes_[x][y][text_hash] = tex;
    return tex;
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