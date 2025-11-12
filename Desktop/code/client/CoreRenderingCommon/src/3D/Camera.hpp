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
    /// Provides accessors for the camera's world-space position and the point it is looking at.
    ///
    class Camera
    {
      public:
        ///
        /// Get the view matrix.
        ///
        /// @return The view matrix.
        ///
        glm::mat4 GetViewMatrix() const;

        ///
        /// Get the projection matrix.
        ///
        /// @return The projection matrix.
        ///
        glm::mat4 GetProjectionMatrix() const;

        ///
        /// Add a delta to the current zoom amount.
        ///
        /// @param zoomAmountDelta The delta to add.
        ///
        void AddZoomAmountDelta(float zoomAmountDelta);

        ///
        /// Add a delta to the current rotation amount, sideways.
        ///
        /// @param rotationDeltaSideways The delta to add.
        ///
        void AddRotationDeltaSideways(float rotationDeltaSideways);

        ///
        /// Add a delta to the current rotation amount, vertical.
        ///
        /// @param rotationDeltaVertical The delta to add.
        ///
        void AddRotationDeltaVertical(float rotationDeltaVertical);

      private:
        ///
        /// Get the camera's world-space position.
        ///
        /// @return The position of the camera as a Point3F.
        ///
        Point3F GetPosition() const;

        ///
        /// Get the world-space point the camera is looking at.
        ///
        /// @return The target point as a Point3F.
        ///
        Point3F GetLookAt() const;

        const float k_minZoomAmount{2.0f}; ///< Minimum zoom amount.

        const float k_maxZoomAmount{20.0f}; ///< Maximum zoom amount.

        const float k_minRotationAngleVertical{-M_PI * 3.0f /
                                               8.0f}; ///< Minimum vertical rotation angle.

        const float k_maxRotationAngleVertical{-M_PI / 8.0f}; ///< Maximum vertical rotation angle.

        float m_zoomAmount{6.0f}; ///< Current zoom amount.

        float m_rotationAngleSideways{0.0f}; ///< Current rotation amount.

        float m_rotationAngleVertical{-M_PI / 4.0f}; ///< Current vertical rotation amount.
    };
}