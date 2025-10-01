/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "file_path_utilities.hpp"

namespace forr {
  str GetFileExtension(str_view path) {
    str extension{path.substr(path.find_last_of('.') + 1).data()};
    return extension;
  }

  str GetFileNameNoExtension(str_view path) {
    auto nameWithExtension{str(path.substr(path.find_last_of('/') + 1))};
    return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
  }
}