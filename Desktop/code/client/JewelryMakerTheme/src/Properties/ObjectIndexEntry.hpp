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
        /**
         *  The scaling factor for the object model.
         */
        float modelScaling{1.0F};
        /**
         *  Whether to ignore the individual model scaling.
         */
        bool ignoreIndividualModelScaling{false};
        int numContainerSlots{0};
        bool blocksMovement{false};
    };
}
