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
    }

    namespace Theme0
    {
        class WorldGenerator
        {
          public:
            void GenerateNewWorld();

          private:
            void Prepare();

            void ClearWithDirt() const;

            void GenerateGrass() const;

            void GenerateLakes() const;

            void GenerateSingleLake(int minX, int minY,
                                    int maxX, int maxY,
                                    int recursion) const;

            void GenerateElevation() const;

            void GenerateRock() const;

            void GenerateRivers() const;

            void GenerateObjects() const;

            void GenerateCreatures() const;

            void GenerateNPCs() const;

            SharedPtr<Theme0::WorldArea> m_worldArea;

            float m_scale;

            Size m_size;
        };
    }
}