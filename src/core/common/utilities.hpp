/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  size GetCanvasSize();

  float CalculateAspectRatio();

  float ConvertWidthToHeight(float width);

  float ConvertHeightToWidth(float height);

  str GetFileExtension(str_view path);

  str GetFileNameNoExtension(str_view path);

  point_f GetNormalizedMousePosition();

  float InvertMovementSpeed(float number);

  int Normalize(int value);

  float Ceil(float number, float k);

  void Randomize();

  int RandomInt(int upperLimit);

  str Replace(str_view text, char replaced, char replacedWith);

  const auto GetTicks{SDL_GetTicks};

  int CInt(auto value) { return static_cast<int>(value); }

  float CFloat(auto value) { return static_cast<float>(value); }

  Uint8 CUint8(auto value) { return static_cast<Uint8>(value); }
}