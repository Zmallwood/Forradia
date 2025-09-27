/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class PlayerStats
    {
    public:
        auto GetOverallBodyStrength() const { return m_overallBodyStrength; }

        auto GetRightArmStrength() const { return m_rightArmStrength; }

        auto GetLeftArmStrength() const { return m_leftArmStrength; }

        auto GetLegsStrength() const { return m_legsStrength; }

        auto GetOverallBodyEnergy() const { return m_overallBodyEnergy; }

        auto GetRightArmEnergy() const { return m_rightArmEnergy; }

        auto GetLeftArmEnergy() const { return m_leftArmEnergy; }

        auto GetLegsEnergy() const { return m_legsEnergy; }

    private:
        float m_overallBodyStrength{0.1f};
        float m_rightArmStrength{0.1f};
        float m_leftArmStrength{0.1f};
        float m_legsStrength{0.1f};
        float m_overallBodyEnergy{1.0f};
        float m_rightArmEnergy{1.0f};
        float m_leftArmEnergy{1.0f};
        float m_legsEnergy{1.0f};
    };
}