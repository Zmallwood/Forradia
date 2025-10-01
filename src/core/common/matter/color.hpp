/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
/**
 * \brief A RGBA color with components defined with float values.
 */
class Color {
public:
  /**
   * \brief Convert this color to a corresponding SDL_Color object.
   *
   * \return Corresponding SDL_Color object.
   */
  SDL_Color ToSDLColor() const;

  float r{0.0f};
  float g{0.0f};
  float b{0.0f};
  float a{0.0f};
};
}