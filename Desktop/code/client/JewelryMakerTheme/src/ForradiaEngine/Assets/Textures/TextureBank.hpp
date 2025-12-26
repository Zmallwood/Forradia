/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include "TextureEntry.hpp"
    #include <GL/gl.h>
    #include <memory>
    #include <unordered_map>
// clang-format on

struct SDL_Surface;

namespace ForradiaEngine
{
    /**
     *  Manages loading and providing of textures which are being used in opengl rendering.
     */
    class TextureBank
    {
      public:
        static auto instance() -> TextureBank &
        {
            static TextureBank instance;
            return instance;
        }

        TextureBank(const TextureBank &) = delete;

        auto operator=(const TextureBank &) -> TextureBank & = delete;

        /**
         *  Constructor.
         */
        TextureBank()
        {
            TextureBank::initialize();
        }

        /**
         *  Destructor.
         */
        ~TextureBank()
        {
            TextureBank::cleanup();
        }

        /**
         *  Get a texture ID for the given image name hash.
         *
         *  @param imageNameHash The hash of the image name.
         *  @return The texture ID.
         */
        [[nodiscard]] auto getTexture(int imageNameHash) const -> GLuint;

        /**
         *  Gets the dimensions of a texture with the given hash.
         *
         *  @param imageNameHash The hash of the image name.
         *  @return The dimensions of the texture.
         */
        [[nodiscard]] static auto getTextureDimensions(int imageNameHash) -> Size;

        /**
         *  Obtains a text texture ID for the given unique texture ID.
         *
         *  @param uniqueTextureID The unique texture ID.
         *  @param[out] textureID The texture ID (output parameter).
         *  @return True if the texture was found, false otherwise.
         */
        auto obtainTextTexture(int uniqueTextureID, GLuint &textureID) const -> bool;

      private:
        static auto initialize() -> void;

        static auto cleanup() -> void;

        static auto loadTextures() -> void;

        [[nodiscard]] static auto loadSingleTexture(const std::shared_ptr<SDL_Surface> &surface)
            -> GLuint;

        inline static const std::string k_relativeImagesPath{"./Resources/Images/"};
        inline static std::unordered_map<int, TextureEntry> m_textureEntries{};
        inline static std::unordered_map<int, GLuint> m_textTextureIDs{};
    };
}
