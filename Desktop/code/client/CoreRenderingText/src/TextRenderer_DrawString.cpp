/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "TextRenderer.hpp"
#include "Textures/TextureBank.hpp"

namespace Forradia {
    auto TextRenderer::DrawString(int uniqueRenderID, std::string_view text, float x, float y,
                                  FontSizes fontSize, bool centerAlign, bool forceRerender,
                                  Color textColor) const -> void {
        if (text.empty())
            return;

        auto fontRaw{m_fonts.at(fontSize).get()};

        Size textureDimensions;
        TTF_SizeText(fontRaw, text.data(), &textureDimensions.width, &textureDimensions.height);

        auto uniqueTextureID{uniqueRenderID};

        GLuint textureID;
        auto textureAlreadyExists{
            Singleton<TextureBank>().ObtainTextTexture(uniqueTextureID, textureID)};

        this->SetupState();

        glBindTexture(GL_TEXTURE_2D, textureID);

        // If the texture doesn't exist yet, create it from the text surface.
        if (!textureAlreadyExists || forceRerender) {
            auto sdlColor{textColor.ToSDLColor()};

            // Render the text to an SDL surface using the font and color.
            auto surface{std::shared_ptr<SDL_Surface>(
                TTF_RenderText_Solid(fontRaw, text.data(), sdlColor), SDLDeleter())};

            if (nullptr == surface) {
                PrintLine(std::string("Error rendering text: ") + text.data());
                return;
            }

            // Upload the surface data to the OpenGL texture.
            this->DefineTexture(surface);
        }

        auto canvasSize{GetCanvasSize(Singleton<SDLDevice>().GetWindow())};

        auto width{static_cast<float>(textureDimensions.width) / canvasSize.width};
        auto height{static_cast<float>(textureDimensions.height) / canvasSize.height};

        if (centerAlign) {
            x -= width / 2;
            y -= height / 2;
        }

        Singleton<Image2DRenderer>().DrawImageByTextureID(uniqueRenderID, textureID, x, y, width,
                                                          height, true);

        this->RestoreState();
    }
}
