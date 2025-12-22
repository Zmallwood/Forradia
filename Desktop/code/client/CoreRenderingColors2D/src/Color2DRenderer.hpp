/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Color2DRenderingOperation.hpp"
#include "Coloring/Color.hpp"
#include "RendererBase.hpp"
#include <unordered_map>

namespace Forradia
{
    /**
     * A renderer for drawing colors to the canvas.
     */
    class Color2DRenderer : public RendererBase
    {
      public:
        static auto Instance() -> Color2DRenderer &
        {
            static Color2DRenderer instance;
            return instance;
        }

        // Delete copy/move
        Color2DRenderer(const Color2DRenderer &) = delete;

        auto operator=(const Color2DRenderer &) -> Color2DRenderer & = delete;

        Color2DRenderer() = default;

        /**
         * Destructor which cleans up the renderer.
         */
        ~Color2DRenderer()
        {
            // Cleanup the renderer.
            this->Cleanup();
        }

        /**
         * Draws a filled rectangle.
         *
         * @param uniqueRenderID The unique render ID.
         * @param color The color of the rectangle.
         * @param x The x coordinate of the rectangle.
         * @param y The y coordinate of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @param updateExisting Whether to update the existing operation.
         */
        auto DrawFilledRectangle(int uniqueRenderID, Color color, float xPos, float yPos,
                                 float width, float height, bool updateExisting = false) -> void;

        /**
         * Draws a line between two points.
         *
         * @param uniqueRenderID The unique render ID.
         * @param color The color of the line.
         * @param x1 The x coordinate of the first point.
         * @param y1 The y coordinate of the first point.
         * @param x2 The x coordinate of the second point.
         * @param y2 The y coordinate of the second point.
         * @param lineWidth The width of the line (normalized, as a fraction of canvas size).
         * @param updateExisting Whether to update the existing operation.
         */
        auto DrawLine(int uniqueRenderID, Color color, float xPos1, float yPos1, float xPos2,
                      float yPos2, float lineWidth = k_defaultLineWidth,
                      bool updateExisting = false) -> void;

      protected:
        /**
         * Returns the vertex shader source.
         *
         * @return The vertex shader source.
         */
        auto GetVSSource() const -> std::string override;

        /**
         * Returns the fragment shader source.
         *
         * @return The fragment shader source.
         */
        auto GetFSSource() const -> std::string override;

        /**
         * Sets up the attribute layout.
         */
        auto SetupAttributeLayout() const -> void override;

      private:
        auto Cleanup() -> void;

        auto SetupState() const -> void;

        static auto RestoreState() -> void;

        auto DrawingOperationIsCached(int uniqueRenderID) const -> bool;

        constexpr static float k_defaultLineWidth{0.001F};
        std::unordered_map<int, Color2DRenderingOperation> m_operationsCache{};
    };
}
