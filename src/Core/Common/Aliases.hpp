/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    using String = std::string;

    using StringView = std::string_view;

    template <class T>
    using SharedPtr = std::shared_ptr<T>;

    template <class T, class U>
    using Map = std::map<T, U>;

    template <class T>
    using Vector = std::vector<T>;
}