/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    std::map<int, std::shared_ptr<SDL_Texture>> GetLoadedImages(std::string_view imagesPath);
}