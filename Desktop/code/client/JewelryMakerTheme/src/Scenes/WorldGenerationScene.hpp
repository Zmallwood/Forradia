/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldGenerator;

    /**
     *  The world generation scene is the scene where the world is generated.
     */
    class WorldGenerationScene : public IScene
    {
      public:
        WorldGenerationScene(WorldGenerator &worldGenerator) : m_worldGenerator(worldGenerator)
        {
        }

      protected:
        /**
         *  Called when the world generation scene is entered.
         */
        auto onEnterDerived() -> void override;

      private:
        WorldGenerator &m_worldGenerator;
    };
}
