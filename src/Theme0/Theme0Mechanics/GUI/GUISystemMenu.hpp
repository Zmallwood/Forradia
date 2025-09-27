/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/GUIComponent.hpp"

namespace Forradia
{
    class GUISystemMenu : public GUIComponent
    {
    public:
        GUISystemMenu();

    protected:
        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;
    };
}