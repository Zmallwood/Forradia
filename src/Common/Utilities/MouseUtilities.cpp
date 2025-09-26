#include "MouseUtilities.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    PointF GetNormalizedMousePosition()
    {
        int xPx;
        int yPx;

        SDL_GetMouseState(&xPx, &yPx);

        auto canvasSize{GetCanvasSize()};

        return {static_cast<float>(xPx) / canvasSize.width,
                static_cast<float>(yPx) / canvasSize.height};
    }
}