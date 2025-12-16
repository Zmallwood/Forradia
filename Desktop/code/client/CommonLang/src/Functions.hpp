//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

typedef uint8_t Uint8;

namespace Forradia {
    /// Can be used to cast any value to int.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    constexpr int CInt(auto value) {
        return static_cast<int>(value);
    }

    /// Can be used to cast any value to float.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    constexpr float CFloat(auto value) {
        return static_cast<float>(value);
    }

    /// Can be used to cast any value to Uint8.
    ///
    /// @param value Value to cast.
    /// @return Casted value.
    constexpr Uint8 CUint8(auto value) {
        return static_cast<Uint8>(value);
    }
}