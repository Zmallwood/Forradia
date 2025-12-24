/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Camera.hpp"
#include "CanvasUtilities.hpp"
#include "Player/Player.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Forradia
{
    auto Camera::getViewMatrix() const -> glm::mat4
    {
        auto cameraPosition{getPosition()};
        auto cameraLookAt{getLookAt()};

        return glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z),
                           glm::vec3(cameraLookAt.x, cameraLookAt.y, cameraLookAt.z),
                           glm::vec3(0.0F, 0.0F, -1.0F));
    }

    auto Camera::getProjectionMatrix() -> glm::mat4
    {
        auto aspectRatio{calcAspectRatio(SDLDevice::instance().getWindow())};

        constexpr float k_near{0.1F};
        constexpr float k_far{100.0F};

        return glm::perspective(glm::radians(k_defaultFOV), aspectRatio, k_near, k_far);
    }

    auto Camera::getPosition() const -> Point3F
    {
        // Returns the camera position in world space. The position is derived from the look-at
        // point with an offset which is determined by the zoom amount and the rotation angle.

        auto point{getLookAt()};

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

    auto Camera::getLookAt() -> Point3F
    {
        // Computes the point in world space the camera should look at. This targets the center
        // of the player's current tile and uses the tile's elevation to set Z.

        auto worldArea{Theme0::World::instance().getCurrentWorldArea()};
        auto rendTileSize{Theme0::Theme0Properties::instance().getTileSize()};
        // auto playerPos{Theme0::Player::Instance().GetPosition()};
        auto playerSmoothPos{Theme0::Player::instance().getSmoothPosition()};
        auto elevHeight{Theme0::Theme0Properties::instance().getElevationHeight()};
        auto playerElevation{
            worldArea->getTile(playerSmoothPos.x, playerSmoothPos.y)->getElevation()};

        // Construct the resulting look-at point in world space.
        Point3F lookAt{playerSmoothPos.x * rendTileSize + rendTileSize / 2,
                       playerSmoothPos.y * rendTileSize + rendTileSize / 2,
                       playerElevation * elevHeight};

        return lookAt;
    }

    auto Camera::addZoomAmountDelta(float zoomAmountDelta) -> void
    {
        // Add the delta to the current zoom amount and clamp it between the minimum and maximum
        // zoom amounts.
        m_zoomAmount += zoomAmountDelta;
        m_zoomAmount = std::max(std::min(m_zoomAmount, k_maxZoomAmount), k_minZoomAmount);
    }

    auto Camera::addRotationDeltaSideways(float rotationDeltaSideways) -> void
    {
        m_rotationAngleSideways += rotationDeltaSideways;
    }

    auto Camera::addRotationDeltaVertical(float rotationDeltaVertical) -> void
    {
        // Add the delta to the current vertical rotation amount and clamp it between the
        // minimum and maximum vertical rotation angles.
        m_rotationAngleVertical += rotationDeltaVertical;

        m_rotationAngleVertical =
            std::max(std::min(m_rotationAngleVertical, k_maxRotationAngleVertical),
                     k_minRotationAngleVertical);
    }
}
