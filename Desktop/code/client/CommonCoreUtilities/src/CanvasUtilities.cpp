//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "CanvasUtilities.hpp"

#include "Functions.hpp"

namespace AAK
{
    namespace Forradia
    {
        Size GetCanvasSize(SharedPtr<SDL_Window> window)
        {
            Size canvasSize;

            // Get the size of the window.

            SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);

            return canvasSize;
        }

        float CalcAspectRatio(SharedPtr<SDL_Window> window)
        {
            auto canvasSize{GetCanvasSize(window)};

            // Calculate the aspect ratio.

            auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};

            return aspectRatio;
        }

        float ConvertWidthToHeight(float width, SharedPtr<SDL_Window> window)
        {
            // Calculate the height based on the width and the aspect ratio.

            return width * CalcAspectRatio(window);
        }

        float ConvertHeightToWidth(float height, SharedPtr<SDL_Window> window)
        {
            // Calculate the width based on the height and the aspect ratio.

            return height / CalcAspectRatio(window);
        }
    }
}