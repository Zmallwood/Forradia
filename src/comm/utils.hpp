/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  // Canvas util functions
  size get_canvas_size();

  float calculate_aspect_ratio();

  float convert_width_to_height(float width);

  float convert_height_to_width(float height);

  // File path util functions
  str get_file_extension(str_view path);

  str get_file_name_no_extension(str_view path);

  // Mouse util functions
  point_f get_normalized_mouse_position();

  // Numbers util functions
  float invert_movement_speed(float number);

  int normalize(int value);

  float ceil(float number, float k);

  // Randomization util functions
  void randomize();

  int random_int(int upper_limit);

  // String util functions
  str replace(str_view text, char replaced, char replaced_with);

  // Time util functions
  const auto get_ticks{SDL_GetTicks};

  // Hash util functions
  /**
   * \brief Compute hash code from a given input text, which
   *        gets computed the same every game start.
   *
   * \param text Text to compute hash code for.
   * \return Computed hash code.
   */
  int hash(str_view text);

  // Print util functions
  /**
   * \brief Print out a string of text, without a following line break.
   *
   * \param text Text to print.
   */
  void print(str_view text);

  /**
   * \brief Print out a string of text, with an added line break at the end.
   *
   * \param text Text to print.
   */
  void print_line(str_view text);

  // Cast util functions
  int c_int(auto value) { return static_cast<int>(value); }

  float c_float(auto value) { return static_cast<float>(value); }

  Uint8 c_uint8(auto value) { return static_cast<Uint8>(value); }
}