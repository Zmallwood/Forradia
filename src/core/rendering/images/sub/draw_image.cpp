/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "draw_image.hpp"
#include "core/image_assets/image_bank.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace Forradia {
  void DrawImage(int imageNameHash, float x, float y, float width,
                 float height) {
    auto image{GetSingleton<ImageBank>().GetImage(imageNameHash)};
    auto canvasSize{GetCanvasSize()};
    auto xPx{CInt(x * canvasSize.width)};
    auto yPx{CInt(y * canvasSize.height)};
    auto widthPx{CInt(width * canvasSize.width)};
    auto heightPx{CInt(height * canvasSize.height)};
    SDL_Rect sdlRectangle{xPx, yPx, widthPx, heightPx};
    SDL_RenderCopy(GetSingleton<SDLDevice>().GetRenderer().get(), image.get(),
                   nullptr, &sdlRectangle);
  }
}