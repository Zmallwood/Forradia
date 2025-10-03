/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui_component {
   public:
    gui_component(float x, float y, float w, float h)
        : m_bounds({x, y, w, h}) {}

    s_ptr<gui_component> add_child_component(s_ptr<gui_component> comp);

    void update();

    void render() const;

    rect_f get_bounds() const;

    void toggle_visibility();

    void set_visible(bool val) { m_visible = val; }

    void set_parent_comp(gui_component *value) { m_parent_comp = value; }

   protected:
    virtual void update_derived() {}

    virtual void render_derived() const {}

    void set_pos(point_f new_pos);

   private:
    rect_f m_bounds;
    vec<s_ptr<gui_component>> m_children;
    bool m_visible{true};
    bool m_enabled{true};
    gui_component *m_parent_comp{nullptr};
  };

  class gui : public gui_component {
   public:
    gui() : gui_component(0.0f, 0.0f, 1.0f, 1.0f) {}
  };

  class gui_label : public gui_component {
   public:
    gui_label(float x, float y, float w, float h, str_view text = "",
              bool cent_align = false, color color = colors::wheat_transp)
        : gui_component(x, y, w, h), m_text(text), m_cent_align(cent_align),
          m_color(color) {}

    void set_text(str_view val) { m_text = val; }

   protected:
    virtual void render_derived() const override;

   private:
    str m_text;
    bool m_cent_align{false};
    color m_color;
  };

  class gui_panel : public gui_component {
   public:
    gui_panel(float x, float y, float w, float h,
              str_view bg_img = k_default_bg_img)
        : gui_component(x, y, w, h), m_bg_img(bg_img) {}

   protected:
    virtual void render_derived() const override;

    void set_bg_img(str_view val) { m_bg_img = val; }

   private:
    inline static const str k_default_bg_img{"GUIPanelBackground"};

    str m_bg_img;
  };

  class gui_button : public gui_panel {
   public:
    gui_button(float x, float y, float w, float h, str_view text,
               func<void()> action, str_view bg_img = k_bg_img,
               str_view hovered_bg_img = k_hovered_bg_img)
        : gui_panel(x, y, w, h), m_text(text), m_action(action),
          m_bg_img(bg_img), m_hovered_bg_img(hovered_bg_img) {}

   protected:
    virtual void update_derived() override;

    virtual void render_derived() const override;

   private:
    inline static const str k_bg_img{"GUIButtonBackground"};
    inline static const str k_hovered_bg_img{"GUIButtonHoveredBackground"};

    str m_text;
    func<void()> m_action;
    str m_bg_img;
    str m_hovered_bg_img;
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

    auto get_being_moved() const { return m_being_moved; }

    auto get_move_start_pos() const { return m_move_start_pos; }

    auto get_move_start_mouse_pos() const { return m_move_start_mouse_pos; }

   private:
    bool m_being_moved{false};
    point_f m_move_start_pos{-1, -1};
    point_f m_move_start_mouse_pos{-1, -1};
  };

  class gui_window : public gui_movable_panel {
   public:
    gui_window(float x, float y, float w, float h, str_view win_title)
        : gui_movable_panel(x, y, w, h), m_gui_win_title_bar(*this, win_title) {
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
          : m_parent_win(parent_win), k_win_title(win_title) {}

      void render() const;

      rect_f get_bounds() const;

     private:
      inline static const float k_h{0.04f};
      const str k_win_title;

      gui_window &m_parent_win;
    };

    gui_window_title_bar m_gui_win_title_bar;
  };

  class gui_fps_panel : public gui_movable_panel {
   public:
    gui_fps_panel() : gui_movable_panel(0.92f, 0.02f, 0.07f, 0.04f) { init(); }

   protected:
    void update_derived() override;

   private:
    void init();

    s_ptr<gui_label> m_fps_text_pnl;
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

    vec<str> m_lines;
  };
}