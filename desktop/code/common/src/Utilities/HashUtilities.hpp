//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Aliases.hpp"

namespace Forradia
{
    ///
    /// Compute hash code from a given input text, which
    /// gets computed the same every game start.
    ///
    /// @param text Text to compute hash code for.
    /// @return Computed hash code.
    ///
    int Hash(StringView text);
}