//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Theme0Properties
    {
      public:
        String GetGameWindowTitle() const;

        Color GetClearColor() const;

        Size GetGridSize() const;

        Size GetWorldAreaSize() const;

        float GetWorldScaling() const;

        float GetTileSize() const;
    };
}