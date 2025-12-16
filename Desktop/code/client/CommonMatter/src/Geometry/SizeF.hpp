//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

namespace Forradia {
    /// Size in 2D space with dimensions of float values.
    class SizeF {
      public:
        float width{0.0f};  ///< Width.
        float height{0.0f}; ///< Height.
    };
}