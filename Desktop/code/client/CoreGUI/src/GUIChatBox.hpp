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
  GUIChatBox() : GUIPanel("ChatBox", 0.0f, 0.8f, 0.4f, 0.2f, k_defaultBackgroundImageDerived) {
    this->Initialize();
  }

  /**
   * Update tasks specific to the chat box, called by the GUIComponent base class.
   */
  void UpdateDerived() override;

  /**
   * Render tasks specific to the chat box, called by the GUIComponent base class.
   */
  void RenderDerived() const override;

  /**
   * Prints a message to the chat box.
   *
   * @param text The message to print.
   */
  void Print(StringView text);

  /**
   * Enables input to the chat box.
   */
  void EnableInput();

  /**
   * Submits the input to the chat box.
   */
  void SubmitInput();

  /**
   * Gets whether the input is active.
   *
   * @return Whether the input is active.
   */
  auto GetInputActive() const {
    return m_inputActive;
  }

 private:
  void Initialize();

  int GetMaxNumLines() const;

  constexpr static StringView k_defaultBackgroundImageDerived{"GUIChatBoxBackground"};
  inline static const float k_lineHeight{0.028f};
  inline static const float k_separatorHeight{0.003f};
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