//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Camera representing a viewpoint in 3D space.
    ///
    /// Provides accessors for the camera's world-space
    /// position and the point it is looking at.
    ///
    class Camera
    {
      public:
        ///
        /// Get the camera's world-space position.
        ///
        /// @return The position of the camera as a Point3F.
        ///
        Point3F GetPosition() const;

        ///
        /// Get the world-space point the camera is looking
        /// at.
        ///
        /// @return The target point as a Point3F.
        ///
        Point3F GetLookAt() const;

        ///
        /// Add a delta to the current zoom amount.
        ///
        /// @param zoomAmountDelta The delta to add.
        ///
        void AddZoomAmountDelta(float zoomAmountDelta);

      private:
        const float k_minZoomAmount{
            2.0f}; ///< Minimum zoom amount.

        const float k_maxZoomAmount{
            15.0f}; ///< Maximum zoom amount.

        float m_zoomAmount{6.0f}; ///< Current zoom amount.
    };
}