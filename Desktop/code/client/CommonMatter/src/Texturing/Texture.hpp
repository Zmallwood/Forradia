//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include "Aliases.hpp"

namespace Forradia {
/// A texture, primarily used for models.
class Texture {
 public:
  Texture(StringView path) : path(path) {
  }

  String path; ///< The path to the texture.
};
}