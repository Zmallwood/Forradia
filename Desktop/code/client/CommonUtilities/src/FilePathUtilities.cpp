//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "FilePathUtilities.hpp"

namespace Forradia {
String GetFileExtension(StringView path) {
  String extension{path.substr(path.find_last_of('.') + 1).data()};
  return extension;
}

String GetFileNameNoExtension(StringView path) {
  auto nameWithExtension{String(path.substr(path.find_last_of('/') + 1))};
  return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
}
}