/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia {
    /**
     * Point in 3D space using dimensions of float type.
     */
    class Point3F {
      public:
        float x{0.0F}; ///< The x dimension.
        float y{0.0F}; ///< The y dimension.
        float z{0.0F}; ///< The z dimension.
    };
}
