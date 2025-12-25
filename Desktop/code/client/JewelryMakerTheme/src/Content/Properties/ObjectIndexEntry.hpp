/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Class for storing object properties.
     */
    class ObjectIndexEntry
    {
      public:
        float modelScaling{1.0F}; ///< The scaling factor for the object model.
        bool ignoreIndividualModelScaling{
            false}; ///< Whether to ignore the individual model scaling.
        int numContainerSlots{0};
        bool blocksMovement{false};
    };
}
