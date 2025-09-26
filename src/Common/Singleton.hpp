#pragma once

namespace Forradia
{
    template <class T>
    T& _()
    {
        static T instance;

        return instance;
    }
}
