/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  class gui_comp {
   public:
    gui_comp(float x, float y, float w, float h) : bounds_({x, y, w, h}) {}

    s_ptr<gui_comp> add_child_comp(s_ptr<gui_comp> comp);

    void update();

    void render() const;

    virtual rect_f bounds() const;

    void set_pos(pt_f new_pos);

    void toggle_visible();

    auto visible() const { return visible_; }

    void set_visible(bool val) { visible_ = val; }

    void set_parent_comp(gui_comp *value) { parent_comp_ = value; }

   protected:
    virtual void update_derived() {}

    virtual void render_derived() const {}

   private:
    rect_f bounds_;
    vec<s_ptr<gui_comp>> children_;
    bool visible_{true};
    bool enabled_{true};
    gui_comp *parent_comp_{nullptr};
  };

  class gui : public gui_comp {
   public:
    gui() : gui_comp(0.0f, 0.0f, 1.0f, 1.0f) {}
  };

  class gui_label : public gui_comp {
   public:
    gui_label(float x, float y, float w, float h, str_view text = "",
              bool cent_align = false, color color = colors::wheat_transp)
        : gui_comp(x, y, w, h), text_(text), cent_align_(cent_align),
          color_(color) {}

    void set_text(str_view val) { text_ = val; }

   protected:
    virtual void render_derived() const override;

   private:
    str text_;
    bool cent_align_{false};
    color color_;
  };

  class gui_panel : public gui_comp {
   public:
    gui_panel(float x, float y, float w, float h,
              str_view bg_img = k_default_bg_img)
        : gui_comp(x, y, w, h), bg_img_(bg_img) {}

   protected:
    virtual void render_derived() const override;

    void set_bg_img(str_view val) { bg_img_ = val; }

   private:
    inline static const str k_default_bg_img{"gui_panel_bg"};

    str bg_img_;
  };

  class gui_button : public gui_panel {
   public:
    gui_button(float x, float y, float w, float h, str_view text,
               func<void()> action, str_view bg_img = k_bg_img,
               str_view hovered_bg_img = k_hovered_bg_img)
        : gui_panel(x, y, w, h), text_(text), action_(action), bg_img_(bg_img),
          hovered_bg_img_(hovered_bg_img) {}

   protected:
    virtual void update_derived() override;

    virtual void render_derived() const override;

   private:
    inline static const str k_bg_img{"gui_button_bg"};
    inline static const str k_hovered_bg_img{"gui_button_hovered_bg"};

    str text_;
    func<void()> action_;
    str bg_img_;
    str hovered_bg_img_;
  };

  class gui_movable_panel : public gui_panel {
   public:
    gui_movable_panel(float x, float y, float w, float h)
        : gui_panel(x, y, w, h) {}

   protected:
    void update_derived() override;

    void start_move();

    void stop_move();

    virtual rect_f get_drag_area();

    auto being_moved() const { return being_moved_; }

    auto move_start_pos() const { return move_start_pos_; }

    auto move_start_mouse_pos() const { return move_start_mouse_pos_; }

   private:
    bool being_moved_{false};
    pt_f move_start_pos_{-1, -1};
    pt_f move_start_mouse_pos_{-1, -1};
  };

  class gui_win : public gui_movable_panel {
   public:
    gui_win(float x, float y, float w, float h, str_view win_title)
        : gui_movable_panel(x, y, w, h) {
      init(win_title);
    }

   protected:
    void render_derived() const override;

    rect_f get_drag_area() override;

    auto get_win_title_bar() const { return gui_win_title_bar_; }

   private:
    void init(str_view win_title);

    class gui_win_title_bar : public gui_panel {
     public:
      gui_win_title_bar(gui_win &parent_win, str_view win_title)
          : parent_win_(parent_win), k_win_title(win_title),
            gui_panel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg") {
        init();
      }

      void render_derived() const override;

      rect_f bounds() const override;

     private:
      void init();

      inline static const float k_h{0.04f};
      const str k_win_title;

      gui_win &parent_win_;
    };

    s_ptr<gui_win_title_bar> gui_win_title_bar_;
  };

  class gui_fps_panel : public gui_movable_panel {
   public:
    gui_fps_panel() : gui_movable_panel(0.92f, 0.02f, 0.07f, 0.04f) { init(); }

   protected:
    void update_derived() override;

   private:
    void init();

    s_ptr<gui_label> fps_text_pnl_;
  };

  class gui_chat_box : public gui_panel {
   public:
    gui_chat_box()
        : gui_panel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived) {}

    void render_derived() const override;

    void print(str_view text);

   private:
    constexpr static str_view k_default_bg_img_derived{"gui_chat_box_bg"};
    inline static const float k_line_h{0.025f};
    inline static const float k_sep_h{0.003f};
    inline static const float k_marg{0.008f};

    vec<str> lines_;
  };
}