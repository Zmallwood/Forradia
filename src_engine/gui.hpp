/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  class gui_component {
   public:
    gui_component(float x, float y, float w, float h) : bounds_({x, y, w, h}) {}

    s_ptr<gui_component> add_child_component(s_ptr<gui_component> comp);

    void update();

    void render() const;

    rect_f bounds() const;

    void set_pos(pt_f new_pos);

    void toggle_visibility();

    auto visible() const { return visible_; }

    void set_visible(bool val) { visible_ = val; }

    void set_parent_comp(gui_component *value) { parent_comp_ = value; }

   protected:
    virtual void update_derived() {}

    virtual void render_derived() const {}

   private:
    rect_f bounds_;
    vec<s_ptr<gui_component>> children_;
    bool visible_{true};
    bool enabled_{true};
    gui_component *parent_comp_{nullptr};
  };

  class gui : public gui_component {
   public:
    gui() : gui_component(0.0f, 0.0f, 1.0f, 1.0f) {}
  };

  class gui_label : public gui_component {
   public:
    gui_label(float x, float y, float w, float h, str_view text = "",
              bool cent_align = false, color color = colors::wheat_transp)
        : gui_component(x, y, w, h), text_(text), cent_align_(cent_align),
          color_(color) {}

    void set_text(str_view val) { text_ = val; }

   protected:
    virtual void render_derived() const override;

   private:
    str text_;
    bool cent_align_{false};
    color color_;
  };

  class gui_panel : public gui_component {
   public:
    gui_panel(float x, float y, float w, float h,
              str_view bg_img = k_default_bg_img)
        : gui_component(x, y, w, h), bg_img_(bg_img) {}

   protected:
    virtual void render_derived() const override;

    void set_bg_img(str_view val) { bg_img_ = val; }

   private:
    inline static const str k_default_bg_img{"GUIPanelBackground"};

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
    inline static const str k_bg_img{"GUIButtonBackground"};
    inline static const str k_hovered_bg_img{"GUIButtonHoveredBackground"};

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

  class gui_window : public gui_movable_panel {
   public:
    gui_window(float x, float y, float w, float h, str_view win_title)
        : gui_movable_panel(x, y, w, h), gui_win_title_bar_(*this, win_title) {
      init();
    }

   protected:
    void render_derived() const override;

    rect_f get_drag_area() override;

   private:
    void init();

    class gui_window_title_bar {
     public:
      gui_window_title_bar(gui_window &parent_win, str_view win_title)
          : parent_win_(parent_win), k_win_title(win_title) {}

      void render() const;

      rect_f bounds() const;

     private:
      inline static const float k_h{0.04f};
      const str k_win_title;

      gui_window &parent_win_;
    };

    gui_window_title_bar gui_win_title_bar_;
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

  class gui_text_console : public gui_panel {
   public:
    gui_text_console()
        : gui_panel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived) {}

    void render_derived() const override;

    void print(str_view text);

   private:
    constexpr static str_view k_default_bg_img_derived{
        "GUITextConsoleBackground"};
    inline static const float k_line_h{0.025f};
    inline static const float k_sep_h{0.003f};
    inline static const float k_marg{0.008f};

    vec<str> lines_;
  };
}