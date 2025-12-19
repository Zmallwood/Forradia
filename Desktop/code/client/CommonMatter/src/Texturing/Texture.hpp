/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * A texture, primarily used for models.
   */
  class Texture {
   public:
    /**
     * Constructor for the Texture class.
     *
     * @param path The path to the texture.
     */
    Texture(std::string_view path) : path(path) {
    }

    /**
     * The path to the texture.
     */
    std::string path;
  };
}
