//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUI;

    ///
    /// The base class for all scenes.
    ///
    class IScene
    {
      public:
        ///
        /// Initializes the scene.
        ///
        void Initialize();

        ///
        /// Called when the scene is entered.
        ///
        void OnEnter();

        ///
        /// Updates the scene.
        ///
        void Update();

        ///
        /// Renders the scene.
        ///
        void Render() const;

        ///
        /// Sets the derived initialize function.
        ///
        /// @param value The function to set.
        ///
        void SetInitializeDerived(Function<void()> value)
        {
            m_initializeDerived = value;
        }

        ///
        /// Sets the derived on enter function.
        ///
        /// @param value The function to set.
        ///
        void SetOnEnterDerived(Function<void()> value)
        {
            m_onEnterDerived = value;
        }

        ///
        /// Sets the derived update function.
        ///
        /// @param value The function to set.
        ///
        void SetUpdateDerived(Function<void()> value)
        {
            m_updateDerived = value;
        }

        ///
        /// Sets the derived render function.
        ///
        /// @param value The function to set.
        ///
        void SetRenderDerived(Function<void()> value)
        {
            m_renderDerived = value;
        }

      protected:
        ///
        /// Gets the GUI.
        ///
        /// @return The GUI.
        ///
        auto GetGUI() const
        {
            return m_gui;
        }

      private:
        SharedPtr<GUI> m_gui; ///< The GUI.

        /// TODO: Consider if the Functions should be replaced with virtual methods. Right now
        /// it is used to make it work with Python bindings.

        Function<void()> m_initializeDerived{[] {}}; ///< The derived initialize function.

        Function<void()> m_onEnterDerived{[] {}}; ///< The derived on enter function.

        Function<void()> m_updateDerived{[] {}}; ///< The derived update function.

        Function<void()> m_renderDerived{[] {}}; ///< The derived render function.
    };
}