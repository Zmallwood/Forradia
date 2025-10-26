//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    namespace Theme0
    {
        class WorldArea;

        class World
        {
          public:
            void Initialize(Size w_area_sz,
                            float world_scaling);

            auto GetCurrentWorldArea() const
            {
                return m_currentWorldArea;
            }

          private:
            SharedPtr<WorldArea> m_currentWorldArea;
        };
    }
}