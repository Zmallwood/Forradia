/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Object.hpp"
    #include "ContainedObjects.hpp"
    #include "Content/Properties/ObjectIndex.hpp"
// clang-format on

namespace Forradia::Theme0
{
    auto Object::initialize() -> void
    {
        // Randomize the model scaling.
        m_modelScaling = 0.75F + static_cast<float>(getRandomInt(100)) / 200.0F;

        auto numContainerSlots{ObjectIndex::instance().getNumContainerSlots(m_type)};
        m_containedObjects = std::make_shared<ContainedObjects>(numContainerSlots);
    }
}
