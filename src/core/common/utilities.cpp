/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "utilities.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  size GetCanvasSize() {
    size canvasSize;
    SDL_GetWindowSize(GetSingleton<sdl_device>().GetWindow().get(),
                      &canvasSize.width, &canvasSize.height);
    return canvasSize;
  }

  float CalculateAspectRatio() {
    auto canvasSize{GetCanvasSize()};
    auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};
    return aspectRatio;
  }

  float ConvertWidthToHeight(float width) {
    return width * CalculateAspectRatio();
  }

  float ConvertHeightToWidth(float height) {
    return height / CalculateAspectRatio();
  }

  str GetFileExtension(str_view path) {
    str extension{path.substr(path.find_last_of('.') + 1).data()};
    return extension;
  }

  str GetFileNameNoExtension(str_view path) {
    auto nameWithExtension{str(path.substr(path.find_last_of('/') + 1))};
    return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
  }

  point_f GetNormalizedMousePosition() {
    int xPx;
    int yPx;
    SDL_GetMouseState(&xPx, &yPx);
    auto canvasSize{GetCanvasSize()};
    return {CFloat(xPx) / canvasSize.width, CFloat(yPx) / canvasSize.height};
  }

  float InvertMovementSpeed(float number) {
    if (number) {
      return k_oneSecondMillis / number;
    } else {
      return 0.0f;
    }
  }

  int Normalize(int value) {
    auto absValue{std::abs(value)};
    auto normalized{0};
    if (value) {
      normalized = value / absValue;
    }
    return normalized;
  }

  float Ceil(float number, float k) {
    auto p{std::pow(10.0, k)};
    return std::ceil(number * p) / p;
  }

  void Randomize() { srand(time(nullptr)); }

  int RandomInt(int upperLimit) { return rand() % upperLimit; }

  str Replace(str_view text, char replaced, char replacedWith) {
    str textData{text.data()};
    std::replace(textData.begin(), textData.end(), replaced, replacedWith);
    return textData;
  }
}