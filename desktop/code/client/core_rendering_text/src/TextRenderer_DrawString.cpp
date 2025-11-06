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
    void TextRenderer::DrawString(StringView text, float x,
                                  float y,
                                  FontSizes fontSize,
                                  bool centerAlign,
                                  Color textColor) const
    {
        if (text.empty())
        {
            return;
        }

        auto fontRaw{m_fonts.at(fontSize).get()};

        Size textureDimensions;

        TTF_SizeText(fontRaw, text.data(),
                     &textureDimensions.width,
                     &textureDimensions.height);

        auto textHash{Hash(text)};

        auto xx{CFloat(CInt(x * 1000))};

        auto yy{CFloat(CInt(y * 1000))};

        auto textureAlreadyExists{
            _<TextureBank>().TextTextureExists(xx, yy,
                                               textHash)};

        auto textureID{_<TextureBank>().ObtainTextTexture(
            xx, yy, textHash)};

        this->SetupState();

        glBindTexture(GL_TEXTURE_2D, textureID);

        if (!textureAlreadyExists)
        {
            auto sdlColor{textColor.ToSDLColor()};

            auto surface{SharedPtr<SDL_Surface>(
                TTF_RenderText_Solid(fontRaw, text.data(),
                                     sdlColor),
                SDLDeleter())};

            this->DefineTexture(surface);
        }

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        auto width{CFloat(textureDimensions.width) /
                   canvasSize.width};

        auto height{CFloat(textureDimensions.height) /
                    canvasSize.height};

        if (centerAlign)
        {
            x -= width / 2;

            y -= height / 2;
        }

        auto uniqueRenderID{Hash(text.data() +
                                 std::to_string(x) +
                                 std::to_string(y))};

        _<Image2DRenderer>().DrawImageByTextureID(
            uniqueRenderID, textureID, x, y, width, height,
            true);

        this->RestoreState();
    }
}