/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include <glm/glm.hpp>
// clang-format on

namespace ForradiaEngine
{
    /**
     *  Camera representing a viewpoint in 3D space.
     *
     *  Provides accessors for the camera's world-space position and the point it is looking at.
     */
    class Camera
    {
      public:
        static auto instance() -> Camera &
        {
            static Camera instance;
            return instance;
        }

        Camera(const Camera &) = delete;

        auto operator=(const Camera &) -> Camera & = delete;

        Camera() = default;

        static auto update() -> void;

        /**
         *  Get the view matrix.
         *
         *  @return The view matrix.
         */
        [[nodiscard]] auto getViewMatrix() const -> glm::mat4;

        /**
         *  Get the projection matrix.
         *
         *  @return The projection matrix.
         */
        [[nodiscard]] static auto getProjectionMatrix() -> glm::mat4;

        /**
         *  Add a delta to the current zoom amount.
         *
         *  @param zoomAmountDelta The delta to add.
         */
        auto addZoomAmountDelta(float zoomAmountDelta) -> void;

        /**
         *  Add a delta to the current rotation amount, sideways.
         *
         *  @param rotationDeltaSideways The delta to add.
         */
        auto addRotationDeltaSideways(float rotationDeltaSideways) -> void;

        /**
         *  Add a delta to the current rotation amount, vertical.
         *
         *  @param rotationDeltaVertical The delta to add.
         */
        auto addRotationDeltaVertical(float rotationDeltaVertical) -> void;

      private:
        [[nodiscard]] auto getPosition() const -> Point3F;

        [[nodiscard]] static auto getLookAt() -> Point3F;

        const float k_minZoomAmount{2.0F};
        const float k_maxZoomAmount{30.0F};
        const float k_minRotationAngleVertical{-M_PI * 3.0F / 8.0F};
        const float k_maxRotationAngleVertical{-M_PI / 8.0F};
        constexpr static float k_defaultFOV{55.0F};
        constexpr static float k_initialZoomAmount{6.0F};
        float m_zoomAmount{k_initialZoomAmount};
        float m_rotationAngleSideways{0.0F};
        // NOLINTNEXTLINE(readability-magic-numbers)
        float m_rotationAngleVertical{-M_PI / 4.0F};
        inline static Point3F m_lookAt;
    };
}
