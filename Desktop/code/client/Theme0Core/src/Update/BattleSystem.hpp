//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0 {
    class Robot;
}

namespace Forradia::Theme0::GameplayCore {
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