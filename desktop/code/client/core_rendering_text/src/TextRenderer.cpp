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
    void TextRenderer::Initialize()
    {
        TTF_Init();

        this->AddFonts();
    }

    void TextRenderer::AddFonts()
    {
        auto absFontPath{String(SDL_GetBasePath()) +
                         k_defaultFontPath.data()};

        for (auto fontSize :
             {FontSizes::_20, FontSizes::_26})
        {
            auto fontPathUnixStyle{
                Replace(absFontPath, '\\', '/')};

            auto fontSizeN{CInt(fontSize)};

            auto newFont{SharedPtr<TTF_Font>(
                TTF_OpenFont(fontPathUnixStyle.c_str(),
                             fontSizeN),
                SDLDeleter())};

            if (!newFont)
            {
                PrintLine("Error loading font.");

                return;
            }

            m_fonts.insert({fontSize, newFont});
        }
    }

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

        SDL_Rect destination;

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        destination.x = CInt(x * canvasSize.width);

        destination.y = CInt(y * canvasSize.height);

        destination.w = textureDimensions.width;

        destination.h = textureDimensions.height;

        if (centerAlign)
        {
            destination.x -= destination.w / 2;

            destination.y -= destination.h / 2;
        }

        auto textHash{Hash(text)};

        auto xx{CFloat(CInt(x * 1000))};

        auto yy{CFloat(CInt(y * 1000))};

        auto textureAlreadyExists{
            _<TextureBank>().TextTextureExists(xx, yy,
                                               textHash)};

        auto texture{_<TextureBank>().ObtainTextTexture(
            xx, yy, textHash)};

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glEnable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, texture);

        if (!textureAlreadyExists)
        {
            auto sdlColor{textColor.ToSDLColor()};

            auto surface{TTF_RenderText_Solid(
                fontRaw, text.data(), sdlColor)};

            auto newWidth{surface->w};

            auto newHeight{surface->h};

            auto intermediary = SDL_CreateRGBSurface(
                0, newWidth, newHeight, 32, 0x000000ff,
                0x0000ff00, 0x00ff0000, 0xff000000);

            SDL_BlitSurface(surface, 0, intermediary, 0);

            glTexImage2D(GL_TEXTURE_2D, 0, 4,
                         intermediary->w, intermediary->h,
                         0, GL_RGBA, GL_UNSIGNED_BYTE,
                         intermediary->pixels);

            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MAG_FILTER,
                            GL_LINEAR);

            SDL_FreeSurface(intermediary);

            SDL_FreeSurface(surface);
        }

        auto xF{CFloat(destination.x) / canvasSize.width};

        auto yF{CFloat(destination.y) / canvasSize.height};

        auto widthF{CFloat(destination.w) /
                    canvasSize.width};

        auto heightF{CFloat(destination.h) /
                     canvasSize.height};

        _<Image2DRenderer>().DrawImageByTextureID(
            texture, xF, yF, widthF, heightF, false);

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}