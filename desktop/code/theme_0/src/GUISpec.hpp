//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUI.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace SpecializedGUI
        {
            class GUIPlayerStatusBox
                : public GUIComponentsLibrary::GUIPanel
            {
              public:
                GUIPlayerStatusBox()
                    : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
                {
                }

              protected:
                virtual void RenderDerived() const override;
            };

            class GUISystemMenu
                : public GUIComponentsLibrary::GUIComponent
            {
              public:
                GUISystemMenu()
                    : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
                {
                    Initialize();
                }

              protected:
                void Initialize();

                virtual void UpdateDerived() override;

                virtual void RenderDerived() const override;
            };

            class GUIInventoryWindow
                : public GUIComponentsLibrary::GUIWindow
            {
              public:
                GUIInventoryWindow()
                    : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f,
                                "Inventory")
                {
                }

              protected:
                void RenderDerived() const override;

              private:
                static constexpr float k_margin{0.005f};
                static constexpr float k_slotSize{0.04f};
                inline static const String k_slotImageName{
                    "gui_inventory_win_slot_bg"};
            };

            class GUIPlayerBodyWindow
                : public GUIComponentsLibrary::GUIWindow
            {
              public:
                GUIPlayerBodyWindow()
                    : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f,
                                "Player body")
                {
                    Initialize();
                }

              protected:
                void Initialize();

              private:
                void SelectBodyPart(int type);

                void UpdateBodyPartInfoLabels();

                int m_selectedBodyPart{0};
                SharedPtr<GUIComponentsLibrary::GUILabel>
                    m_labelBodyPartName;
                SharedPtr<GUIComponentsLibrary::GUILabel>
                    m_labelBodyPartStrength;
                SharedPtr<GUIComponentsLibrary::GUILabel>
                    m_labelBodyPartEnergy;
                SharedPtr<GUIComponentsLibrary::GUILabel>
                    m_labelBodyPartTemperature;
            };

            class GUIInteractionMenu
                : public GUIComponentsLibrary::GUIPanel
            {
              public:
                GUIInteractionMenu()
                    : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
                {
                    Initialize();
                }

                void BuildMenu();

              protected:
                void Initialize();

                virtual void UpdateDerived() override;

                virtual void RenderDerived() const override;

              private:
                static constexpr float k_indentWidth{0.01f};
                static constexpr float k_lineHeight{0.025f};

                class GUIInteractionMenuEntry
                {
                  public:
                    GUIInteractionMenuEntry(
                        StringView label,
                        Function<void()> action)
                        : m_label(label), m_action(action)
                    {
                    }

                    auto GetLabel() const
                    {
                        return m_label;
                    }

                    auto GetAction() const
                    {
                        return m_action;
                    }

                  private:
                    String m_label;
                    Function<void()> m_action;
                };

                Vector<GUIInteractionMenuEntry> m_entries;
                Point m_clickedCoordinate{-1, -1};
            };
        }
        using namespace SpecializedGUI;
    }
}