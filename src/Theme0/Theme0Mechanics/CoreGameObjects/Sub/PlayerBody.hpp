/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "BodyPart.hpp"

namespace Forradia
{
    class PlayerBody : public BodyPart
    {
    public:
        auto &GetRightArmRef() { return m_rightArm; }

        auto &GetLeftArmRef() { return m_leftArm; }

        auto &GetLegsRef() { return m_legs; }

    private:
        BodyPart m_overallBody;
        BodyPart m_rightArm;
        BodyPart m_leftArm;
        BodyPart m_legs;
    };
}