/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_spec.hpp"
#include "core.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "rend.hpp"
#include "update.hpp"
#include "world_struct.hpp"

_NS_START_
void gui_player_status_box::render_derived() const {
  gui_panel::render_derived();
  auto b{bounds()};
  _<text_rend>().draw_str(_<player>().name(), b.x + 0.01f, b.y + 0.01f,
                          font_szs::_26);
}

void gui_sys_menu::init() { set_visible(false); }

void gui_sys_menu::update_derived() {
  gui_comp::update_derived();
  _<mouse_inp>().left_btn_ref().reset();
}

void gui_sys_menu::render_derived() const {
  gui_comp::render_derived();
  auto c_sz{get_canv_sz(_<sdl_device>().win())};
  auto rect{SDL_Rect{0, 0, c_sz.w, c_sz.h}};
  SDL_SetRenderDrawBlendMode(_<sdl_device>().rend().get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(_<sdl_device>().rend().get(), 200, 0, 255, 50);
  SDL_RenderFillRect(_<sdl_device>().rend().get(), &rect);
}

void gui_inventory_win::render_derived() const {
  gui_win::render_derived();
  auto b{bounds()};
  auto margin_x{k_margin};
  auto margin_y{conv_w_to_h(k_margin, _<sdl_device>().win())};
  auto x_start{b.x + margin_x};
  auto y_start{b.y + margin_y + get_win_title_bar()->bounds().h};
  auto slot_w{k_slot_size};
  auto slot_h{conv_w_to_h(k_slot_size, _<sdl_device>().win())};
  auto num_cols{c_int((b.w - 2 * margin_x) / slot_w)};
  auto num_rows{c_int((b.h - 2 * margin_y - (y_start - b.y)) / slot_h)};
  for (auto y = 0; y < num_rows; y++) {
    for (auto x = 0; x < num_cols; x++) {
      _<img_rend>().draw_img(k_slot_img_name, x_start + x * (slot_w + margin_x),
                             y_start + y * (slot_h + margin_y), slot_w, slot_h);
    }
  }
}

void gui_player_body_win::init() {
  auto img_w{0.07f};
  auto img_h{conv_w_to_h(img_w, _<sdl_device>().win())};
  auto overall_body_img_btn{std::make_shared<gui_button>(
      0.1f - img_w / 2, 0.04f, img_w, img_h, "",
      [this] {
        sel_body_part(c_int(body_part_types::overall_body));
        update_body_part_info_lbls();
      },
      "gui_image_overall_body", "gui_image_overall_body_hovered")};
  add_child_comp(overall_body_img_btn);
  auto right_arm_body_img_btn{std::make_shared<gui_button>(
      0.1f - img_w / 2 - img_w, 0.04f, img_w, img_h, "",
      [this] {
        sel_body_part(c_int(body_part_types::right_arm));
        update_body_part_info_lbls();
      },
      "gui_image_right_arm", "gui_image_right_arm_hovered")};
  add_child_comp(right_arm_body_img_btn);
  auto left_arm_body_img_btn{std::make_shared<gui_button>(
      0.1f - img_w / 2 + img_w, 0.04f, img_w, img_h, "",
      [this] {
        sel_body_part(c_int(body_part_types::left_arm));
        update_body_part_info_lbls();
      },
      "gui_image_left_arm", "gui_image_left_arm_hovered")};
  add_child_comp(left_arm_body_img_btn);
  auto legs_img_btn{std::make_shared<gui_button>(
      0.1f - img_w / 2, 0.04f + img_h, img_w, img_h, "",
      [this] {
        sel_body_part(c_int(body_part_types::legs));
        update_body_part_info_lbls();
      },
      "gui_image_legs", "gui_image_legs_hovered")};
  add_child_comp(legs_img_btn);
  lbl_body_part_name_ = std::make_shared<gui_label>(
      0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false, colors::yellow_transp);
  lbl_body_part_str_ = std::make_shared<gui_label>(
      0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
  lbl_body_part_energy_ = std::make_shared<gui_label>(
      0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
  lbl_body_part_temp_ = std::make_shared<gui_label>(
      0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
  add_child_comp(lbl_body_part_name_);
  add_child_comp(lbl_body_part_str_);
  add_child_comp(lbl_body_part_energy_);
  add_child_comp(lbl_body_part_temp_);
}

void gui_player_body_win::sel_body_part(int type) { sel_body_part_ = type; }

void gui_player_body_win::update_body_part_info_lbls() {
  auto &p_body{_<player>().body_ref()};
  constexpr auto overall_body{c_int(body_part_types::overall_body)};
  constexpr auto right_arm{c_int(body_part_types::right_arm)};
  constexpr auto left_arm{c_int(body_part_types::left_arm)};
  constexpr auto legs{c_int(body_part_types::legs)};
  switch (sel_body_part_) {
  case overall_body: {
    lbl_body_part_name_->set_text("Body part: Overall body");
    auto str{p_body.body_part_ptr(body_part_types::overall_body)->str()};
    lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
    auto max_energy{
        p_body.body_part_ptr(body_part_types::overall_body)->max_energy()};
    auto curr_energy{
        p_body.body_part_ptr(body_part_types::overall_body)->curr_energy()};
    lbl_body_part_energy_->set_text(
        fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
    auto temp{p_body.body_part_ptr(body_part_types::overall_body)->temp()};
    lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
  } break;
  case right_arm: {
    lbl_body_part_name_->set_text("Body part: Right arm");
    auto str{p_body.body_part_ptr(body_part_types::right_arm)->str()};
    lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
    auto max_energy{
        p_body.body_part_ptr(body_part_types::right_arm)->max_energy()};
    auto curr_energy{
        p_body.body_part_ptr(body_part_types::right_arm)->curr_energy()};
    lbl_body_part_energy_->set_text(
        fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
    auto temp{p_body.body_part_ptr(body_part_types::right_arm)->temp()};
    lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
  } break;
  case left_arm: {
    lbl_body_part_name_->set_text("Body part: Left arm");
    auto str{p_body.body_part_ptr(body_part_types::left_arm)->str()};
    lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
    auto max_energy{
        p_body.body_part_ptr(body_part_types::left_arm)->max_energy()};
    auto curr_energy{
        p_body.body_part_ptr(body_part_types::left_arm)->curr_energy()};
    lbl_body_part_energy_->set_text(
        fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
    auto temp{p_body.body_part_ptr(body_part_types::left_arm)->temp()};
    lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
  } break;
  case legs: {
    lbl_body_part_name_->set_text("Body part: Legs");
    auto str{p_body.body_part_ptr(body_part_types::legs)->str()};
    lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
    auto max_energy{p_body.body_part_ptr(body_part_types::legs)->max_energy()};
    auto curr_energy{
        p_body.body_part_ptr(body_part_types::legs)->curr_energy()};
    lbl_body_part_energy_->set_text(
        fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
    auto temp{p_body.body_part_ptr(body_part_types::legs)->temp()};
    lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
  } break;
  }
}

void gui_interact_menu::init() { set_visible(false); }

void gui_interact_menu::build_menu() {
  entries_.clear();
  auto hov_tl{_<tl_hovering>().hovered_coord()};
  auto w_area{_<world>().curr_w_area()};
  auto tl{w_area->get_tl(hov_tl.x, hov_tl.y)};
  if (tl && tl->ground() == hash("ground_grass")) {
    entries_.push_back({"Forage", [=]() {
                          _<gui_chat_box>().print(
                              "Grass foraged. You found blue berries.");
                        }});
  }
  auto objects{tl->objects_stack()->objects()};
  for (auto &obj : objects) {
    auto type{obj->type()};
    if (type == hash("object_fir_tree") || type == hash("object_birch_tree")) {
      entries_.push_back({"Cut down tree", [=]() {
                            _<gui_chat_box>().print(
                                "Tree cut down. You found some wood.");
                          }});
    }
  }
}

void gui_interact_menu::update_derived() {
  gui_panel::update_derived();
  auto b{bounds()};
  auto mouse_pos{norm_mouse_pos(_<sdl_device>().win())};
  auto i{0};
  for (auto &entry : entries_) {
    auto menu_entry_rect{rect_f{b.x + 0.01f + k_indent_w,
                                b.y + 0.01f + k_line_h * (i + 1), b.w,
                                k_line_h}};
    if (_<mouse_inp>().left_btn_ref().been_fired_no_pick_res()) {
      if (menu_entry_rect.contains(mouse_pos))
        entry.action()();
      set_visible(false);
    }
    ++i;
  }
  if (_<mouse_inp>().left_btn_ref().been_fired_pick_res())
    set_visible(false);
}

void gui_interact_menu::render_derived() const {
  gui_panel::render_derived();
  auto b{bounds()};
  _<text_rend>().draw_str("Actions", b.x + 0.01f, b.y + 0.01f, font_szs::_20,
                          false, colors::yellow_transp);
  auto i{0};
  for (auto &entry : entries_) {
    _<text_rend>().draw_str(entry.label(), b.x + 0.01f + k_indent_w,
                            b.y + 0.01f + (i + 1) * k_line_h, font_szs::_20);
    ++i;
  }
}
_NS_END_