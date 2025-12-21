/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Camera.hpp"
#include "CanvasUtilities.hpp"
#include "Player/Player.hpp"
#include "SDLDevice.hpp"
#include "StdAfx.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Forradia {
    auto Camera::GetViewMatrix() const -> glm::mat4 {
        auto cameraPosition{GetPosition()};
        auto cameraLookAt{GetLookAt()};
        return glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z),
                           glm::vec3(cameraLookAt.x, cameraLookAt.y, cameraLookAt.z),
                           glm::vec3(0.0F, 0.0F, -1.0F));
    }

    auto Camera::GetProjectionMatrix() -> glm::mat4 {
        auto aspectRatio{CalcAspectRatio(Singleton<SDLDevice>().GetWindow())};
        constexpr float k_near{0.1F};
        constexpr float k_far{100.0F};
        return glm::perspective(glm::radians(k_defaultFOV), aspectRatio, k_near, k_far);
    }

    auto Camera::GetPosition() const -> Point3F {
        // Returns the camera position in world space. The position is derived from the look-at
        // point with an offset which is determined by the zoom amount and the rotation angle.

        auto point{GetLookAt()};

        // Calculate the rotation in the X and Y axes.
        auto cosRotation{std::cos(m_rotationAngleSideways + M_PI / 2)};
        auto sinRotation{std::sin(m_rotationAngleSideways + M_PI / 2)};

        // Calculate the vertical rotation.
        auto cosVertical{std::cos(-m_rotationAngleVertical)};
        auto sinVertical{std::sin(-m_rotationAngleVertical)};

        // Apply the distance based on the zoom amount and vertical rotation.
        // The horizontal distance is scaled by the vertical angle, and the vertical offset
        // is determined by the vertical angle.
        auto horizontalDistance{cosVertical * m_zoomAmount};

        point.x += cosRotation * horizontalDistance;
        point.y += sinRotation * horizontalDistance;
        point.z += sinVertical * m_zoomAmount;
        return point;
    }

    auto Camera::GetLookAt() -> Point3F {
        // Computes the point in world space the camera should look at. This targets the center
        // of the player's current tile and uses the tile's elevation to set Z.

        auto worldArea{Singleton<Theme0::World>().GetCurrentWorldArea()};
        auto rendTileSize{Singleton<Theme0::Theme0Properties>().GetTileSize()};
        auto playerPos{Singleton<Theme0::Player>().GetPosition()};
        auto elevHeight{Singleton<Theme0::Theme0Properties>().GetElevationHeight()};
        auto playerElevation{worldArea->GetTile(playerPos.x, playerPos.y)->GetElevation()};

        // Construct the resulting look-at point in world space.
        Point3F lookAt{playerPos.x * rendTileSize + rendTileSize / 2,
                       playerPos.y * rendTileSize + rendTileSize / 2, playerElevation * elevHeight};
        return lookAt;
    }

    auto Camera::AddZoomAmountDelta(float zoomAmountDelta) -> void {
        // Add the delta to the current zoom amount and clamp it between the minimum and maximum
        // zoom amounts.
        m_zoomAmount += zoomAmountDelta;
        m_zoomAmount = std::max(std::min(m_zoomAmount, k_maxZoomAmount), k_minZoomAmount);
    }

    auto Camera::AddRotationDeltaSideways(float rotationDeltaSideways) -> void {
        m_rotationAngleSideways += rotationDeltaSideways;
    }

    auto Camera::AddRotationDeltaVertical(float rotationDeltaVertical) -> void {
        // Add the delta to the current vertical rotation amount and clamp it between the
        // minimum and maximum vertical rotation angles.
        m_rotationAngleVertical += rotationDeltaVertical;
        m_rotationAngleVertical =
            std::max(std::min(m_rotationAngleVertical, k_maxRotationAngleVertical),
                     k_minRotationAngleVertical);
    }
}
