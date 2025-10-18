/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui.hpp"
#include "core.hpp"
#include "input.hpp"
#include "rend.hpp"

_NS_START_
namespace GUICore {
  s_ptr<gui_comp> gui_comp::add_child_comp(s_ptr<gui_comp> comp) {
    comp->set_parent_comp(this);
    children_.push_back(comp);
    return comp;
  }

  void gui_comp::update() {
    if (!visible_ || !enabled_)
      return;
    for (auto comp : std::views::reverse(children_))
      comp->update();
    update_derived();
  }

  void gui_comp::render() const {
    if (!visible_)
      return;
    render_derived();
    for (auto comp : children_)
      comp->render();
  }

  rect_f gui_comp::bounds() const {
    auto b_res{bounds_};
    if (parent_comp_) {
      auto parent_pos{parent_comp_->bounds().pos()};
      b_res.offs(parent_pos);
    }
    return b_res;
  }

  void gui_comp::toggle_visible() { visible_ = !visible_; }

  void gui_comp::set_pos(pt_f new_pos) {
    bounds_.x = new_pos.x;
    bounds_.y = new_pos.y;
  }

  void gui_label::render_derived() const {
    auto b{bounds()};
    auto x{b.x};
    auto y{b.y};
    if (cent_align_) {
      b.x += b.w / 2;
      b.y += b.h / 2;
    }
    _<text_rend>().draw_str(text_, b.x, b.y, font_szs::_20, cent_align_,
                            color_);
  }

  void gui_panel::render_derived() const {
    auto b{bounds()};
    _<img_2d_rend>().draw_img(bg_img_, b.x, b.y, b.w, b.h);
  }

  void gui_button::update_derived() {
    gui_panel::update_derived();
    auto mouse_pos{norm_mouse_pos(_<engine::sdl_device>().win())};
    auto hovered{bounds().contains(mouse_pos)};
    if (hovered) {
      set_bg_img(hovered_bg_img_);
      _<engine::cursor>().set_curs_style(
          engine::cursor::curs_styles::hovering_clickable_gui);
      if (_<mouse_inp::left_mouse_btn>().been_fired_pick_res())
        action_();
    } else {
      set_bg_img(bg_img_);
    }
  }

  void gui_button::render_derived() const {
    gui_panel::render_derived();
    auto b{bounds()};
    _<text_rend>().draw_str(text_, b.x + b.w / 2, b.y + b.h / 2, font_szs::_20,
                            true);
  }

  void gui_movable_panel::update_derived() {
    auto mouse_pos{norm_mouse_pos(_<engine::sdl_device>().win())};
    auto drag_area{get_drag_area()};
    if (drag_area.contains(mouse_pos)) {
      _<engine::cursor>().set_curs_style(
          engine::cursor::curs_styles::hovering_clickable_gui);
      if (_<mouse_inp::left_mouse_btn>().been_fired_pick_res())
        start_move();
    }
    if (_<mouse_inp::left_mouse_btn>().been_released_no_pick_res())
      stop_move();
    auto b{bounds()};
    if (b.contains(mouse_pos)) {
      if (_<mouse_inp::left_mouse_btn>().been_fired_no_pick_res())
        _<mouse_inp::left_mouse_btn>().reset();
    }
    if (being_moved()) {
      auto curr_mouse_pos{norm_mouse_pos(_<engine::sdl_device>().win())};
      auto new_pos{move_start_pos() + curr_mouse_pos - move_start_mouse_pos()};
      set_pos(new_pos);
    }
  }

  void gui_movable_panel::start_move() {
    being_moved_ = true;
    move_start_pos_ = bounds().pos();
    move_start_mouse_pos_ = norm_mouse_pos(_<engine::sdl_device>().win());
  }

  void gui_movable_panel::stop_move() { being_moved_ = false; }

  rect_f gui_movable_panel::get_drag_area() { return bounds(); }

  void gui_win::gui_win_title_bar::init() {
    auto parent_win_b{parent_win_.bounds()};
    add_child_comp(std::make_shared<gui_button>(
        parent_win_b.w - conv_w_to_h(0.015f, _<engine::sdl_device>().win()),
        0.01f, 0.015f, conv_w_to_h(0.015f, _<engine::sdl_device>().win()), "X",
        [this] { parent_win_.toggle_visible(); }));
  }

  void gui_win::gui_win_title_bar::render_derived() const {
    gui_panel::render_derived();
    auto parent_win_b{parent_win_.bounds()};
    _<text_rend>().draw_str(k_win_title, parent_win_b.x + 0.01f,
                            parent_win_b.y + 0.01f, font_szs::_20, false,
                            colors::yellow);
  }

  rect_f gui_win::gui_win_title_bar::bounds() const {
    rect_f b_res;
    auto parent_win_b{parent_win_.bounds()};
    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;
    return b_res;
  }
  void gui_win::init(str_view win_title) {
    set_visible(false);
    gui_win_title_bar_ = std::make_shared<gui_win_title_bar>(*this, win_title);
    add_child_comp(gui_win_title_bar_);
  }

  void gui_win::render_derived() const { gui_movable_panel::render_derived(); }

  rect_f gui_win::get_drag_area() { return gui_win_title_bar_->bounds(); }

  void gui_fps_panel::init() {
    fps_text_pnl_ = std::make_shared<gui_label>(0.01f, 0.01f, 0.1f, 0.05f);
    add_child_comp(fps_text_pnl_);
  }

  void gui_fps_panel::update_derived() {
    gui_movable_panel::update_derived();
    auto fps{_<engine::fps_counter>().fps()};
    fps_text_pnl_->set_text(fmt::format("FPS: {}", fps));
  }

  void gui_chat_box::render_derived() const {
    gui_panel::render_derived();
    auto b{bounds()};
    auto max_num_lines{c_int(b.h / k_line_h - 1)};
    auto y{b.y + k_marg};
    for (auto i = 0; i < max_num_lines; i++) {
      auto idx{lines_.size() - max_num_lines + i};
      if (idx < 0 || idx >= lines_.size())
        continue;
      auto text_line = lines_.at(idx);
      _<text_rend>().draw_str(text_line, b.x + k_marg, y);
      y += k_line_h;
    }
    auto sep_rect{rect_f{b.x, b.y + b.h - k_line_h, b.w, k_sep_h}};
    _<img_2d_rend>().draw_img("black", sep_rect.x, sep_rect.y, sep_rect.w,
                              sep_rect.h);
  }

  void gui_chat_box::print(str_view text) { lines_.push_back(text.data()); }
}
_NS_END_