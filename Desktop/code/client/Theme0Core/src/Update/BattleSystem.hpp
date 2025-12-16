/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
class Robot;

class BattleSystem {
 public:
  void Update();

  auto GetTargetedRobot() const {
    return m_targetedRobot;
  }

  void SetTargetedRobot(SharedPtr<Robot> value) {
    m_targetedRobot = value;
  }

 private:
  SharedPtr<Robot> m_targetedRobot;
};
}