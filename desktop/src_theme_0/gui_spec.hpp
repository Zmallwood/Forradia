/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

_NS_START_
class gui_player_status_box : public gui_panel
{
  public:
    gui_player_status_box() : gui_panel(0.0f, 0.0f, 0.2f, 0.14f) {}

  protected:
    virtual void render_derived() const override;
};

class gui_sys_menu : public gui_comp
{
  public:
    gui_sys_menu() : gui_comp(0.0f, 0.0f, 1.0f, 1.0f) { init(); }

  protected:
    void init();

    virtual void update_derived() override;

    virtual void render_derived() const override;
};

class gui_inventory_win : public gui_win
{
  public:
    gui_inventory_win() : gui_win(0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {}

  protected:
    void render_derived() const override;

  private:
    static constexpr float k_margin{0.005f};
    static constexpr float k_slot_size{0.04f};
    inline static const str k_slot_img_name{"gui_inventory_win_slot_bg"};
};

class gui_player_body_win : public gui_win
{
  public:
    gui_player_body_win() : gui_win(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
    {
        init();
    }

  protected:
    void init();

  private:
    void sel_body_part(int type);

    void update_body_part_info_lbls();

    int sel_body_part_{0};
    s_ptr<gui_label> lbl_body_part_name_;
    s_ptr<gui_label> lbl_body_part_str_;
    s_ptr<gui_label> lbl_body_part_energy_;
    s_ptr<gui_label> lbl_body_part_temp_;
};

class gui_interact_menu : public gui_panel
{
  public:
    gui_interact_menu() : gui_panel(0.0f, 0.0f, 0.2f, 0.14f) { init(); }

    void build_menu();

  protected:
    void init();

    virtual void update_derived() override;

    virtual void render_derived() const override;

  private:
    static constexpr float k_indent_w{0.01f};
    static constexpr float k_line_h{0.025f};

    class gui_interact_menu_entry
    {
      public:
        gui_interact_menu_entry(str_view label, func<void()> action)
            : label_(label), action_(action)
        {
        }

        auto label() const { return label_; }

        auto action() const { return action_; }

      private:
        str label_;
        func<void()> action_;
    };

    vec<gui_interact_menu_entry> entries_;
};
_NS_END_