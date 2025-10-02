/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "utils.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  // Canvas util functions
  size get_canvas_size() {
    size canvasSize;
    SDL_GetWindowSize(get_singleton<sdl_device>().get_window().get(),
                      &canvasSize.w, &canvasSize.h);
    return canvasSize;
  }

  float calculate_aspect_ratio() {
    auto canvasSize{get_canvas_size()};
    auto aspectRatio{c_float(canvasSize.w) / canvasSize.h};
    return aspectRatio;
  }

  float convert_width_to_height(float width) {
    return width * calculate_aspect_ratio();
  }

  float convert_height_to_width(float height) {
    return height / calculate_aspect_ratio();
  }

  // File path util functions
  str get_file_extension(str_view path) {
    str extension{path.substr(path.find_last_of('.') + 1).data()};
    return extension;
  }

  str get_file_name_no_extension(str_view path) {
    auto nameWithExtension{str(path.substr(path.find_last_of('/') + 1))};
    return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
  }

  // Numbers util functions
  point_f get_normalized_mouse_position() {
    int xPx;
    int yPx;
    SDL_GetMouseState(&xPx, &yPx);
    auto canvasSize{get_canvas_size()};
    return {c_float(xPx) / canvasSize.w, c_float(yPx) / canvasSize.h};
  }

  float invert_movement_speed(float number) {
    if (number) {
      return k_one_second_millis / number;
    } else {
      return 0.0f;
    }
  }

  int normalize(int value) {
    auto absValue{std::abs(value)};
    auto normalized{0};
    if (value) {
      normalized = value / absValue;
    }
    return normalized;
  }

  float ceil(float number, float k) {
    auto p{std::pow(10.0, k)};
    return std::ceil(number * p) / p;
  }

  // Randomization util functions
  void randomize() { srand(time(nullptr)); }

  int random_int(int upperLimit) { return rand() % upperLimit; }

  // String util functions
  str replace(str_view text, char replaced, char replacedWith) {
    str textData{text.data()};
    std::replace(textData.begin(), textData.end(), replaced, replacedWith);
    return textData;
  }

  // Hash util functions
  int hash(str_view text) {
    // Use algorithm from forgotten source.
    unsigned long hash{5381};
    for (size_t i = 0; i < text.size(); ++i) {
      hash = 33 * hash + (unsigned char)text[i];
    }
    return c_int(hash);
  }

  // Print util functions
  void print(str_view text) {
    // Print out text without a following line break.
    std::cout << text;
  }

  void print_line(str_view text) {
    // Print out text with a following line break.
    std::cout << text << std::endl;
  }
}