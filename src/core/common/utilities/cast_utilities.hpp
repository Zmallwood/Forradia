/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace forr {
  int CInt(auto value) { return static_cast<int>(value); }

  float CFloat(auto value) { return static_cast<float>(value); }

  Uint8 CUint8(auto value) { return static_cast<Uint8>(value); }
}