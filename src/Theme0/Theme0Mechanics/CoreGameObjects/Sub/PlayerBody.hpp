/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class PlayerBody
    {
    public:
        auto GetOverallBodyStrength() const { return m_overallBodyStrength; }

        auto GetRightArmStrength() const { return m_rightArmStrength; }

        auto GetLeftArmStrength() const { return m_leftArmStrength; }

        auto GetLegsStrength() const { return m_legsStrength; }

        auto GetOverallBodyMaxEnergy() const { return m_overallBodyMaxEnergy; }

        auto GetRightArmMaxEnergy() const { return m_rightArmMaxEnergy; }

        auto GetLeftArmMaxEnergy() const { return m_leftArmMaxEnergy; }

        auto GetLegsMaxEnergy() const { return m_legsMaxEnergy; }

        auto GetOverallBodyHealth() const { return m_overallBodyHealth; }

        auto GetRightArmHealth() const { return m_rightArmHealth; }

        auto GetLeftArmHealth() const { return m_leftArmHealth; }

        auto GetLegsHealth() const { return m_legsHealth; }

    private:
        float m_overallBodyStrength{0.1f};
        float m_rightArmStrength{0.1f};
        float m_leftArmStrength{0.1f};
        float m_legsStrength{0.1f};
        float m_overallBodyMaxEnergy{1.0f};
        float m_rightArmMaxEnergy{1.0f};
        float m_leftArmMaxEnergy{1.0f};
        float m_legsMaxEnergy{1.0f};
        float m_overallBodyHealth{1.0f};
        float m_rightArmHealth{1.0f};
        float m_leftArmHealth{1.0f};
        float m_legsHealth{1.0f};
    };
}