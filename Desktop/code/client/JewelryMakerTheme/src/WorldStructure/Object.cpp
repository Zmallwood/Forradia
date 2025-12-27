/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Object.hpp"

#include "ContainedObjects.hpp"
#include "Properties/ObjectIndex.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto Object::initialize() -> void
    {
        // Randomize the model scaling.
        m_modelScaling = 0.75F + static_cast<float>(getRandomInt(100)) / 200.0F;

        auto numContainerSlots{ObjectIndex::instance().getNumContainerSlots(m_type)};
        m_containedObjects = std::make_shared<ContainedObjects>(numContainerSlots);
    }
}
