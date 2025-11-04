//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    /**
     * Camera representing a viewpoint in 3D space.
     *
     * Provides accessors for the camera's world-space
     * position and the point it is looking at.
     */
    class Camera
    {
      public:
        /**
         * Get the camera's world-space position.

         * @return The position of the camera as a Point3F.
         */
        Point3F GetPosition() const;

        /**
         * Get the world-space point the camera is looking
         at.

         * @return The target point as a Point3F.
         */
        Point3F GetLookAt() const;
    };
}