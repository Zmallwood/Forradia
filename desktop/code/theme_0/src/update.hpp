/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_1_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_1_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_2_                                      \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_2_
void update_kb_actions();

void update_mouse_actions();

void update_kb_movem();

void update_mouse_movem();

void update_crea_movem();

void update_npcs();

class tl_hovering
{
  public:
    void update();

    auto hovered_coord() const
    {
        return hovered_coord_;
    }

  private:
    Point hovered_coord_{-1, -1};
};
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_
_NS_END_