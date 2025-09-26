/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    std::shared_ptr<SDL_Texture> LoadSingleImage(std::string_view path);
}