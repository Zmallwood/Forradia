//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GroundRenderingGroupOperation.hpp"
#include "GroundRenderingOperation.hpp"
#include "RendererBase.hpp"
#include "TileDrawGroup.hpp"

namespace Forradia
{
    ///
    /// A renderer for the ground tiles.
    ///
    class GroundRenderer : public RendererBase
    {
      public:
        ///
        /// Destructor that cleans up the renderer.
        ///
        ~GroundRenderer()
        {
            // Cleanup the renderer.

            this->Cleanup();
        }

        ///
        /// Draws a tile in the game world.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @param imageNameHash The image name hash.
        /// @param xCoordinate The x coordinate.
        /// @param yCoordinate The y coordinate.
        /// @param tileSize The tile size.
        /// @param elevations The elevations.
        /// @param forceUpdate Whether to force update the tile.
        ///
        void DrawTile(int uniqueRenderID, int imageNameHash, int xCoordinate, int yCoordinate,
                      float tileSize, const Vector<float> &elevations, bool forceUpdate = false);

        ///
        /// Draws a batch of tiles in a single operation. Tiles are automatically grouped by
        /// texture and rendered efficiently.
        ///
        /// @param tiles The vector of tiles to draw.
        ///
        void DrawTiles(const Vector<TileData> &tiles);

        ///
        /// Resets the renderer with regards to the operations cache. Called for instance when a
        /// new map is loaded from file.
        ///
        void Reset();

        ///
        /// Cleans up the renderer.
        ///
        void Cleanup();

        ///
        /// Sets up the state for the renderer.
        ///
        void SetupState() const;

        ///
        /// Restores the state for the renderer.
        ///
        void RestoreState() const;

      protected:
        ///
        /// Returns the vertex shader source.
        ///
        String GetVSSource() const override;

        ///
        /// Returns the fragment shader source.
        ///
        String GetFSSource() const override;

        ///
        /// Does initialization that is specific to this renderer.
        ///
        void InitializeDerived() override;

        ///
        /// Sets up the attribute layout for the vertex shader.
        ///
        void SetupAttributeLayout() const override;

      private:
        ///
        /// Checks if a drawing operation is cached.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @return True if the drawing operation is cached, false otherwise.
        ///
        bool DrawingOperationIsCached(int uniqueRenderID) const;

        ///
        /// Calculates the vertices for a tile without normals.
        ///
        /// @param xCoordinate The x coordinate.
        /// @param yCoordinate The y coordinate.
        /// @param tileSize The tile size.
        /// @param elevations The elevations.
        /// @return The vertices for a tile without normals.
        ///
        Vector<float> CalcTileVerticesNoNormals(int xCoordinate, int yCoordinate, float tileSize,
                                                const Vector<float> &elevations,
                                                Vector<Color> colors) const;

        ///
        /// Calculates the vertices for a tile with normals.
        ///
        /// @param verticesNoNormals The vertices without normals.
        /// @return The vertices for a tile with normals.
        ///
        Vector<float> CalcTileVerticesWithNormals(const Vector<float> &verticesNoNormals) const;

        ///
        /// Calculates the normals for a tile.
        ///
        /// @param verticesNoNormals The vertices without normals.
        /// @return The normals for a tile.
        ///
        Vector<glm::vec3> CalcTileNormals(const Vector<float> &verticesNoNormals) const;

        static constexpr unsigned short k_indices[] = {0, 1, 2, 3}; ///< Indices for every tile.

        std::map<int, GroundRenderingOperation> m_operationsCache; ///< Operations cache.

        GLint m_layoutLocationMVP; ///< Layout location for the MVP matrix in the shader.

        std::map<int, GroundRenderingGroupOperation> m_groupOperationsCache; ///< Operations cache.
    };
}