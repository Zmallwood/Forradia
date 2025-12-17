/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
class Robot;

class BattleSystem {
 public:
  auto Update() -> void;

  auto GetTargetedRobot() const {
    return m_targetedRobot;
  }

  auto SetTargetedRobot(SharedPtr<Robot> value) -> void {
    m_targetedRobot = value;
  }

 private:
  SharedPtr<Robot> m_targetedRobot;
};
}
