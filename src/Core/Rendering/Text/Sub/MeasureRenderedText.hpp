/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    Size MeasureRenderedText(std::string_view text,
                     TTF_Font *fontRaw);
}