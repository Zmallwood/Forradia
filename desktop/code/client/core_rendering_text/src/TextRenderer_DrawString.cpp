//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextRenderer.hpp"

#include "SDLDevice.hpp"

#include "Textures/TextureBank.hpp"

#include "Image2DRenderer.hpp"

namespace Forradia
{
    void TextRenderer::DrawString(
        int uniqueRenderID, StringView text, float x,
        float y, FontSizes fontSize, bool centerAlign,
        bool forceRerender, Color textColor) const
    {
        // Early return if the text string is empty.

        if (text.empty())
        {
            return;
        }

        // Get the raw TTF font pointer for the specified
        // font size.

        auto fontRaw{m_fonts.at(fontSize).get()};

        // Calculate the dimensions of the text using
        // SDL_ttf.

        Size textureDimensions;

        TTF_SizeText(fontRaw, text.data(),
                     &textureDimensions.width,
                     &textureDimensions.height);

        // Use the unique render ID as the texture ID.

        auto uniqueTextureID{uniqueRenderID};

        // Obtain or create the texture for this text from
        // the texture bank.

        GLuint textureID;

        auto textureAlreadyExists{
            _<TextureBank>().ObtainTextTexture(
                uniqueTextureID, textureID)};

        // Set up OpenGL state for text rendering.

        this->SetupState();

        // Bind the texture for rendering.

        glBindTexture(GL_TEXTURE_2D, textureID);

        // If the texture doesn't exist yet, create it from
        // the text surface.

        if (!textureAlreadyExists || forceRerender)
        {
            // Convert the text color to SDL color format.

            auto sdlColor{textColor.ToSDLColor()};

            // Render the text to an SDL surface using the
            // font and color.

            auto surface{SharedPtr<SDL_Surface>(
                TTF_RenderText_Solid(fontRaw, text.data(),
                                     sdlColor),
                SDLDeleter())};

            // If the surface is null, print an error
            // message and return.

            if (nullptr == surface)
            {
                PrintLine(String("Error rendering text: ") +
                          text.data());

                return;
            }

            // Upload the surface data to the OpenGL
            // texture.

            this->DefineTexture(surface);
        }

        // Get the canvas size to normalize texture
        // dimensions.

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        // Convert texture dimensions to normalized
        // coordinates (0-1 range)
        auto width{CFloat(textureDimensions.width) /
                   canvasSize.width};

        auto height{CFloat(textureDimensions.height) /
                    canvasSize.height};

        // Adjust position for center alignment if
        // requested.

        if (centerAlign)
        {
            x -= width / 2;

            y -= height / 2;
        }

        // Draw the text image using the 2D image renderer.

        _<Image2DRenderer>().DrawImageByTextureID(
            uniqueRenderID, textureID, x, y, width, height,
            true);

        // Restore the previous OpenGL state.

        this->RestoreState();
    }
}