/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "DrawImage.hpp"
#include "Core/ImageAssets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia {
  void DrawImage(int imageNameHash, float x, float y, float width,
                 float height) {
    auto image{_<ImageBank>().GetImage(imageNameHash)};

    auto canvasSize{GetCanvasSize()};

    auto xPx{CInt(x * canvasSize.width)};

    auto yPx{CInt(y * canvasSize.height)};

    auto widthPx{CInt(width * canvasSize.width)};

    auto heightPx{CInt(height * canvasSize.height)};

    SDL_Rect sdlRectangle{xPx, yPx, widthPx, heightPx};

    SDL_RenderCopy(_<SDLDevice>().GetRenderer().get(), image.get(), nullptr,
                   &sdlRectangle);
  }
}