/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "CanvasUtilities.hpp"
#include "Functions.hpp"

namespace Forradia {
  auto GetCanvasSize(const std::shared_ptr<SDL_Window> &window) -> Size {
    Size canvasSize;
    SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);
    return canvasSize;
  }

  auto CalcAspectRatio(const std::shared_ptr<SDL_Window> &window) -> float {
    auto canvasSize{GetCanvasSize(window)};
    auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};
    return aspectRatio;
  }

  auto ConvertWidthToHeight(float width, const std::shared_ptr<SDL_Window> &window) -> float {
    return width * CalcAspectRatio(window);
  }

  auto ConvertHeightToWidth(float height, const std::shared_ptr<SDL_Window> &window) -> float {
    return height / CalcAspectRatio(window);
  }
}
