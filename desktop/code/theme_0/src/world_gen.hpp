/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_                     \
    namespace Theme0                                                           \
    {                                                                          \
        namespace WorldStructure                                               \
        {                                                                      \
            class WorldArea;                                                   \
        }                                                                      \
    }
_HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_
namespace WorldGeneration
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
        void GenerateSingleLake(int minX, int minY, int maxX, int maxY,
                                int recursion) const;
        void GenerateElevation() const;
        void GenerateRock() const;
        void GenerateRivers() const;
        void GenerateObjects() const;
        void GenerateCreatures() const;
        void GenerateNPCs() const;

        SharedPtr<Theme0::WorldStructure::WorldArea> m_worldArea;
        float m_scale;
        Size m_size;
    };
}
using namespace WorldGeneration;
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_
_NS_END_