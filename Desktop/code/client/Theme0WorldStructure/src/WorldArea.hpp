/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  class Tile;
  class Entity;
  class Robot;

  /**
   * A world area in the game.
   */
  class WorldArea {
   public:
    /**
     * Constructor.
     *
     * @param worldAreaSize The size of the world area.
     * @param worldScaling The scaling of the world area size.
     */
    WorldArea(Size worldAreaSize, float worldScaling) {
      // Initialize the world area.

      this->Initialize(worldAreaSize, worldScaling);
    }

    /**
     * Resets the world area.
     */
    auto Reset() -> void;

    /**
     * Gets the size of the world area.
     *
     * @return The size of the world area.
     */
    auto GetSize() const -> Size;

    /**
     * Checks if a coordinate is valid in the world area.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the coordinate is valid, false otherwise.
     */
    auto IsValidCoordinate(int x, int y) const -> bool;

    /**
     * Checks if a coordinate is valid in the world area.
     *
     * @param coordinate The coordinate.
     * @return True if the coordinate is valid, false otherwise.
     */
    auto IsValidCoordinate(Point coordinate) const -> bool;

    /**
     * Gets the tile at the given coordinate.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return The tile at the given coordinate, or nullptr if the coordinate is invalid.
     */
    auto GetTile(int x, int y) const -> std::shared_ptr<Tile>;

    /**
     * Gets the tile at the given coordinate.
     *
     * @param coordinate The coordinate.
     * @return The tile at the given coordinate, or nullptr if the coordinate is invalid.
     */
    auto GetTile(Point coord) const -> std::shared_ptr<Tile>;

    /**
     * Adds a claimed coordinate.
     *
     * @param coordinate The coordinate to add.
     */
    auto AddClaimedCoordinate(Point coordinate) -> void;

    /**
     * Checks if a coordinate is claimed.
     *
     * @param coordinate The coordinate to check.
     * @return True if the coordinate is claimed, false otherwise.
     */
    auto CoordinateIsClaimed(Point coordinate) const -> bool;

    /**
     * Gets a reference to the entities mirror.
     *
     * @return A reference to the entities mirror.
     */
    auto &GetEntitiesMirrorRef() {
      return m_entitiesMirror;
    }

   private:
    auto Initialize(Size worldAreaSize, float worldScaling) -> void;

    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
    std::map<std::shared_ptr<Entity>, Point> m_entitiesMirror;
    std::set<Point> m_claimedCoordinates;
  };
}
