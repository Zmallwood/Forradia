/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
class GUIInteractionMenuEntry {
 public:
  GUIInteractionMenuEntry(StringView label, Function<void()> action)
      : m_label(label), m_action(action) {
  }

  auto GetLabel() const {
    return m_label;
  }

  auto GetAction() const {
    return m_action;
  }

 private:
  String m_label;
  Function<void()> m_action;
};
}