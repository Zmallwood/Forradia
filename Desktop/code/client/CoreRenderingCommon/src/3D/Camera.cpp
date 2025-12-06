//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Camera.hpp"
#include "Player/PlayerCharacter.hpp"
#include "SDLDevice.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia
{
    glm::mat4 Camera::GetViewMatrix() const
    {
        // Compute the view matrix using the camera position and look-at point.

        auto cameraPosition{GetPosition()};

        auto cameraLookAt{GetLookAt()};

        // Return the view matrix.

        return glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z),
                           glm::vec3(cameraLookAt.x, cameraLookAt.y, cameraLookAt.z),
                           glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        // Compute the projection matrix using the aspect ratio.

        auto aspectRatio{CalcAspectRatio(_<SDLDevice>().GetWindow())};

        // Return the projection matrix.

        return glm::perspective(glm::radians(k_defaultFOV), aspectRatio, 0.1f, 100.0f);
    }

    Point3F Camera::GetPosition() const
    {
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

    Point3F Camera::GetLookAt() const
    {
        // Computes the point in world space the camera should look at. This targets the center
        // of the player's current tile and uses the tile's elevation to set Z.

        // Obtain current world area and determine its size.

        auto worldArea{_<Theme0::World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        // Rendered size of a single tile in world units.

        auto rendTileSize{_<Theme0::Theme0Properties>().GetTileSize()};

        // Player position in tile-space (grid indices).

        auto playerPos{_<Theme0::GameplayCore::PlayerCharacter>().GetPosition()};

        // Multiplier mapping tile elevation to world Z height.

        auto elevHeight{_<Theme0::Theme0Properties>().GetElevationHeight()};

        // Elevation at the player's tile. Coordinates are (currently, it would be preferred if
        // it wasnt) flipped relative to render space (width - x, height - y).

        auto playerElev{worldArea->GetTile(playerPos.x, playerPos.y)->GetElevation()};

        // Construct the resulting look-at point in world space. Again, the coordinates are
        // (currently, it would be preferred if it wasnt) flipped relative to render space
        // (width - x, height - y).

        Point3F lookAt{playerPos.x * rendTileSize + rendTileSize / 2,
                       playerPos.y * rendTileSize + rendTileSize / 2, playerElev * elevHeight};

        return lookAt;
    }

    void Camera::AddZoomAmountDelta(float zoomAmountDelta)
    {
        // Add the delta to the current zoom amount and clamp it between the minimum and maximum
        // zoom amounts.

        m_zoomAmount += zoomAmountDelta;

        m_zoomAmount = std::max(std::min(m_zoomAmount, k_maxZoomAmount), k_minZoomAmount);
    }

    void Camera::AddRotationDeltaSideways(float rotationDeltaSideways)
    {
        // Add the delta to the current rotation amount.

        m_rotationAngleSideways += rotationDeltaSideways;
    }

    void Camera::AddRotationDeltaVertical(float rotationDeltaVertical)
    {
        // Add the delta to the current vertical rotation amount and clamp it between the
        // minimum and maximum vertical rotation angles.

        m_rotationAngleVertical += rotationDeltaVertical;

        m_rotationAngleVertical =
            std::max(std::min(m_rotationAngleVertical, k_maxRotationAngleVertical),
                     k_minRotationAngleVertical);
    }
}