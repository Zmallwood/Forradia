//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TreeObject.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void
        TreeObject::Initialize(StringView objectTypeName)
        {
            if (objectTypeName != "object_fir_tree" &&
                objectTypeName != "object_birch_tree")
            {
                return;
            }

            int numTrunkParts;

            if (objectTypeName == "object_fir_tree")
            {
                numTrunkParts = 45 + GetRandomInt(44);
            }

            else if (objectTypeName == "object_birch_tree")
            {
                numTrunkParts = 45 + GetRandomInt(14);
            }

            m_widthFactor *=
                (GetRandomInt(5) + 1) / 2.0f + 1.0f;

            auto offsetX{0.0f};

            for (auto i = 0; i < numTrunkParts; i++)
            {
                offsetX += (GetRandomInt(40) - 20) / 100.0f;

                auto offsetY{i * 1.0f};

                auto position{PointF{offsetX, offsetY}};

                auto needlesType{GetRandomInt(5)};

                m_trunkParts.push_back(position);

                if (i < 20)
                {
                    m_needleTypes.push_back(0);

                    continue;
                }

                String needlesName;

                if (objectTypeName == "object_fir_tree")
                {
                    needlesName =
                        "object_fir_tree_needles_";
                }
                else if (objectTypeName ==
                         "object_birch_tree")
                {
                    if (i % 8 != 0)
                    {
                        m_needleTypes.push_back(0);

                        continue;
                    }

                    needlesName =
                        "object_birch_tree_branch_";
                }

                m_needleTypes.push_back(
                    needlesType
                        ? Hash(needlesName +
                               std::to_string(needlesType))
                        : 0);
            }
        }
    }
}