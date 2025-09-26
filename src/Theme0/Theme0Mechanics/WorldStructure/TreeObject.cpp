/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "TreeObject.hpp"

namespace Forradia
{
    TreeObject::TreeObject(std::string_view objectTypeName)
        : Object(objectTypeName)
    {
        if (objectTypeName != "ObjectFirTree" && objectTypeName != "ObjectBirchTree")
        {
            return;
        }

        int numTrunkParts;

        if (objectTypeName == "ObjectFirTree")
        {
            numTrunkParts = 35 + RandomInt(44);
        }
        else if (objectTypeName == "ObjectBirchTree")
        {
            numTrunkParts = 15 + RandomInt(14);
        }

        m_widthFactor *= (RandomInt(5) + 1) / 2.0f + 0.5f;

        auto offsetX{0.0f};

        for (auto i = 0; i < numTrunkParts; i++)
        {
            offsetX += (RandomInt(20) - 10) / 100.0f;
            auto offsetY{i * 0.1f};

            auto position{PointF{offsetX, offsetY}};

            auto needlesType{RandomInt(5)};

            m_trunkParts.push_back(position);

            std::string needlesName;

            if (objectTypeName == "ObjectFirTree")
            {
                needlesName = "ObjectFirTreeNeedles";
            }
            else if (objectTypeName == "ObjectBirchTree")
            {
                if (i % 4 != 0)
                {
                    m_needleTypes.push_back(0);

                    continue;
                }

                needlesName = "ObjectBirchTreeBranch";
            }

            m_needleTypes.push_back(needlesType ? Hash(needlesName + std::to_string(needlesType)) : 0);
        }
    }
}