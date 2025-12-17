/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"

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
  Texture(StringView path) : path(path) {
  }

  /**
   * The path to the texture.
   */
  String path;
};
}