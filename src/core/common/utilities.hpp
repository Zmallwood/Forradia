/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  // Canvas util functions
  size GetCanvasSize();

  float CalculateAspectRatio();

  float ConvertWidthToHeight(float width);

  float ConvertHeightToWidth(float height);

  // File path util functions
  str GetFileExtension(str_view path);

  str GetFileNameNoExtension(str_view path);

  // Mouse util functions
  point_f GetNormalizedMousePosition();

  // Numbers util functions
  float InvertMovementSpeed(float number);

  int Normalize(int value);

  float Ceil(float number, float k);

  // Randomization util functions
  void Randomize();

  int RandomInt(int upperLimit);

  // String util functions
  str Replace(str_view text, char replaced, char replacedWith);

  // Time util functions
  const auto GetTicks{SDL_GetTicks};

  // Cast util functions
  int CInt(auto value) { return static_cast<int>(value); }

  float CFloat(auto value) { return static_cast<float>(value); }

  Uint8 CUint8(auto value) { return static_cast<Uint8>(value); }
}