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
            class WorldArea;                                                  \
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
        void gen_new_world();

      private:
        void prep();
        void clear_with_dirt() const;
        void gen_grass() const;
        void gen_lakes() const;
        void gen_single_lake(int min_x, int min_y, int max_x, int max_y,
                             int recurs) const;
        void gen_elev() const;
        void gen_rock() const;
        void gen_rivers() const;
        void gen_objs() const;
        void gen_creas() const;
        void gen_npcs() const;

        SharedPtr<Theme0::WorldStructure::WorldArea> w_area_;
        float scale_;
        Size sz_;
    };
}
using namespace WorldGeneration;
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_
_NS_END_