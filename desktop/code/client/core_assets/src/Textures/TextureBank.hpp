//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "TextureEntry.hpp"

struct SDL_Surface;

namespace Forradia
{
    ///
    /// Manages loading and providing of textures
    /// which are being used in opengl rendering.
    ///
    class TextureBank
    {
      public:
        ///
        /// Constructor.
        ///
        TextureBank()
        {
            Initialize();
        }

        ///
        /// Destructor.
        ///
        ~TextureBank()
        {
            Cleanup();
        }

        ///
        /// Get a texture ID for the given image name hash.
        ///
        /// @param imageNameHash The hash of the image name.
        /// @return The texture ID.
        ///
        GLuint GetTexture(int imageNameHash) const;

        ///
        /// Gets the dimensions of a texture with the
        /// given hash.
        ///
        /// @param imageNameHash The hash of the image name.
        /// @return The dimensions of the texture.
        ///
        Size GetTextureDimensions(int imageNameHash) const;

        ///
        /// Obtains a text texture ID for the given unique
        /// texture ID.
        ///
        /// @param uniqueTextureID The unique texture ID.
        /// @param[out] textureID The texture ID (output
        /// parameter).
        /// @return True if the texture was found, false
        /// otherwise.
        ///
        bool ObtainTextTexture(int uniqueTextureID,
                               GLuint &textureID);

      private:
        ///
        /// Initializes the texture bank.
        ///
        void Initialize();

        ///
        /// Cleans up the texture bank.
        ///
        void Cleanup();

        ///
        /// Loads textures from the image resource
        /// directory.
        ///
        void LoadTextures();

        ///
        /// Obtains a texture ID for a single loaded
        /// texture.
        ///
        /// @param surface The SDL surface to create the
        /// texture from.
        /// @return The texture ID.
        ///
        GLuint
        LoadSingleTexture(SharedPtr<SDL_Surface> surface);

        inline static const String k_relativeImagesPath{
            "./Resources/Images/"}; ///< The relative path
                                    ///< to the image
                                    ///< resource directory.

        std::map<int, TextureEntry>
            m_textureEntries; ///< The texture entries,
                              ///< stored by image name
                              ///< hash.

        std::map<int, GLuint>
            m_textTextureIDs; ///< The text texture IDs,
                              ///< stored by x, y and
                              ///< text hash values.
    };
}