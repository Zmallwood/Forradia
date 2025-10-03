/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "comm.hpp"
#include "core/core.hpp"

namespace forr {
  ////////////////////
  // Convenience
  ////////////////////
  void sdl_deleter::operator()(SDL_Window *win) const {
    // Free up resources from a SDL_Window object.
    SDL_DestroyWindow(win);
  }

  void sdl_deleter::operator()(SDL_Renderer *rend) const {
    // Free up resources from a SDL_Renderer object.
    SDL_DestroyRenderer(rend);
  }

  void sdl_deleter::operator()(SDL_Surface *surf) const {
    // Free up resources from a SDL_Surface object.
    SDL_FreeSurface(surf);
  }

  void sdl_deleter::operator()(SDL_Texture *tex) const {
    // Free up resources from a SDL_Texture object.
    SDL_DestroyTexture(tex);
  }

  void sdl_deleter::operator()(TTF_Font *font) const {
    // Free up resources from a TTF_Font object.
    TTF_CloseFont(font);
  }

  ////////////////////
  // Matter
  ////////////////////
  bool point::operator==(const point &p) const {
    // Compare x and y dimensions.
    return p.x == x && p.y == y;
  }

  point_f point_f::operator+(const point_f &p) const {
    // Sum the dimensions of the two points.
    return {x + p.x, y + p.y};
  }

  point_f point_f::operator-(const point_f &p) const {
    // Subract the dimensions of the other point from this point.
    return {x - p.x, y - p.y};
  }

  bool rect_f::contains(point_f p) {
    // Create condition by checking against the boundaries of this rectangle.
    return p.x >= x && p.y >= y && p.x < x + w && p.y < y + h;
  }

  point_f rect_f::get_position() const {
    // Return only the coordinates.
    return {x, y};
  }

  void rect_f::offset(point_f offs) {
    // Add the offset to the dimensions separately.
    x += offs.x;
    y += offs.y;
  }

  SDL_Color color::to_sdl_color() const {
    // Calculate individual color components.
    auto r_n{c_uint8(r * 255)};
    auto g_n{c_uint8(g * 255)};
    auto b_n{c_uint8(b * 255)};
    auto a_n{c_uint8(a * 255)};
    return {r_n, g_n, b_n, a_n};
  }

  ////////////////////
  // Utils
  ////////////////////
  // Canvas util functions
  size get_canvas_size() {
    size canv_sz;
    SDL_GetWindowSize(get_singleton<sdl_device>().get_window().get(),
                      &canv_sz.w, &canv_sz.h);
    return canv_sz;
  }

  float calculate_aspect_ratio() {
    auto canv_sz{get_canvas_size()};
    auto asp_rat{c_float(canv_sz.w) / canv_sz.h};
    return asp_rat;
  }

  float convert_width_to_height(float w) {
    return w * calculate_aspect_ratio();
  }

  float convert_height_to_width(float h) {
    return h / calculate_aspect_ratio();
  }

  // File path util functions
  str get_file_extension(str_view path) {
    str ext{path.substr(path.find_last_of('.') + 1).data()};
    return ext;
  }

  str get_file_name_no_extension(str_view path) {
    auto name_with_ext{str(path.substr(path.find_last_of('/') + 1))};
    return name_with_ext.substr(0, name_with_ext.find_last_of('.'));
  }

  // Numbers util functions
  point_f get_normalized_mouse_position() {
    int x_px;
    int y_px;
    SDL_GetMouseState(&x_px, &y_px);
    auto canv_sz{get_canvas_size()};
    return {c_float(x_px) / canv_sz.w, c_float(y_px) / canv_sz.h};
  }

  float invert_movement_speed(float num) {
    if (num) {
      return k_one_second_millis / num;
    } else {
      return 0.0f;
    }
  }

  int normalize(int val) {
    auto abs_val{std::abs(val)};
    auto norm{0};
    if (val) {
      norm = val / abs_val;
    }
    return norm;
  }

  float ceil(float num, float k) {
    auto p{std::pow(10.0, k)};
    return std::ceil(num * p) / p;
  }

  // Randomization util functions
  void randomize() { srand(time(nullptr)); }

  int random_int(int upper_lim) { return rand() % upper_lim; }

  // String util functions
  str replace(str_view text, char repl, char repl_with) {
    str res{text.data()};
    std::replace(res.begin(), res.end(), repl, repl_with);
    return res;
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