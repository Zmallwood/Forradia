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

namespace AAK
{
    namespace Forradia
    {
        // Convenience aliases.

        using String = std::string;

        using StringView = std::string_view;

        template <class T>
        using SharedPtr = std::shared_ptr<T>;

        template <class T>
        using Vector = std::vector<T>;

        template <class T>
        using Function = std::function<T>;
    }
}