/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

struct SDL_Color;

namespace Forradia {
  /**
   * A RGBA color with components defined with float values.
   */
  class Color {
   public:
    /**
     * Convert this color to a corresponding SDL_Color object.
     *
     * @return Corresponding SDL_Color object.
     */
    [[nodiscard]] auto ToSDLColor() const -> SDL_Color;

    /**
     * Red component.
     */
    float r{0.0F};

    /**
     * Green component.
     */
    float g{0.0F};

    /**
     * Blue component.
     */
    float b{0.0F};

    /**
     * Alpha component.
     */
    float a{0.0F};
  };
}
