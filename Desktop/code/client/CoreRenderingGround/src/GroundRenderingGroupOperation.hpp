//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "TileDrawGroup.hpp"

namespace AAK
{
    namespace Forradia
    {
        class GroundRenderingGroupOperation
        {
          public:
            std::map<int, TileDrawGroup> tilesByTexture;
        };
    }
}