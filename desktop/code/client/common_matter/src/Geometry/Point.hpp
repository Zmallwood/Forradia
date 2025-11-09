//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Point in 2D space, using dimensions of int type.
    ///
    class Point
    {
      public:
        ///
        /// Equality operator between two Points.
        ///
        /// @param other Other Point to check equality against.
        /// @return True if the two points are equal, otherwise false.
        ///
        bool operator==(const Point &other) const;

        int x{0}; ///< The x dimension.

        int y{0}; ///< The y dimension.
    };
}