/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class GUISystemMenu;
    class GUIWindow;
    class GUIPlayerStatsWindow;

    class MainScene : public IScene
    {
    public:
        auto GetGUISystemMenu() const
        {
            return m_guiSystemMenu;
        }

    protected:
        void Initialize() override;

        void UpdateDerived() override;

        void RenderDerived() const override;

    private:
        std::shared_ptr<GUISystemMenu> m_guiSystemMenu;
        std::shared_ptr<GUIWindow> m_inventoryWindow;
        std::shared_ptr<GUIPlayerStatsWindow> m_playerStatsWindow;
    };
}
