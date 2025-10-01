/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  Map<int, SharedPtr<SDL_Texture>>
  GetLoadedImages(StringView relativeImagesPath);
}