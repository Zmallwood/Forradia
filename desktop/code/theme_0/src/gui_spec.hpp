/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_SPEC_TOP_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GUI_SPEC_TOP_
namespace SpecializedGUI
{
    class GUIPlayerStatusBox : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        GUIPlayerStatusBox() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
        }

      protected:
        virtual void render_derived() const override;
    };

    class GUISystemMenu : public Core::GUIComponentsLibrary::GUIComponent
    {
      public:
        GUISystemMenu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
        {
            init();
        }

      protected:
        void init();

        virtual void update_derived() override;

        virtual void render_derived() const override;
    };

    class GUIInventoryWindow : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        GUIInventoryWindow() : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f, "Inventory")
        {
        }

      protected:
        void render_derived() const override;

      private:
        static constexpr float k_margin{0.005f};
        static constexpr float k_slot_size{0.04f};
        inline static const String k_slot_img_name{"gui_inventory_win_slot_bg"};
    };

    class GUIPlayerBodyWindow : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        GUIPlayerBodyWindow() : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
        {
            init();
        }

      protected:
        void init();

      private:
        void sel_body_part(int type);

        void update_body_part_info_lbls();

        int sel_body_part_{0};
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_name_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_str_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_energy_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_temp_;
    };

    class GUIInteractionMenu : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        GUIInteractionMenu() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
            init();
        }

        void build_menu();

      protected:
        void init();

        virtual void update_derived() override;

        virtual void render_derived() const override;

      private:
        static constexpr float k_indent_w{0.01f};
        static constexpr float k_line_h{0.025f};

        class GUIInteractionMenuEntry
        {
          public:
            GUIInteractionMenuEntry(StringView label, Function<void()> action)
                : label_(label), action_(action)
            {
            }

            auto label() const
            {
                return label_;
            }

            auto action() const
            {
                return action_;
            }

          private:
            String label_;
            Function<void()> action_;
        };

        Vector<GUIInteractionMenuEntry> entries_;
    };
}
using namespace SpecializedGUI;
#define _HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_ }
_HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_
_NS_END_