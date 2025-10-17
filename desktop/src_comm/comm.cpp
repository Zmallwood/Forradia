/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "comm.hpp"

_NS_START_
////////////////////
// Convenience
////////////////////
void sdl_del::operator()(SDL_Window *win) const {
  // Free up resources from a SDL_Window object.
  SDL_DestroyWindow(win);
}

void sdl_del::operator()(SDL_Renderer *rend) const {
  // Free up resources from a SDL_Renderer object.
  SDL_DestroyRenderer(rend);
}

void sdl_del::operator()(SDL_Surface *surf) const {
  // Free up resources from a SDL_Surface object.
  SDL_FreeSurface(surf);
}

void sdl_del::operator()(SDL_Texture *tex) const {
  // Free up resources from a SDL_Texture object.
  SDL_DestroyTexture(tex);
}

void sdl_del::operator()(TTF_Font *font) const {
  // Free up resources from a TTF_Font object.
  TTF_CloseFont(font);
}

////////////////////
// Matter
////////////////////
bool pt::operator==(const pt &p) const {
  // Compare x and y dimensions.
  return p.x == x && p.y == y;
}

pt_f pt_f::operator+(const pt_f &p) const {
  // Sum the dimensions of the two points.
  return {x + p.x, y + p.y};
}

pt_f pt_f::operator-(const pt_f &p) const {
  // Subract the dimensions of the other point from this point.
  return {x - p.x, y - p.y};
}

bool rect_f::contains(pt_f p) {
  // Create condition by checking against the boundaries of this rectangle.
  return p.x >= x && p.y >= y && p.x < x + w && p.y < y + h;
}

pt_f rect_f::pos() const {
  // Return only the coordinates.
  return {x, y};
}

void rect_f::offs(pt_f offs) {
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
sz get_canv_sz(s_ptr<SDL_Window> win) {
  sz canv_sz;
  // Get the size of the window.
  SDL_GetWindowSize(win.get(), &canv_sz.w, &canv_sz.h);
  return canv_sz;
}

float calc_aspect_ratio(s_ptr<SDL_Window> win) {
  auto canv_sz{get_canv_sz(win)};
  // Calculate the aspect ratio.
  auto asp_rat{c_float(canv_sz.w) / canv_sz.h};
  return asp_rat;
}

float conv_w_to_h(float w, s_ptr<SDL_Window> win) {
  // Calculate the height based on the width and the aspect ratio.
  return w * calc_aspect_ratio(win);
}

float conv_h_to_w(float h, s_ptr<SDL_Window> win) {
  // Calculate the width based on the height and the aspect ratio.
  return h / calc_aspect_ratio(win);
}

// File path util functions
str file_ext(str_view path) {
  // Get the file extension.
  str ext{path.substr(path.find_last_of('.') + 1).data()};
  return ext;
}

str file_name_no_ext(str_view path) {
  // Get the file name without the extension.
  auto name_with_ext{str(path.substr(path.find_last_of('/') + 1))};
  return name_with_ext.substr(0, name_with_ext.find_last_of('.'));
}

// Numbers util functions
pt_f norm_mouse_pos(s_ptr<SDL_Window> win) {
  int x_px;
  int y_px;
  // Get the mouse position.
  SDL_GetMouseState(&x_px, &y_px);
  auto canv_sz{get_canv_sz(win)};
  // Calculate the normalized mouse position.
  return {c_float(x_px) / canv_sz.w, c_float(y_px) / canv_sz.h};
}

float inv_movem_spd(float num) {
  // Calculate the inverse of the movement speed.
  if (num)
    // If the movement speed is not zero, invert it and return.
    return k_one_sec_millis / num;
  else
    // If the movement speed is zero, avoid division by zero
    // and return zero directly instead.
    return 0.0f;
}

int normalize(int val) {
  auto abs_val{std::abs(val)};
  auto norm{0};
  // Calculate the normalized value.
  if (val)
    norm = val / abs_val;
  return norm;
}

float ceil(float num, float k) {
  // Calculate the ceiled value with k decimal places.
  auto p{std::pow(10.0, k)};
  return std::ceil(num * p) / p;
}

// Randomization util functions
void randomize() {
  // Randomize the seed.
  srand(time(nullptr));
}

int rand_int(int upper_lim) {
  // Generate a random integer.
  return rand() % upper_lim;
}

// String util functions
str repl(str_view text, char repl, char repl_with) {
  str res{text.data()};
  // Replace all instances of repl with repl_with.
  std::replace(res.begin(), res.end(), repl, repl_with);
  return res;
}

// Time util functions
int ticks() {
  // Get the number of ticks.
  return SDL_GetTicks();
}

// Hash util functions
int hash(str_view text) {
  // Use algorithm from source which is forgotten what it was.
  unsigned long hash{5381};
  for (size_t i = 0; i < text.size(); ++i)
    hash = 33 * hash + (unsigned char)text[i];
  return c_int(hash);
}

// Print util functions
void print(str_view text) {
  // Print out text without a following line break.
  std::cout << text;
}

void print_ln(str_view text) {
  // Print out text with a following line break.
  std::cout << text << std::endl;
}
_NS_END_