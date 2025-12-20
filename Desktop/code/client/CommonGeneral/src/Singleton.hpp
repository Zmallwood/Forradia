/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

namespace Forradia {
    /**
     * Returns a singleton of an object of type T, in the form of a SharedPtr.
     *
     * @tparam T Type to get singleton for.
     * @return The singleton object as a SharedPtr.
     */
    template <class T>
    auto __() -> std::shared_ptr<T> {
        static std::shared_ptr<T> instance{std::make_shared<T>()};
        return instance;
    }

    /**
     * Returns a singleton of an object of type T, in the form of a reference.
     *
     * @tparam T Type to get singleton for.
     * @return The singleton object as a reference.
     */
    template <class T>
    auto _() -> T & {
        return *__<T>();
    }
}
