/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Object.hpp"

namespace Forradia
{
    class TreeObject : public Object
    {
    public:
        TreeObject(StringView objectTypeName);

        auto GetTrunkparts() const
        {
            return m_trunkParts;
        }

        auto GetNeedleTypes() const
        {
            return m_needleTypes;
        }

        auto GetWidthFactor() const
        {
            return m_widthFactor;
        }

    private:
        Vector<PointF> m_trunkParts;
        Vector<int> m_needleTypes;
        float m_widthFactor{1.0f};
    };
}