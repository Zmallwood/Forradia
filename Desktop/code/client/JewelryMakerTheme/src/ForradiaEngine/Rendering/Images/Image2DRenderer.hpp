/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <unordered_map>
    
    #include <GL/glew.h>
    #include <GL/gl.h>

    #include "Image2DRenderingOperation.hpp"
    #include "ForradiaEngine/Rendering/Base/RendererBase.hpp"
// clang-format on

namespace ForradiaEngine
{
    /**
     *  A renderer for drawing images to the canvas.
     */
    class Image2DRenderer : public RendererBase
    {
      public:
        static auto instance() -> Image2DRenderer &
        {
            static Image2DRenderer instance;
            return instance;
        }

        Image2DRenderer(const Image2DRenderer &) = delete;

        auto operator=(const Image2DRenderer &) -> Image2DRenderer & = delete;

        Image2DRenderer() = default;

        /**
         *  Destructor which cleans up the renderer.
         */
        ~Image2DRenderer() override
        {
            // Clean up the renderer.
            this->cleanup();
        }

        /**
         *  Draws an image by name.
         *
         *  @param uniqueRenderID The unique render ID.
         *  @param imageName The name of the image.
         *  @param xPos The x coordinate of the image.
         *  @param yPos The y coordinate of the image.
         *  @param width The width of the image.
         *  @param height The height of the image.
         *  @param updateExisting Whether to update the existing operation.
         */
        auto drawImageByName(int uniqueRenderID, std::string_view imageName, float xPos, float yPos,
                             float width, float height, bool updateExisting = false) -> void;

        /**
         *  Draws an image by hash.
         *
         *
         *  @param uniqueRenderID The unique render ID.
         *  @param imageNameHash The hash of the image name.
         *  @param xPos The x coordinate of the image.
         *  @param yPos The y coordinate of the image.
         *  @param width The width of the image.
         *  @param height The height of the image.
         *  @param updateExisting Whether to update the existing operation.
         */
        auto drawImageByHash(int uniqueRenderID, int imageNameHash, float xPos, float yPos,
                             float width, float height, bool updateExisting = false) -> void;

        /**
         *  Draws an image by texture ID.
         *
         *  @param uniqueRenderID The unique render ID.
         *  @param textureID The texture ID.
         *  @param xPos The x coordinate of the image.
         *  @param yPos The y coordinate of the image.
         *  @param width The width of the image.
         *  @param height The height of the image.
         *  @param updateExisting Whether to update the existing operation.
         */
        auto drawImageByTextureID(int uniqueRenderID, GLuint textureID, float xPos, float yPos,
                                  float width, float height, bool updateExisting = false) -> void;

        /**
         *  Draws an image by name with automatic height, meaning the height is calculated based
         *  on the width and the aspect ratio of the image.
         *
         *  @param uniqueRenderID The unique render ID.
         *  @param imageName The name of the image.
         *  @param xPos The x coordinate of the image.
         *  @param yPos The y coordinate of the image.
         *  @param width The width of the image.
         */
        auto drawImageAutoHeight(int uniqueRenderID, std::string_view imageName, float xPos,
                                 float yPos, float width) -> void;

      protected:
        /**
         *  Returns the vertex shader source.
         *
         *  @return The vertex shader source.
         */
        auto getVSSource() const -> std::string override;

        /**
         *  Returns the fragment shader source.
         *
         *  @return The fragment shader source.
         */
        auto getFSSource() const -> std::string override;

        /**
         *  Sets up the attribute layout.
         */
        auto setupAttributeLayout() const -> void override;

      private:
        auto cleanup() const -> void;

        auto setupState() const -> void;

        auto static restoreState() -> void;

        auto drawingOperationIsCached(int uniqueRenderID) const -> bool;

        std::unordered_map<int, Image2DRenderingOperation> m_operationsCache{};
    };
}
