/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "canvas_utilities.hpp"
#include "core/sdl_device/sdl_device.hpp"

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