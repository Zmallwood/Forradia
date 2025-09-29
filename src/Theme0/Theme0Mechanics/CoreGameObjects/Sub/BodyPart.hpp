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
        auto GetTemperature() const { return m_temperature; }

    private:
        float m_strength{0.1f};
        float m_maxEnergy{1.0f};
        float m_temperature{37.0f};
    };
}