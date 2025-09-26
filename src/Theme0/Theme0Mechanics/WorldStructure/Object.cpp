/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Object.hpp"

namespace Forradia
{
    Object::Object(std::string_view objectTypeName)
        : m_type(Hash(objectTypeName))
    {
    }
}