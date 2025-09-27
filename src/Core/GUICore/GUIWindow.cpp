#include "GUIWindow.hpp"

namespace Forradia
{
    GUIWindow::GUIWindow(float x,
                         float y,
                         float width,
                         float height)
        : GUIMovablePanel(x, y, width, height)
    {
        SetVisible(false);
    }
}
