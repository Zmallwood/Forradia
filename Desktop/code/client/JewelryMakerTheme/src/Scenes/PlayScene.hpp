/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine
{
    class GUIButton;
}

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  The play scene is the scene where the player can choose to play a new game or continue a
     *  saved game.
     */
    class PlayScene : public IScene
    {
      protected:
        /**
         *  Initializes the play scene.
         */
        auto initializeDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        auto renderDerived() const -> void override;

      private:
        std::shared_ptr<GUIButton> m_btnToggleMuteMusic;
    };
}
