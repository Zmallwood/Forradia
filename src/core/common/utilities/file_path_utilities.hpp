/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  String GetFileExtension(StringView path);

  String GetFileNameNoExtension(StringView path);
}