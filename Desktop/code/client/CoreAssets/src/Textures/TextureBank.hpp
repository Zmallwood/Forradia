/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Size.hpp"
#include "TextureEntry.hpp"
#include <GL/gl.h>
#include <memory>
#include <unordered_map>

struct SDL_Surface;

namespace Forradia
{
    /**
     * Manages loading and providing of textures which are being used in opengl rendering.
     */
    class TextureBank
    {
      public:
        static auto Instance() -> TextureBank &
        {
            static TextureBank instance;
            return instance;
        }

        // Delete copy/move
        TextureBank(const TextureBank &) = delete;

        auto operator=(const TextureBank &) -> TextureBank & = delete;

        /**
         * Constructor.
         */
        TextureBank()
        {
            TextureBank::Initialize();
        }

        /**
         * Destructor.
         */
        ~TextureBank()
        {
            TextureBank::Cleanup();
        }

        /**
         * Get a texture ID for the given image name hash.
         *
         * @param imageNameHash The hash of the image name.
         * @return The texture ID.
         */
        [[nodiscard]] auto GetTexture(int imageNameHash) const -> GLuint;

        /**
         * Gets the dimensions of a texture with the given hash.
         *
         * @param imageNameHash The hash of the image name.
         * @return The dimensions of the texture.
         */
        [[nodiscard]] static auto GetTextureDimensions(int imageNameHash) -> Size;

        /**
         * Obtains a text texture ID for the given unique texture ID.
         *
         * @param uniqueTextureID The unique texture ID.
         * @param[out] textureID The texture ID (output parameter).
         * @return True if the texture was found, false otherwise.
         */
        auto ObtainTextTexture(int uniqueTextureID, GLuint &textureID) const -> bool;

      private:
        static auto Initialize() -> void;

        static auto Cleanup() -> void;

        static auto LoadTextures() -> void;

        [[nodiscard]] static auto LoadSingleTexture(const std::shared_ptr<SDL_Surface> &surface)
            -> GLuint;

        inline static const std::string k_relativeImagesPath{"./Resources/Images/"};
        inline static std::unordered_map<int, TextureEntry> m_textureEntries{};
        inline static std::unordered_map<int, GLuint> m_textTextureIDs{};
    };
}
