/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <array>
    #include <unordered_map>
    #include <vector>
    
    #include <glm/glm.hpp>
    #include <GL/glew.h>
    #include <GL/gl.h>

    #include "GroundRenderingGroupOperation.hpp"
    #include "GroundRenderingOperation.hpp"
    #include "ForradiaEngine/Rendering/Base/RendererBase.hpp"
    #include "TileData.hpp"
    #include "TileDrawGroup.hpp"
// clang-format on

namespace ForradiaEngine
{
    /**
     *  A renderer for the ground tiles.
     */
    class GroundRenderer : public RendererBase
    {
      public:
        static auto instance() -> GroundRenderer &
        {
            static GroundRenderer instance;
            return instance;
        }

        GroundRenderer(const GroundRenderer &) = delete;

        auto operator=(const GroundRenderer &) -> GroundRenderer & = delete;

        GroundRenderer() = default;

        /**
         *   Destructor that cleans up the renderer.
         */
        ~GroundRenderer()
        {
            this->cleanup();
        }
        /**
         *  Draws a tile in the game world.
         *
         *  @param uniqueRenderID The unique render ID.
         *  @param imageNameHash The image name hash.
         *  @param xCoordinate The x coordinate.
         *  @param yCoordinate The y coordinate.
         *  @param tileSize The tile size.
         *  @param elevations The elevations.
         *  @param forceUpdate Whether to force update the tile.
         */
        auto drawTile(int uniqueRenderID, int imageNameHash, int xCoordinate, int yCoordinate,
                      float tileSize, const std::vector<float> &elevations,
                      bool forceUpdate = false) -> void;

        /**
         *  Draws a batch of tiles in a single operation. Tiles are automatically grouped by
         *  texture and rendered efficiently.
         *
         *  @param tiles The vector of tiles to draw.
         */
        auto drawTiles(const std::vector<TileData> &tiles) -> void;

        /**
         *  Resets the renderer with regards to the operations cache. Called for instance when a
         *  new map is loaded from file.
         */
        auto reset() -> void;

        /**
         *  Cleans up the renderer.
         */
        auto cleanup() -> void;

        /**
         *  Sets up the state for the renderer.
         */
        auto setupState() const -> void;

        /**
         *  Restores the state for the renderer.
         */
        static auto restoreState() -> void;

      protected:
        /**
         *  Returns the vertex shader source.
         */
        [[nodiscard]] auto getVSSource() const -> std::string override;

        /**
         *  Returns the fragment shader source.
         */
        [[nodiscard]] auto getFSSource() const -> std::string override;

        /**
         *  Does initialization that is specific to this renderer.
         */
        auto initializeDerived() -> void override;

        /**
         *  Sets up the attribute layout for the vertex shader.
         */
        auto setupAttributeLayout() const -> void override;

      private:
        [[nodiscard]] auto drawingOperationIsCached(int uniqueRenderID) const -> bool;

        [[nodiscard]] static auto
        calcTileVerticesNoNormals(int xCoordinate, int yCoordinate, float tileSize,
                                  const std::vector<float> &elevations, std::vector<Color> colors)
            -> std::vector<float>;

        [[nodiscard]] auto static calcTileVerticesWithNormals(
            const std::vector<float> &verticesNoNormals) -> std::vector<float>;

        [[nodiscard]] static auto calcTileNormals(const std::vector<float> &verticesNoNormals)
            -> std::vector<glm::vec3>;

        static constexpr std::array<unsigned short, 4> k_indices{0, 1, 2, 3};
        std::unordered_map<int, GroundRenderingOperation> m_operationsCache{};
        GLint m_layoutLocationMVP{};
        std::unordered_map<int, GroundRenderingGroupOperation> m_groupOperationsCache{};
    };
}
