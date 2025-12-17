/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIInteractionMenuEntry.hpp"
#include "GUIPanel.hpp"

namespace Forradia::Theme0 {
class Robot;

/**
 * Represents the interaction menu.
 */
class GUIInteractionMenu : public GUIPanel {
 public:
  /**
   * Constructor.
   */
  GUIInteractionMenu() : GUIPanel("GUIInteractionMenu", 0.0f, 0.0f, 0.2f, 0.14f) {
    this->Initialize();
  }

  /**
   * Builds the menu.
   */
  void BuildMenu();

  /**
   * Gets the timed actions.
   *
   * @return The timed actions.
   */
  auto &GetTimedActionsRef() {
    return m_timedActions;
  }

  /**
   * Gets the clicked robot.
   *
   * @return The clicked robot.
   */
  auto GetClickedRobot() const {
    return m_clickedRobot;
  }

  /**
   * Gets the clicked coordinate.
   *
   * @return The clicked coordinate.
   */
  auto GetClickedCoordinate() const {
    return m_clickedCoordinate;
  }

 protected:
  /**
   * Initializes the interaction menu.
   */
  void Initialize();

  /**
   * Does update logic that is specific to the interaction menu.
   */
  virtual void UpdateDerived() override;

  /**
   * Does render logic that is specific to the interaction menu.
   */
  virtual void RenderDerived() const override;

 private:
  static constexpr float k_indentWidth{0.01f};
  static constexpr float k_lineHeight{0.025f};
  const int k_renderIDActionsString{Hash("GUIInteractionMenuActionsString")};
  const int k_maxNumMenuEntries{40};
  Vector<int> m_renderIDsMenuEntryStrings;
  Vector<GUIInteractionMenuEntry> m_entries;
  Point m_clickedCoordinate{-1, -1};
  SharedPtr<Robot> m_clickedRobot;
  std::map<int, int> m_timedActions;
};
}