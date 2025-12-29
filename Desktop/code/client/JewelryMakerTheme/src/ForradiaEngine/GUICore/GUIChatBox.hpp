/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <vector>
#include "GUIPanel.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine
{
    /**
     *  A chat box component for the GUI which displays a list of messages and allows the user
     *  to input a message.
     */
    class GUIChatBox : public GUIPanel
    {
      public:
        static auto instancePtr() -> std::shared_ptr<GUIChatBox>
        {
            static std::shared_ptr<GUIChatBox> instancePtr = std::make_shared<GUIChatBox>();
            return instancePtr;
        }

        static auto instance() -> GUIChatBox &
        {
            return *instancePtr();
        }

        // Delete copy/move
        GUIChatBox(const GUIChatBox &) = delete;

        auto operator=(const GUIChatBox &) -> GUIChatBox & = delete;

        /**
         *  Constructor.
         */
        GUIChatBox()
            : GUIPanel("ChatBox", k_defaultBounds.x, k_defaultBounds.y, k_defaultBounds.width,
                       k_defaultBounds.height, k_defaultBackgroundImageDerived)
        {
            this->initialize();
        }

        /**
         *  Update tasks specific to the chat box, called by the GUIComponent base class.
         */
        auto updateDerived() -> void override;

        /**
         *  Render tasks specific to the chat box, called by the GUIComponent base class.
         */
        auto renderDerived() const -> void override;

        /**
         *  Prints a message to the chat box.
         *
         *  @param text The message to print.
         */
        auto print(std::string_view text) -> void;

        /**
         *  Adds text input to the chat box.
         *
         *  @param text The text to add.
         */
        auto addTextInput(std::string_view text) -> void;

        /**
         *  Enables input to the chat box.
         */
        auto enableInput() -> void;

        /**
         *  Submits the input to the chat box.
         */
        auto submitInput() -> void;

        /**
         *  Gets whether the input is active.
         *
         *  @return Whether the input is active.
         */
        [[nodiscard]] auto getInputActive() const
        {
            return m_inputActive;
        }

      private:
        auto initialize() -> void;

        [[nodiscard]] auto getMaxNumLines() const -> int;

        constexpr static std::string_view k_defaultBackgroundImageDerived{"GUIChatBoxBackground"};
        constexpr static RectF k_defaultBounds{0.0F, 0.8F, 0.4F, 0.2F};
        constexpr static float k_lineHeight{0.028F};
        constexpr static float k_separatorHeight{0.003F};
        constexpr static float k_margin{0.008F};
        const int k_renderIDSeparator{hash("RenderIDSeparator")};
        const int k_renderIDInputCursor{hash("RenderIDInputCursor")};
        const int k_renderIDInputText{hash("RenderIDInputText")};
        const float k_cursorWidth{0.01F};
        std::vector<int> m_renderIDsTextLines{};
        std::vector<std::string> m_lines{};
        std::string m_input{};
        bool m_inputActive{false};
    };
}
