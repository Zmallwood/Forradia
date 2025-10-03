/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_system_menu.hpp"
#include "engine.hpp"
#include "input.hpp"

namespace forr {
  void gui_system_menu::init() { set_visible(false); }

  void gui_system_menu::update_derived() {
    gui_component::update_derived();
    _<mouse_input>().get_left_btn_ref().reset();
  }

  void gui_system_menu::render_derived() const {
    gui_component::render_derived();
    auto canv_sz{get_canv_sz(_<sdl_device>().get_win())};
    auto rect{SDL_Rect{0, 0, canv_sz.w, canv_sz.h}};
    SDL_SetRenderDrawBlendMode(_<sdl_device>().get_rend().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(_<sdl_device>().get_rend().get(), 200, 0, 255, 50);
    SDL_RenderFillRect(_<sdl_device>().get_rend().get(), &rect);
  }
}