/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_TOP_                                           \
    namespace Core                                                             \
    {
_HIDE_FROM_OUTLINER_GUI_TOP_
namespace GUIComponentsLibrary
{
    class GUIComponent
    {
      public:
        GUIComponent(float x, float y, float w, float h) : bounds_({x, y, w, h})
        {
        }

        SharedPtr<GUIComponent> add_child_comp(SharedPtr<GUIComponent> comp);

        void update();

        void render() const;

        virtual RectF bounds() const;

        void set_pos(PointF new_pos);

        void toggle_visible();

        auto visible() const
        {
            return visible_;
        }

        void set_visible(bool val)
        {
            visible_ = val;
        }

        void set_parent_comp(GUIComponent *value)
        {
            parent_comp_ = value;
        }

      protected:
        virtual void update_derived()
        {
        }

        virtual void render_derived() const
        {
        }

      private:
        RectF bounds_;
        Vector<SharedPtr<GUIComponent>> children_;
        bool visible_{true};
        bool enabled_{true};
        GUIComponent *parent_comp_{nullptr};
    };

    class GUILabel : public GUIComponent
    {
      public:
        GUILabel(float x, float y, float w, float h, StringView text = "",
                  bool cent_align = false, Color color = colors::wheat_transp)
            : GUIComponent(x, y, w, h), text_(text), cent_align_(cent_align),
              color_(color)
        {
        }

        void set_text(StringView val)
        {
            text_ = val;
        }

      protected:
        virtual void render_derived() const override;

      private:
        String text_;
        bool cent_align_{false};
        Color color_;
    };

    class GUIPanel : public GUIComponent
    {
      public:
        GUIPanel(float x, float y, float w, float h,
                  StringView bg_img = k_default_bg_img)
            : GUIComponent(x, y, w, h), bg_img_(bg_img)
        {
        }

      protected:
        virtual void render_derived() const override;

        void set_bg_img(StringView val)
        {
            bg_img_ = val;
        }

      private:
        inline static const String k_default_bg_img{"gui_panel_bg"};

        String bg_img_;
    };

    class GUIButton : public GUIPanel
    {
      public:
        GUIButton(float x, float y, float w, float h, StringView text,
                   Function<void()> action, StringView bg_img = k_bg_img,
                   StringView hovered_bg_img = k_hovered_bg_img)
            : GUIPanel(x, y, w, h), text_(text), action_(action),
              bg_img_(bg_img), hovered_bg_img_(hovered_bg_img)
        {
        }

      protected:
        virtual void update_derived() override;

        virtual void render_derived() const override;

      private:
        inline static const String k_bg_img{"gui_button_bg"};
        inline static const String k_hovered_bg_img{"gui_button_hovered_bg"};

        String text_;
        Function<void()> action_;
        String bg_img_;
        String hovered_bg_img_;
    };

    class GUIMovablePanel : public GUIPanel
    {
      public:
        GUIMovablePanel(float x, float y, float w, float h)
            : GUIPanel(x, y, w, h)
        {
        }

      protected:
        void update_derived() override;

        void start_move();

        void stop_move();

        virtual RectF get_drag_area();

        auto being_moved() const
        {
            return being_moved_;
        }

        auto move_start_pos() const
        {
            return move_start_pos_;
        }

        auto move_start_mouse_pos() const
        {
            return move_start_mouse_pos_;
        }

      private:
        bool being_moved_{false};
        PointF move_start_pos_{-1, -1};
        PointF move_start_mouse_pos_{-1, -1};
    };

    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(float x, float y, float w, float h, StringView win_title)
            : GUIMovablePanel(x, y, w, h)
        {
            init(win_title);
        }

      protected:
        void render_derived() const override;

        RectF get_drag_area() override;

        auto get_win_title_bar() const
        {
            return gui_win_title_bar_;
        }

      private:
        void init(StringView win_title);

        class gui_win_title_bar : public GUIPanel
        {
          public:
            gui_win_title_bar(GUIWindow &parent_win, StringView win_title)
                : parent_win_(parent_win), k_win_title(win_title),
                  GUIPanel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
            {
                init();
            }

            void render_derived() const override;

            RectF bounds() const override;

          private:
            void init();

            inline static const float k_h{0.04f};
            const String k_win_title;

            GUIWindow &parent_win_;
        };

        SharedPtr<gui_win_title_bar> gui_win_title_bar_;
    };

    class GUIFPSPanel : public GUIMovablePanel
    {
      public:
        GUIFPSPanel() : GUIMovablePanel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            init();
        }

      protected:
        void update_derived() override;

      private:
        void init();

        SharedPtr<GUILabel> fps_text_pnl_;
    };

    class GUIChatBox : public GUIPanel
    {
      public:
        GUIChatBox()
            : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived)
        {
        }

        void render_derived() const override;

        void print(StringView text);

      private:
        constexpr static StringView k_default_bg_img_derived{"gui_chat_box_bg"};
        inline static const float k_line_h{0.025f};
        inline static const float k_sep_h{0.003f};
        inline static const float k_marg{0.008f};

        Vector<String> lines_;
    };
}
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
_HIDE_FROM_OUTLINER_CORE_BOTTOM_
_NS_END_