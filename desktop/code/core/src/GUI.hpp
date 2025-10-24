/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_GUI_TOP_                                           \
    namespace Core                                                             \
    {
    _HIDE_FROM_OUTLINER_GUI_TOP_
    namespace GUIComponentsLibrary
    {
        class GUIComponent
        {
          public:
            GUIComponent(float x, float y, float width, float height)
                : m_bounds({x, y, width, height})
            {
            }

            SharedPtr<GUIComponent>
            AddChildComponent(SharedPtr<GUIComponent> component);

            void Update();

            void Render() const;

            virtual RectF GetBounds() const;

            void SetPosition(PointF newPosition);

            void ToggleVisibility();

            auto GetVisible() const
            {
                return m_visible;
            }

            void SetVisible(bool value)
            {
                m_visible = value;
            }

            void SetParentComponent(GUIComponent *value)
            {
                m_parentComponent = value;
            }

          protected:
            virtual void UpdateDerived()
            {
            }

            virtual void RenderDerived() const
            {
            }

          private:
            RectF m_bounds;
            Vector<SharedPtr<GUIComponent>> m_childComponents;
            bool m_visible{true};
            bool m_enabled{true};
            GUIComponent *m_parentComponent{nullptr};
        };

        class GUILabel : public GUIComponent
        {
          public:
            GUILabel(float x, float y, float width, float height,
                     StringView text = "", bool centerAlign = false,
                     Color color = Colors::WheatTransparent)
                : GUIComponent(x, y, width, height), m_text(text),
                  m_centerAlign(centerAlign), m_color(color)
            {
            }

            void SetText(StringView value)
            {
                m_text = value;
            }

          protected:
            virtual void RenderDerived() const override;

          private:
            String m_text;
            bool m_centerAlign{false};
            Color m_color;
        };

        class GUIPanel : public GUIComponent
        {
          public:
            GUIPanel(float x, float y, float width, float height,
                     StringView backgroundImage = k_defaultBackgroundImage)
                : GUIComponent(x, y, width, height),
                  m_backgroundImage(backgroundImage)
            {
            }

          protected:
            virtual void RenderDerived() const override;

            void SetBackgroundImage(StringView value)
            {
                m_backgroundImage = value;
            }

          private:
            inline static const String k_defaultBackgroundImage{"gui_panel_bg"};

            String m_backgroundImage;
        };

        class GUIButton : public GUIPanel
        {
          public:
            GUIButton(
                float x, float y, float width, float height, StringView text,
                Function<void()> action,
                StringView backgroundImage = k_backgroundImage,
                StringView hoveredBackgroundImage = k_hoveredBackgroundImage)
                : GUIPanel(x, y, width, height), m_text(text), m_action(action),
                  m_backgroundImage(backgroundImage),
                  m_hoveredBackgroundImage(hoveredBackgroundImage)
            {
            }

          protected:
            virtual void UpdateDerived() override;

            virtual void RenderDerived() const override;

          private:
            inline static const String k_backgroundImage{"gui_button_bg"};
            inline static const String k_hoveredBackgroundImage{
                "gui_button_hovered_bg"};

            String m_text;
            Function<void()> m_action;
            String m_backgroundImage;
            String m_hoveredBackgroundImage;
        };

        class GUIMovablePanel : public GUIPanel
        {
          public:
            GUIMovablePanel(float x, float y, float width, float height)
                : GUIPanel(x, y, width, height)
            {
            }

          protected:
            void UpdateDerived() override;

            void StartMove();

            void StopMove();

            virtual RectF GetDragArea();

            auto GetIsBeingMoved() const
            {
                return m_isBeingMoved;
            }

            auto GetMoveStartingPosition() const
            {
                return m_moveStartingPosition;
            }

            auto GetMoveStartingMousePosition() const
            {
                return m_moveStartingMousePosition;
            }

          private:
            bool m_isBeingMoved{false};
            PointF m_moveStartingPosition{-1, -1};
            PointF m_moveStartingMousePosition{-1, -1};
        };

        class GUIWindow : public GUIMovablePanel
        {
          public:
            GUIWindow(float x, float y, float width, float height,
                      StringView windowTitle)
                : GUIMovablePanel(x, y, width, height)
            {
                Initialize(windowTitle);
            }

          protected:
            void RenderDerived() const override;

            RectF GetDragArea() override;

            auto GetGUIWindowTitleBar() const
            {
                return m_guiWindowTitleBar;
            }

          private:
            void Initialize(StringView windowTitle);

            class GUIWindowTitleBar : public GUIPanel
            {
              public:
                GUIWindowTitleBar(GUIWindow &parentWindow,
                                  StringView windowTitle)
                    : m_parentWindow(parentWindow), k_windowTitle(windowTitle),
                      GUIPanel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
                {
                    Initialize();
                }

                void RenderDerived() const override;

                RectF GetBounds() const override;

              private:
                void Initialize();

                inline static const float k_h{0.04f};
                const String k_windowTitle;

                GUIWindow &m_parentWindow;
            };

            SharedPtr<GUIWindowTitleBar> m_guiWindowTitleBar;
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

            SharedPtr<GUILabel> m_fpsTextPanel;
        };

        class GUIChatBox : public GUIPanel
        {
          public:
            GUIChatBox()
                : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f,
                           k_defaultBackgroundImageDerived)
            {
            }

            void RenderDerived() const override;

            void Print(StringView text);

          private:
            constexpr static StringView k_defaultBackgroundImageDerived{
                "gui_chat_box_bg"};
            inline static const float k_lineHeight{0.025f};
            inline static const float k_separatorHeight{0.003f};
            inline static const float k_margin{0.008f};

            Vector<String> m_lines;
        };
    }
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
    _HIDE_FROM_OUTLINER_CORE_BOTTOM_
}