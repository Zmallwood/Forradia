//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    template <class T>
    T &_()
    {
        static T instance;
        return instance;
    }
}