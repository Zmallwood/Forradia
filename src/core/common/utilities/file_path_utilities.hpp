/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  str GetFileExtension(str_view path);

  str GetFileNameNoExtension(str_view path);
}