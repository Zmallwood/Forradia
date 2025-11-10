//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    ///
    /// A chat box component for the GUI which displays a list of messages and allows the user to
    /// input a message.
    ///
    class GUIChatBox : public GUIPanel
    {
      public:
        ///
        /// Constructor.
        ///
        GUIChatBox() : GUIPanel("ChatBox", 0.0f, 0.8f, 0.4f, 0.2f, k_defaultBackgroundImageDerived)
        {
            this->Initialize();
        }

        ///
        /// Render tasks specific to the chat box, called by the GUIComponent base class.
        ///
        void RenderDerived() const override;

        ///
        /// Prints a message to the chat box.
        ///
        /// @param text The message to print.
        ///
        void Print(StringView text);

        ///
        /// Enables input to the chat box.
        ///
        void EnableInput();

        ///
        /// Submits the input to the chat box.
        ///
        void SubmitInput();

        ///
        /// Gets whether the input is active.
        ///
        /// @return Whether the input is active.
        ///
        auto GetInputActive() const
        {
            return m_inputActive;
        }

      private:
        ///
        /// Initializes the chat box.
        ///
        void Initialize();

        ///
        /// Gets the maximum number of lines that can be displayed in the chat box.
        ///
        /// @return The maximum number of lines that can be displayed in the chat box.
        ///
        int GetMaxNumLines() const;

        constexpr static StringView k_defaultBackgroundImageDerived{
            "GUIChatBoxBackground"}; ///< The default background image of the chat box. The GUIPanel
                                     ///< base class also has a default background image, why this
                                     ///< is named "Derived".

        inline static const float k_lineHeight{
            0.025f}; ///< The height of each line in the chat box.

        inline static const float k_separatorHeight{
            0.003f}; ///< The height of the separator between
                     ///< the input and the messages.

        inline static const float k_margin{0.008f}; ///< The margin between the chat box and the
                                                    ///< edges of the screen.

        const int k_renderIDSeparator{Hash("RenderIDSeparator")}; ///< Render ID of the separator.

        const int k_renderIDInputCursor{Hash("RenderIDInputCursor")}; ///< Render ID of the input
                                                                      ///< cursor.

        Vector<int> m_renderIDsTextLines; ///< Render IDs of the text lines.

        Vector<String> m_lines; ///< The lines of text in the chat box.

        String m_input; ///< The input text in the chat box.

        bool m_inputActive{false}; ///< Whether the input is active.
    };
}