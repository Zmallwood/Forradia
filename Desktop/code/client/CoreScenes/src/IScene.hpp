/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
    class GUI;

    /**
     * The base class for all scenes.
     */
    class IScene {
      public:
        /**
         * Initializes the scene.
         */
        auto Initialize() -> void;

        /**
         * Called when the scene is entered.
         */
        auto OnEnter() -> void;

        virtual auto OnMouseDown(Uint8 mouseButton) -> void;

        virtual auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void;

        virtual auto OnMouseWheel(int delta) -> void;

        /**
         * Updates the scene.
         */
        virtual auto Update() -> void;

        /**
         * Renders the scene.
         */
        virtual auto Render() const -> void;

      protected:
        /**
         * Initializes the scene. Should be specific to the deriving class.
         */
        virtual auto InitializeDerived() -> void {
        }

        /**
         * Called when the scene is entered. Should be specific to the deriving class.
         */
        virtual auto OnEnterDerived() -> void {
        }

        /**
         * Updates the scene. Should be specific to the deriving class.
         */
        virtual auto UpdateDerived() -> void {
        }

        /**
         * Renders the scene. Should be specific to the deriving class.
         */
        virtual auto RenderDerived() const -> void {
        }

        /**
         * Gets the GUI.
         *
         * @return The GUI.
         */
        auto GetGUI() const -> std::shared_ptr<GUI> {
            return m_gui;
        }

      private:
        std::shared_ptr<GUI> m_gui;
    };
}
