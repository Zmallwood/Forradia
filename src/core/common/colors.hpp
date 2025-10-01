/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "matter.hpp"

namespace forr {
  /**
   * \brief Contains a palette of colors.
   */
  namespace colors {
    constexpr color Black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

    constexpr color Wheat{1.0f, 1.0f, 0.65f, 1.0f}; ///< Wheat color.

    constexpr color WheatTransparent{1.0f, 1.0f, 0.65f,
                                     0.7f}; ///< Transparent wheat color.

    constexpr color Yellow{1.0f, 1.0f, 0.0f, 1.0f}; ///< Yellow color.

    constexpr color YellowTransparent{1.0f, 1.0f, 0.0f,
                                      0.7f}; ///< Transparent yellow color.
  }
}
