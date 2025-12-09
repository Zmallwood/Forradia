//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

#include "Image2DRenderingOperation.hpp"
#include "RendererBase.hpp"

namespace Forradia
{
    /// A renderer for drawing images to the canvas.
    class Image2DRenderer : public RendererBase
    {
      public:
        /// Destructor which cleans up the renderer.
        ~Image2DRenderer()
        {
            // Clean up the renderer.
            this->Cleanup();
        }

        /// Draws an image by name.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @param imageName The name of the image.
        /// @param x The x coordinate of the image.
        /// @param y The y coordinate of the image.
        /// @param width The width of the image.
        void DrawImageByName(int uniqueRenderID, StringView imageName, float x, float y,
                             float width, float height, bool updateExisting = false);

        /// Draws an image by hash.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @param imageNameHash The hash of the image name.
        /// @param x The x coordinate of the image.
        /// @param y The y coordinate of the image.
        /// @param width The width of the image.
        void DrawImageByHash(int uniqueRenderID, int imageNameHash, float x, float y, float width,
                             float height, bool updateExisting = false);

        /// Draws an image by texture ID.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @param textureID The texture ID.
        /// @param x The x coordinate of the image.
        /// @param y The y coordinate of the image.
        /// @param width The width of the image.
        void DrawImageByTextureID(int uniqueRenderID, GLuint textureID, float x, float y,
                                  float width, float height, bool updateExisting = false);

        /// Draws an image by name with automatic height, meaning the height is calculated based
        /// on the width and the aspect ratio of the image.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @param imageName The name of the image.
        /// @param x The x coordinate of the image.
        /// @param y The y coordinate of the image.
        /// @param width The width of the image.
        void DrawImageAutoHeight(int uniqueRenderID, StringView imageName, float x, float y,
                                 float width);

      protected:
        /// Returns the vertex shader source.
        ///
        /// @return The vertex shader source.
        String GetVSSource() const override;

        /// Returns the fragment shader source.
        ///
        /// @return The fragment shader source.
        String GetFSSource() const override;

        /// Sets up the attribute layout.
        void SetupAttributeLayout() const override;

      private:
        /// Cleans up the renderer.
        void Cleanup();

        /// Sets up the state.
        void SetupState() const;

        /// Resets the state.
        void RestoreState() const;

        /// Checks if the drawing operation is cached.
        ///
        /// @param uniqueRenderID The unique render ID.
        /// @return True if the drawing operation is cached, false otherwise.
        bool DrawingOperationIsCached(int uniqueRenderID) const;

        std::map<int, Image2DRenderingOperation> m_operationsCache; ///< The operations cache.
    };
}