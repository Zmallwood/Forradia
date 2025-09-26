#include "TextRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    TextRenderer::TextRenderer()
    {
        TTF_Init();

        AddFontSize(FontSizes::_20);
        AddFontSize(FontSizes::_26);
    }

    void TextRenderer::AddFontSize(FontSizes fontSize)
    {
        auto fontSizeN{static_cast<int>(fontSize)};

        auto fontPath{
            std::string(SDL_GetBasePath()) + k_defaultFontPath};

        auto fontPathUnixStyle{
            Replace(fontPath, '\\', '/')};

        auto newFont{
            std::shared_ptr<TTF_Font>(
                TTF_OpenFont(
                    fontPathUnixStyle.c_str(),
                    fontSizeN),
                SDLDeleter())};

        if (!newFont)
        {
            std::cout << "Error loading font.\n";

            return;
        }

        m_fonts.insert({fontSize, newFont});
    }

    void TextRenderer::DrawString(std::string_view text,
                                  float x,
                                  float y,
                                  FontSizes fontSize,
                                  bool centerAlign,
                                  Color textColor) const
    {
        auto font{m_fonts.at(fontSize).get()};

        auto renderer{
            _<SDLDevice>().GetRenderer().get()};

        auto sdlColor{textColor.ToSDLColor()};

        auto surface{
            TTF_RenderText_Solid(
                font,
                text.data(),
                sdlColor)};

        int textWidth;
        int textHeight;

        TTF_SizeText(
            font,
            text.data(),
            &textWidth,
            &textHeight);

        auto texture{
            SDL_CreateTextureFromSurface(renderer, surface)};

        auto canvasSize{GetCanvasSize()};

        SDL_Rect rect;

        rect.x = static_cast<int>(x * canvasSize.width);
        rect.y = static_cast<int>(y * canvasSize.height);

        rect.w = textWidth;
        rect.h = textHeight;

        if (centerAlign)
        {
            rect.x -= rect.w / 2;
            rect.y -= rect.h / 2;
        }

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}