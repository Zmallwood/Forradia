/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Object
    {
    public:
        Object(std::string_view objectTypeName);

        auto GetType() const
        {
            return m_type;
        }

    private:
        int m_type{0};
    };
}