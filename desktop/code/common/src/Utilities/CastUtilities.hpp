//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Cast a value to int.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    ///
    constexpr int CInt(auto value)
    {
        return static_cast<int>(value);
    }

    ///
    /// Cast a value to float.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    ///
    float CFloat(auto value)
    {
        return static_cast<float>(value);
    }

    ///
    /// Cast a value to Uint8.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    ///
    Uint8 CUint8(auto value)
    {
        return static_cast<Uint8>(value);
    }
}