/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui.hpp"
#include "core.hpp"
#include "input.hpp"
#include "rend.hpp"

namespace forr {
  s_ptr<gui_component>
  gui_component::add_child_component(s_ptr<gui_component> comp) {
    comp->set_parent_comp(this);
    m_children.push_back(comp);
    return comp;
  }

  void gui_component::update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto comp : std::views::reverse(m_children)) {
      comp->update();
    }
    update_derived();
  }

  void gui_component::render() const {
    if (!m_visible) {
      return;
    }
    render_derived();
    for (auto comp : m_children) {
      comp->render();
    }
  }

  rect_f gui_component::get_bounds() const {
    auto b_res{m_bounds};
    if (m_parent_comp) {
      auto parent_pos{m_parent_comp->get_bounds().get_pos()};
      b_res.offs(parent_pos);
    }
    return b_res;
  }

  void gui_component::toggle_visibility() { m_visible = !m_visible; }

  void gui_component::set_pos(point_f new_pos) {
    m_bounds.x = new_pos.x;
    m_bounds.y = new_pos.y;
  }

  void gui_label::render_derived() const {
    auto b{get_bounds()};
    auto x{b.x};
    auto y{b.y};
    if (m_cent_align) {
      b.x += b.w / 2;
      b.y += b.h / 2;
    }
    _<text_renderer>().draw_str(m_text, b.x, b.y, font_sizes::_20, m_cent_align,
                                m_color);
  }

  void gui_panel::render_derived() const {
    auto b{get_bounds()};
    _<image_renderer>().draw_img(m_bg_img, b.x, b.y, b.w, b.h);
  }

  void gui_button::update_derived() {
    gui_panel::update_derived();
    auto mouse_pos{get_norm_mouse_pos(_<sdl_device>().get_win())};
    auto hovered{get_bounds().contains(mouse_pos)};
    if (hovered) {
      set_bg_img(m_hovered_bg_img);
      _<cursor>().set_curs_style(cursor_styles::hovering_clickable_gui);
      if (_<mouse_input>().get_left_btn_ref().get_been_fired_pick_result()) {
        m_action();
      }
    } else {
      set_bg_img(m_bg_img);
    }
  }

  void gui_button::render_derived() const {
    gui_panel::render_derived();
    auto b{get_bounds()};
    _<text_renderer>().draw_str(m_text, b.x + b.w / 2, b.y + b.h / 2,
                                font_sizes::_20, true);
  }

  void gui_movable_panel::update_derived() {
    auto mouse_pos{get_norm_mouse_pos(_<sdl_device>().get_win())};
    auto drag_area{get_drag_area()};
    if (drag_area.contains(mouse_pos)) {
      _<cursor>().set_curs_style(cursor_styles::hovering_clickable_gui);
      if (_<mouse_input>().get_left_btn_ref().get_been_fired_pick_result()) {
        start_move();
      }
    }
    if (_<mouse_input>()
            .get_left_btn_ref()
            .get_been_released_dont_pick_result()) {
      stop_move();
    }
    auto b{get_bounds()};
    if (b.contains(mouse_pos)) {
      if (_<mouse_input>()
              .get_left_btn_ref()
              .get_been_fired_dont_pick_result()) {
        _<mouse_input>().get_left_btn_ref().reset();
      }
    }
    if (get_being_moved()) {
      auto move_start_pos{get_move_start_pos()};
      auto move_start_mouse_pos{get_move_start_mouse_pos()};
      auto curr_mouse_pos{get_norm_mouse_pos(_<sdl_device>().get_win())};
      auto new_pos{move_start_pos + curr_mouse_pos - move_start_mouse_pos};
      set_pos(new_pos);
    }
  }

  void gui_movable_panel::start_move() {
    m_being_moved = true;
    m_move_start_pos = get_bounds().get_pos();
    m_move_start_mouse_pos = get_norm_mouse_pos(_<sdl_device>().get_win());
  }

  void gui_movable_panel::stop_move() { m_being_moved = false; }

  rect_f gui_movable_panel::get_drag_area() { return get_bounds(); }

  void gui_window::gui_window_title_bar::render() const {
    auto parent_win_b{m_parent_win.get_bounds()};
    _<image_renderer>().draw_img("GUIWindowTitleBarBackground", parent_win_b.x,
                                 parent_win_b.y, parent_win_b.w, k_h);
    _<text_renderer>().draw_str(k_win_title, parent_win_b.x + 0.01f,
                                parent_win_b.y + 0.01f, font_sizes::_20, false,
                                colors::yellow);
  }

  rect_f gui_window::gui_window_title_bar::get_bounds() const {
    rect_f b_res;
    auto parent_win_b{m_parent_win.get_bounds()};
    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;
    return b_res;
  }
  void gui_window::init() { set_visible(false); }

  void gui_window::render_derived() const {
    gui_movable_panel::render_derived();
    m_gui_win_title_bar.render();
  }

  rect_f gui_window::get_drag_area() {
    return m_gui_win_title_bar.get_bounds();
  }

  void gui_fps_panel::init() {
    m_fps_text_pnl = std::make_shared<gui_label>(0.01f, 0.01f, 0.1f, 0.05f);
    add_child_component(m_fps_text_pnl);
  }

  void gui_fps_panel::update_derived() {
    gui_movable_panel::update_derived();
    auto fps{_<fps_counter>().get_fps()};
    m_fps_text_pnl->set_text(fmt::format("FPS: {}", fps));
  }

  void gui_text_console::render_derived() const {
    gui_panel::render_derived();
    auto b{get_bounds()};
    auto max_num_lines{c_int(b.h / k_line_h - 1)};
    auto y{b.y + k_marg};
    for (auto i = 0; i < max_num_lines; i++) {
      auto idx{m_lines.size() - max_num_lines + i};
      if (idx < 0 || idx >= m_lines.size()) {
        continue;
      }
      auto text_line = m_lines.at(idx);
      _<text_renderer>().draw_str(text_line, b.x + k_marg, y);
      y += k_line_h;
    }
    auto sep_rect{rect_f{b.x, b.y + b.h - k_line_h, b.w, k_sep_h}};
    _<image_renderer>().draw_img("Black", sep_rect.x, sep_rect.y, sep_rect.w,
                                 sep_rect.h);
  }

  void gui_text_console::print(str_view text) {
    m_lines.push_back(text.data());
  }
}