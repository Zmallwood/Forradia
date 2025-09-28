/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class BodyPart
    {
    public:
        auto GetStrength() const { return m_strength; }
        auto GetMaxEnergy() const { return m_maxEnergy; }
        auto GetHealth() const { return m_health; }

    private:
        float m_strength{0.1f};
        float m_maxEnergy{1.0f};
        float m_health{1.0f};
    };
}