/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Palette.hpp"
#include "Hash.hpp"
#include "StdAfx.hpp"

namespace Forradia::Palette {
template <>
auto GetColor<Hash("Black")>() -> Color {
  return {0.0F, 0.0F, 0.0F, 1.0F};
}

template <>
auto GetColor<Hash("White")>() -> Color {
  return {1.0F, 1.0F, 0.65F, 1.0F};
}

template <>
auto GetColor<Hash("Wheat")>() -> Color {
  return {1.0F, 1.0F, 0.65F, 1.0F};
}

template <>
auto GetColor<Hash("WheatTransparent")>() -> Color {
  auto color{GetColor<Hash("Wheat")>()};
  color.a = 0.7F;
  return color;
}

template <>
auto GetColor<Hash("Yellow")>() -> Color {
  return {1.0F, 1.0F, 0.0F, 1.0F};
}

template <>
auto GetColor<Hash("YellowTransparent")>() -> Color {
  auto color{GetColor<Hash("Yellow")>()};
  color.a = 0.7F;
  return color;
}

template <>
auto GetColor<Hash("MildBlue")>() -> Color {
  return {0.0F, 0.4F, 0.9F, 1.0F};
}

template <>
auto GetColor<Hash("LightBlue")>() -> Color {
  return {0.4F, 0.4F, 1.0F, 1.0F};
}

template <>
auto GetColor<Hash("Red")>() -> Color {
  return {1.0F, 0.0F, 0.0F, 1.0F};
}

template <>
auto GetColor<Hash("Green")>() -> Color {
  return {0.0F, 1.0F, 0.0F, 1.0F};
}

template <>
auto GetColor<Hash("Brown")>() -> Color {
  return {0.5F, 0.25F, 0.0F, 1.0F};
}

template <>
auto GetColor<Hash("Gray")>() -> Color {
  return {0.5F, 0.5F, 0.5F, 1.0F};
}
}
