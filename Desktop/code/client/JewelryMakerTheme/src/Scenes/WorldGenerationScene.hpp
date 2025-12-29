/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  The world generation scene is the scene where the world is generated.
     */
    class WorldGenerationScene : public IScene
    {
      public:
        WorldGenerationScene() = default;

      protected:
        /**
         *  Called when the world generation scene is entered.
         */
        auto onEnterDerived() -> void override;
    };
}
