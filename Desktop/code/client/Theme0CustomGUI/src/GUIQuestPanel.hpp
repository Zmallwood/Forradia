/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIMovablePanel.hpp"

namespace Forradia {
class GUILabel;
}

namespace Forradia::Theme0 {
/**
 * Represents the quest panel.
 */
class GUIQuestPanel : public GUIMovablePanel {
 public:
  /**
   * Constructor.
   */
  GUIQuestPanel() : GUIMovablePanel("GUIQuestPanel", 0.8f, 0.2f, 0.2f, 0.14f) {
    this->Initialize();
  }

 protected:
  /**
   * Does update logic that is specific to the quest panel.
   */
  void UpdateDerived() override;

 private:
  void Initialize();

  SharedPtr<GUILabel> m_questTitleTextPanel;
  SharedPtr<GUILabel> m_questNameTextPanel;
  SharedPtr<GUILabel> m_questDescriptionTextPanel;
  SharedPtr<GUILabel> m_questStatusTextPanel;
};
}