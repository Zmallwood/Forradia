#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindow : public GUIMovablePanel
    {
    public:
        GUIWindow(float x,
                  float y,
                  float width,
                  float height);
    };
}
