/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"
#include "Geometry/Size.hpp"

struct SDL_Window;

namespace Forradia {
  /** Obtain canvas size in pixels.
   *
   * @param window Window to get the canvas size for.
   * @return The canvas size in pixels.
   */
  auto GetCanvasSize(const SharedPtr<SDL_Window> &window) -> Size;

  /** Calculate the aspect ratio of a given   window.
   *
   * @param window Window to calculate the aspect ratio for.
   * @return The calculated aspect ratio.
   */
  auto CalcAspectRatio(const SharedPtr<SDL_Window> &window) -> float;

  /**
   * Convert a width to a height based on the width and the aspect ratio.
   *
   * @param width Width to convert.
   * @param window Window to calculate the aspect ratio for.
   * @return The resulting height.
   */
  auto ConvertWidthToHeight(float width, const SharedPtr<SDL_Window> &window) -> float;

  /**
   * Convert a height to a width base on the height and the aspect ratio.
   *
   * @param height Height to convert.
   * @param window Window to calculate the aspect ratio for.
   * @return The resulting width.
   */
  auto ConvertHeightToWidth(float height, const SharedPtr<SDL_Window> &window) -> float;
}
