//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Object.hpp"

namespace Forradia::Theme0
{
    class TreeObject : public Object
    {
      public:
        using Object::Object;
        //     TreeObject(StringView obj_type_name) : Object(obj_type_name)
        //     {
        //         this->Initialize(obj_type_name);
        //     }

        //     auto GetTrunkParts() const
        //     {
        //         return m_trunkParts;
        //     }

        //     auto GetNeedleTypes() const
        //     {
        //         return m_needleTypes;
        //     }

        //     auto GetWidthFactor() const
        //     {
        //         return m_widthFactor;
        //     }

        //   private:
        //     void Initialize(StringView obj_type_name);

        //     Vector<PointF> m_trunkParts;

        //     Vector<int> m_needleTypes;

        //     float m_widthFactor{1.0f};
    };
}