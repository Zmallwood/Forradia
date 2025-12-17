/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Palette.hpp"
#include "Hash.hpp"

namespace Forradia::Palette {
template <>
auto GetColor<Hash("Black")>() -> Color {
  return {0.0f, 0.0f, 0.0f, 1.0f};
}

template <>
auto GetColor<Hash("White")>() -> Color {
  return {1.0f, 1.0f, 0.65f, 1.0f};
}

template <>
auto GetColor<Hash("Wheat")>() -> Color {
  return {1.0f, 1.0f, 0.65f, 1.0f};
}

template <>
auto GetColor<Hash("WheatTransparent")>() -> Color {
  auto color{GetColor<Hash("Wheat")>()};
  color.a = 0.7f;
  return color;
}

template <>
auto GetColor<Hash("Yellow")>() -> Color {
  return {1.0f, 1.0f, 0.0f, 1.0f};
}

template <>
auto GetColor<Hash("YellowTransparent")>() -> Color {
  auto color{GetColor<Hash("Yellow")>()};
  color.a = 0.7f;
  return color;
}

template <>
auto GetColor<Hash("MildBlue")>() -> Color {
  return {0.0f, 0.4f, 0.9f, 1.0f};
}

template <>
auto GetColor<Hash("LightBlue")>() -> Color {
  return {0.4f, 0.4f, 1.0f, 1.0f};
}

template <>
auto GetColor<Hash("Red")>() -> Color {
  return {1.0f, 0.0f, 0.0f, 1.0f};
}

template <>
auto GetColor<Hash("Green")>() -> Color {
  return {0.0f, 1.0f, 0.0f, 1.0f};
}

template <>
auto GetColor<Hash("Brown")>() -> Color {
  return {0.5f, 0.25f, 0.0f, 1.0f};
}

template <>
auto GetColor<Hash("Gray")>() -> Color {
  return {0.5f, 0.5f, 0.5f, 1.0f};
}
}