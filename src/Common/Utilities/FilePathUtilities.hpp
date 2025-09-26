/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    std::string GetFileExtension(std::string_view path);

    std::string GetFileNameNoExtension(std::string_view path);
}