//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Lang.hpp"

namespace Forradia
{
    ///
    /// Print out a string of text, without a following line
    /// break.
    ///
    /// @param text Text to print.
    ///
    void Print(StringView text);

    ///
    /// Print out a string of text, with an added line break
    /// at the end.
    ///
    /// @param text Text to print.
    ///
    void PrintLine(StringView text);
}