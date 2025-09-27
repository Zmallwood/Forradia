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
        auto GetGUISystemMenu() const { return m_guiSystemMenu; }

    protected:
        void InitializeDerived() override;

        void UpdateDerived() override;

        void RenderDerived() const override;

    private:
        SharedPtr<GUISystemMenu> m_guiSystemMenu;
        SharedPtr<GUIWindow> m_inventoryWindow;
        SharedPtr<GUIPlayerStatsWindow> m_playerStatsWindow;
    };
}
