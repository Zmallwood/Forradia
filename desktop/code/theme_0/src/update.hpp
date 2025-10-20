/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
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

    auto hovered_coord() const { return hovered_coord_; }

  private:
    pt hovered_coord_{-1, -1};
};
_NS_END_