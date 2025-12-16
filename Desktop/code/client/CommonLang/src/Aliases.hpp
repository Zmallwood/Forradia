//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Forradia {
    // Convenience text aliases.
    using String = std::string;
    using StringView = std::string_view;

    // Convenience smart pointer aliases.
    template <class T>
    using SharedPtr = std::shared_ptr<T>;

    // Convenience data structure aliases.
    template <class T>
    using Vector = std::vector<T>;

    // Convenience function aliases.
    template <class T>
    using Function = std::function<T>;
}