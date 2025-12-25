/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIComponent.hpp"
// clang-format on

namespace ForradiaEngine
{
    class GUI;

    /**
     *  The base class for all scenes.
     */
    class IScene
    {
      public:
        virtual ~IScene() = default;

        /**
         *  Initializes the scene.
         */
        auto initialize() -> void;

        /**
         *  Called when the scene is entered.
         */
        auto onEnter() -> void;

        virtual auto onMouseDown(Uint8 mouseButton) -> void;

        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> void;

        virtual auto onMouseWheel(int delta) -> void;

        virtual auto onKeyDown(SDL_Keycode key) -> void;

        virtual auto onKeyUp(SDL_Keycode key) -> void;

        virtual auto onTextInput(std::string_view text) -> void;

        /**
         *  Updates the scene.
         */
        virtual auto update() -> void;

        /**
         *  Renders the scene.
         */
        virtual auto render() const -> void;

        /**
         *  Gets the GUI.
         *
         *  @return The GUI.
         */
        [[nodiscard]] auto getGUI() const -> std::shared_ptr<GUI>
        {
            return m_gui;
        }

      protected:
        /**
         *  Initializes the scene. Should be specific to the deriving class.
         */
        virtual auto initializeDerived() -> void
        {
        }

        /**
         *  Called when the scene is entered. Should be specific to the deriving class.
         */
        virtual auto onEnterDerived() -> void
        {
        }

        /**
         *  Updates the scene. Should be specific to the deriving class.
         */
        virtual auto updateDerived() -> void
        {
        }

        /**
         *  Renders the scene. Should be specific to the deriving class.
         */
        virtual auto renderDerived() const -> void
        {
        }

      private:
        std::shared_ptr<GUI> m_gui{};
    };
}
