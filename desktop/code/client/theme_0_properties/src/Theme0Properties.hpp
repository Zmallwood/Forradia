//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Theme0Properties
    {
      public:
        ///
        /// Get the game window title.
        ///
        /// @return The game window title.
        ///
        String GetGameWindowTitle() const;

        ///
        /// Get the clear color of the canvas.
        ///
        /// @return The clear color of the canvas.
        ///
        Color GetClearColor() const;

        ///
        /// Get the size of the grid rendered by the
        /// WorldView.
        ///
        /// @return The size of the grid rendered by the
        /// WorldView.
        ///
        Size GetGridSize() const;

        ///
        /// Get the base size of a single world area. This
        /// size is being scaled using GetWorldScaling() to
        /// obtain the resulting world area size.
        ///
        /// @return The base size of a single world area.
        ///
        Size GetBaseWorldAreaSize() const;

        ///
        /// Get the world scaling factor which is applied
        /// to the world area size and world generation
        /// amounts.
        ///
        /// @return The world scaling factor.
        ///
        float GetWorldScaling() const;

        ///
        /// Get the size of a single tile in opengl space.
        ///
        /// @return The size of a single tile in opengl
        /// space.
        ///
        float GetTileSize() const;

        ///
        /// Get the height of one unit of elevation in
        /// opengl 3D space.
        ///
        /// @return The height of one unit of elevation.
        ///
        float GetElevationHeight() const;
    };
}