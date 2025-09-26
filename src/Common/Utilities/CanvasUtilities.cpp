#include "CanvasUtilities.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    Size GetCanvasSize()
    {
        Size canvasSize;

        SDL_GetWindowSize(
            _<SDLDevice>().GetWindow().get(),
            &canvasSize.width,
            &canvasSize.height);

        return canvasSize;
    }

    float CalculateAspectRatio()
    {
        auto canvasSize{GetCanvasSize()};

        auto aspectRatio{
            static_cast<float>(canvasSize.width) / canvasSize.height};

        return aspectRatio;
    }

    float ConvertWidthToHeight(float width)
    {
        return width * CalculateAspectRatio();
    }

    float ConvertHeightToWidth(float height)
    {
        return height / CalculateAspectRatio();
    }
}