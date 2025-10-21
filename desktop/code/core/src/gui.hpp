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

        SharedPtr<GUIComponent> AddChildComponent(SharedPtr<GUIComponent> comp);

        void Update();

        void Render() const;

        virtual RectF GetBounds() const;

        void SetPosition(PointF new_pos);

        void ToggleVisibility();

        auto GetVisible() const
        {
            return visible_;
        }

        void SetVisible(bool value)
        {
            visible_ = value;
        }

        void SetParentComponent(GUIComponent *value)
        {
            parent_component_ = value;
        }

      protected:
        virtual void UpdateDerived()
        {
        }

        virtual void RenderDerived() const
        {
        }

      private:
        RectF bounds_;
        Vector<SharedPtr<GUIComponent>> children_;
        bool visible_{true};
        bool enabled_{true};
        GUIComponent *parent_component_{nullptr};
    };

    class GUILabel : public GUIComponent
    {
      public:
        GUILabel(float x, float y, float w, float h, StringView text = "",
                  bool cent_align = false, Color color = Colors::wheat_transp)
            : GUIComponent(x, y, w, h), text_(text), cent_align_(cent_align),
              color_(color)
        {
        }

        void SetText(StringView value)
        {
            text_ = value;
        }

      protected:
        virtual void RenderDerived() const override;

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
            : GUIComponent(x, y, w, h), background_image_(bg_img)
        {
        }

      protected:
        virtual void RenderDerived() const override;

        void SetBackgroundImage(StringView value)
        {
            background_image_ = value;
        }

      private:
        inline static const String k_default_bg_img{"gui_panel_bg"};

        String background_image_;
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
        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

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
        void UpdateDerived() override;

        void StartMove();

        void StopMove();

        virtual RectF GetDragArea();

        auto GetIsBeingMoved() const
        {
            return is_being_moved_;
        }

        auto GetMoveStartingPosition() const
        {
            return move_starting_position_;
        }

        auto GetMoveStartingMousePosition() const
        {
            return move_starting_mouse_position_;
        }

      private:
        bool is_being_moved_{false};
        PointF move_starting_position_{-1, -1};
        PointF move_starting_mouse_position_{-1, -1};
    };

    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(float x, float y, float w, float h, StringView win_title)
            : GUIMovablePanel(x, y, w, h)
        {
            Initialize(win_title);
        }

      protected:
        void RenderDerived() const override;

        RectF GetDragArea() override;

        auto GetGUIWindowTitleBar() const
        {
            return gui_window_title_bar_;
        }

      private:
        void Initialize(StringView win_title);

        class GUIWindowTitleBar : public GUIPanel
        {
          public:
            GUIWindowTitleBar(GUIWindow &parent_win, StringView win_title)
                : parent_win_(parent_win), k_win_title(win_title),
                  GUIPanel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
            {
                Initialize();
            }

            void RenderDerived() const override;

            RectF GetBounds() const override;

          private:
            void Initialize();

            inline static const float k_h{0.04f};
            const String k_win_title;

            GUIWindow &parent_win_;
        };

        SharedPtr<GUIWindowTitleBar> gui_window_title_bar_;
    };

    class GUIFPSPanel : public GUIMovablePanel
    {
      public:
        GUIFPSPanel() : GUIMovablePanel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            Initialize();
        }

      protected:
        void UpdateDerived() override;

      private:
        void Initialize();

        SharedPtr<GUILabel> fps_text_pnl_;
    };

    class GUIChatBox : public GUIPanel
    {
      public:
        GUIChatBox()
            : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, k_default_bg_img_derived)
        {
        }

        void RenderDerived() const override;

        void Print(StringView text);

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