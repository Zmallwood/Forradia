#include "TreeObject.hpp"

namespace Forradia
{
    TreeObject::TreeObject(std::string_view objectTypeName)
        : Object(objectTypeName)
    {
        if (objectTypeName != "ObjectFirTree")
        {
            return;
        }

        auto numTrunkParts{25 + RandomInt(44)};

        auto offsetX{0.0f};

        for (auto i = 0; i < numTrunkParts; i++)
        {
            // auto offsetX{(RandomInt(20) - 10) / 100.0f};
            offsetX += (RandomInt(20) - 10) / 100.0f;
            auto offsetY{i * 0.1f};

            auto position{PointF{offsetX, offsetY}};

            auto needlesType{RandomInt(5)};

            m_trunkParts.push_back(position);
            m_needleTypes.push_back(needlesType ? Hash("ObjectFirTreeNeedles" + std::to_string(needlesType)) : 0);
        }

        m_widthFactor *= (RandomInt(5) + 1) / 2.0f + 0.5f;
    }
}