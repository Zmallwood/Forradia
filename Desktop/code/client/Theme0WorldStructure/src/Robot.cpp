//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Robot.hpp"
#include "GUIChatBox.hpp"

namespace Forradia::Theme0
{
    void Robot::Initialize()
    {
        // Multiply movement speed by a random number between 0.5 and 2.

        m_movementSpeed *= (GetRandomInt(3) + 1) / 2.0f;
    }

    void Robot::Hit(float points)
    {
        _<GUIChatBox>().Print("You hit robot for: " + std::to_string(points));

        // Subtract the points from the health.

        m_wellBeing -= points;
    }

    bool Robot::IsKnockedOut() const
    {
        // Return true if the robot's well-being is less than or equal to 0.

        return m_wellBeing <= 0.0f;
    }
}