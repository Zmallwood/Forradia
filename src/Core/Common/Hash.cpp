/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Hash.hpp"

namespace Forradia
{
    int Hash(StringView text)
    {
        unsigned long hash{5381};

        for (size_t i = 0; i < text.size(); ++i)
        {
            hash = 33 * hash + (unsigned char)text[i];
        }

        return CInt(hash);
    }
}
