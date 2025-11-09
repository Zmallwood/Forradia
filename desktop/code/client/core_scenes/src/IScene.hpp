//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class IScene
    {
      public:
        class ScenesGUI
        {
          public:
            class GUIRoot : public GUIComponent
            {
              public:
                GUIRoot() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
                {
                }
            };
        };

        void Initialize();

        void Update();

        void Render() const;

        void OnEnter();

        void SetInitializeDerived(Function<void()> value)
        {
            m_initializeDerived = value;
        }

        void SetOnEnterDerived(Function<void()> value)
        {
            m_onEnterDerived = value;
        }

        void SetUpdateDerived(Function<void()> value)
        {
            m_updateDerived = value;
        }

        void SetRenderDerived(Function<void()> value)
        {
            m_renderDerived = value;
        }

      protected:
        auto GetGUI() const
        {
            return m_gui;
        }

      private:
        SharedPtr<ScenesGUI::GUIRoot> m_gui;

        Function<void()> m_initializeDerived{[] {}};

        Function<void()> m_onEnterDerived{[] {}};

        Function<void()> m_updateDerived{[] {}};

        Function<void()> m_renderDerived{[] {}};
    };
}