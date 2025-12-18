/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIPanel.hpp"

namespace Forradia {
  /**
   * A chat box component for the GUI which displays a list of messages and allows the user
   * to input a message.
   */
  class GUIChatBox : public GUIPanel {
   public:
    /**
     * Constructor.
     */
    GUIChatBox() : GUIPanel("ChatBox", 0.0F, 0.8F, 0.4F, 0.2F, k_defaultBackgroundImageDerived) {
      this->Initialize();
    }

    /**
     * Update tasks specific to the chat box, called by the GUIComponent base class.
     */
    auto UpdateDerived() -> void override;

    /**
     * Render tasks specific to the chat box, called by the GUIComponent base class.
     */
    auto RenderDerived() const -> void override;

    /**
     * Prints a message to the chat box.
     *
     * @param text The message to print.
     */
    auto Print(StringView text) -> void;

    /**
     * Enables input to the chat box.
     */
    auto EnableInput() -> void;

    /**
     * Submits the input to the chat box.
     */
    auto SubmitInput() -> void;

    /**
     * Gets whether the input is active.
     *
     * @return Whether the input is active.
     */
    auto GetInputActive() const {
      return m_inputActive;
    }

   private:
    auto Initialize() -> void;

    auto GetMaxNumLines() const -> int;

    constexpr static StringView k_defaultBackgroundImageDerived{"GUIChatBoxBackground"};
    inline static const float k_lineHeight{0.028F};
    inline static const float k_separatorHeight{0.003F};
    inline static const float k_margin{0.008f};
    const int k_renderIDSeparator{Hash("RenderIDSeparator")};
    const int k_renderIDInputCursor{Hash("RenderIDInputCursor")};
    const int k_renderIDInputText{Hash("RenderIDInputText")};
    Vector<int> m_renderIDsTextLines;
    Vector<String> m_lines;
    String m_input;
    bool m_inputActive{false};
  };
}
