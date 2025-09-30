/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CanvasUtilities.hpp"
#include "core/sdl_device/SDLDevice.hpp"

namespace Forradia {
  Size GetCanvasSize() {
    Size canvasSize;

    SDL_GetWindowSize(GetSingleton<SDLDevice>().GetWindow().get(),
                      &canvasSize.width, &canvasSize.height);

    return canvasSize;
  }

  float CalculateAspectRatio() {
    auto canvasSize{GetCanvasSize()};

    auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};

    return aspectRatio;
  }
}