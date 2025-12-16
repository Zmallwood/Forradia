/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "FilePathUtilities.hpp"

namespace Forradia {
auto GetFileExtension(StringView path) -> String {
  String extension{path.substr(path.find_last_of('.') + 1).data()};
  return extension;
}

auto GetFileNameNoExtension(StringView path) -> String {
  auto nameWithExtension{String(path.substr(path.find_last_of('/') + 1))};
  return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
}
}