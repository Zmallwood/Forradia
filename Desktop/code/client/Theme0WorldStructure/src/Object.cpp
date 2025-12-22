/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Object.hpp"
#include "ContainedObjects.hpp"
#include "ObjectIndex.hpp"

namespace Forradia::Theme0
{
    auto Object::Initialize() -> void
    {
        // Randomize the model scaling between 0.25f and 2.0f using integer steps.
        m_modelScaling = 0.5F + static_cast<float>(GetRandomInt(100)) / 100.0F;

        auto numContainerSlots{ObjectIndex::Instance().GetNumContainerSlots(m_type)};
        m_containedObjects = std::make_shared<ContainedObjects>(numContainerSlots);
    }
}
