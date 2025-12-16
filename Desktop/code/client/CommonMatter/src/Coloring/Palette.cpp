//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Palette.hpp"
#include "Hash.hpp"

namespace Forradia::Palette {
template <>
Color GetColor<Hash("Black")>() {
  return {0.0f, 0.0f, 0.0f, 1.0f};
}

template <>
Color GetColor<Hash("White")>() {
  return {1.0f, 1.0f, 0.65f, 1.0f};
}

template <>
Color GetColor<Hash("Wheat")>() {
  return {1.0f, 1.0f, 0.65f, 1.0f};
}

template <>
Color GetColor<Hash("WheatTransparent")>() {
  auto color{GetColor<Hash("Wheat")>()};
  color.a = 0.7f;
  return color;
}

template <>
Color GetColor<Hash("Yellow")>() {
  return {1.0f, 1.0f, 0.0f, 1.0f};
}

template <>
Color GetColor<Hash("YellowTransparent")>() {
  auto color{GetColor<Hash("Yellow")>()};
  color.a = 0.7f;
  return color;
}

template <>
Color GetColor<Hash("MildBlue")>() {
  return {0.0f, 0.4f, 0.9f, 1.0f};
}

template <>
Color GetColor<Hash("LightBlue")>() {
  return {0.4f, 0.4f, 1.0f, 1.0f};
}

template <>
Color GetColor<Hash("Red")>() {
  return {1.0f, 0.0f, 0.0f, 1.0f};
}

template <>
Color GetColor<Hash("Green")>() {
  return {0.0f, 1.0f, 0.0f, 1.0f};
}

template <>
Color GetColor<Hash("Brown")>() {
  return {0.5f, 0.25f, 0.0f, 1.0f};
}

template <>
Color GetColor<Hash("Gray")>() {
  return {0.5f, 0.5f, 0.5f, 1.0f};
}
}