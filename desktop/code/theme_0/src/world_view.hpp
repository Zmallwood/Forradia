/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_                                  \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_
class world_view
{
  public:
    void render() const;
};
}
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_
_NS_END_