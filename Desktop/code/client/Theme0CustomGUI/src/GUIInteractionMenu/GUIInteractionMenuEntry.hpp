/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
/**
 * Represents an entry in the interaction menu.
 */
class GUIInteractionMenuEntry {
 public:
  /**
   * Constructor.
   *
   * @param label The label of the entry.
   * @param action The action to perform when the entry is clicked.
   */
  GUIInteractionMenuEntry(StringView label, Function<void()> action)
      : m_label(label), m_action(action) {
  }

  /**
   * Gets the label of the entry.
   *
   * @return The label of the entry.
   */
  auto GetLabel() const {
    return m_label;
  }

  /**
   * Gets the action of the entry.
   *
   * @return The action of the entry.
   */
  auto GetAction() const {
    return m_action;
  }

 private:
  String m_label;
  Function<void()> m_action;
};
}