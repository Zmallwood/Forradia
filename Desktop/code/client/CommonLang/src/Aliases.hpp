//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include <functional>

#include <memory>

#include <string>

#include <vector>

namespace Forradia
{
    // Convenience aliases.

    // Text

    using String = std::string;

    using StringView = std::string_view;

    // Memory

    template <class T>
    using SharedPtr = std::shared_ptr<T>;

    // Data structures

    template <class T>
    using Vector = std::vector<T>;

    // Functions

    template <class T>
    using Function = std::function<T>;
}