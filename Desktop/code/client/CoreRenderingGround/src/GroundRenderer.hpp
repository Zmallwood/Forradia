/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GroundRenderingGroupOperation.hpp"
#include "GroundRenderingOperation.hpp"
#include "RendererBase.hpp"
#include "TileDrawGroup.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Forradia {
    /**
     * A renderer for the ground tiles.
     */
    class GroundRenderer : public RendererBase {
      public:
        /**
         * Destructor that cleans up the renderer.
         */
        ~GroundRenderer() {
            this->Cleanup();
        }
        /**
         * Draws a tile in the game world.
         *
         * @param uniqueRenderID The unique render ID.
         * @param imageNameHash The image name hash.
         * @param xCoordinate The x coordinate.
         * @param yCoordinate The y coordinate.
         * @param tileSize The tile size.
         * @param elevations The elevations.
         * @param forceUpdate Whether to force update the tile.
         */
        auto DrawTile(int uniqueRenderID, int imageNameHash, int xCoordinate, int yCoordinate,
                      float tileSize, const std::vector<float> &elevations,
                      bool forceUpdate = false) -> void;

        /**
         * Draws a batch of tiles in a single operation. Tiles are automatically grouped by
         * texture and rendered efficiently.
         *
         * @param tiles The vector of tiles to draw.
         */
        auto DrawTiles(const std::vector<TileData> &tiles) -> void;

        /**
         * Resets the renderer with regards to the operations cache. Called for instance when a
         * new map is loaded from file.
         */
        auto Reset() -> void;

        /**
         * Cleans up the renderer.
         */
        auto Cleanup() -> void;

        /**
         * Sets up the state for the renderer.
         */
        auto SetupState() const -> void;

        /**
         * Restores the state for the renderer.
         */
        static auto RestoreState() -> void;

      protected:
        /**
         * Returns the vertex shader source.
         */
        auto GetVSSource() const -> std::string override;

        /**
         * Returns the fragment shader source.
         */
        auto GetFSSource() const -> std::string override;

        /**
         * Does initialization that is specific to this renderer.
         */
        auto InitializeDerived() -> void override;

        /**
         * Sets up the attribute layout for the vertex shader.
         */
        auto SetupAttributeLayout() const -> void override;

      private:
        auto DrawingOperationIsCached(int uniqueRenderID) const -> bool;

        auto CalcTileVerticesNoNormals(int xCoordinate, int yCoordinate, float tileSize,
                                       const std::vector<float> &elevations,
                                       std::vector<Color> colors) const -> std::vector<float>;

        auto CalcTileVerticesWithNormals(const std::vector<float> &verticesNoNormals) const
            -> std::vector<float>;

        auto CalcTileNormals(const std::vector<float> &verticesNoNormals) const
            -> std::vector<glm::vec3>;

        static constexpr unsigned short k_indices[] = {0, 1, 2, 3};
        std::unordered_map<int, GroundRenderingOperation> m_operationsCache;
        GLint m_layoutLocationMVP;
        std::unordered_map<int, GroundRenderingGroupOperation> m_groupOperationsCache;
    };
}
