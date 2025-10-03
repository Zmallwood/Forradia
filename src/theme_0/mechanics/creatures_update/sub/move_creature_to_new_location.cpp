/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "move_creature_to_new_location.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void move_creature_to_new_location(s_ptr<creature> crea, point new_pos) {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto old_pos{creas.at(crea)};
    auto now{get_ticks()};
    crea->set_ticks_last_move(now);
    auto old_tile{w_area->get_tile(old_pos.x, old_pos.y)};
    auto new_tile{w_area->get_tile(new_pos.x, new_pos.y)};
    old_tile->set_creature(nullptr);
    new_tile->set_creature(crea);
    creas.erase(crea);
    creas.insert({crea, {new_pos.x, new_pos.y}});
  }
}