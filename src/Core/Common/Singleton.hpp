/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    template <class T>
    SharedPtr<T> __()
    {
        static SharedPtr<T> instance = std::make_shared<T>();

        return instance;
    }

    template <class T>
    T &_()
    {
        return *__<T>();
    }
}
