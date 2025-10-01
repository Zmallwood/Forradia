/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_mouse_movement.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/tile_hovering.hpp"

namespace forr {
  void UpdateMouseMovement() {
    if (GetSingleton<mouse_input>()
            .GetLeftMouseButtonRef()
            .GetHasBeenFiredPickResult()) {
      auto newDestination{GetSingleton<tile_hovering>().GetHoveredCoordinate()};
      GetSingleton<player>().SetDestination(newDestination);
    }
    auto playerPosition{GetSingleton<player>().GetPosition()};
    auto destination{GetSingleton<player>().GetDestination()};
    if (destination == point{-1, -1}) {
      return;
    }
    auto now{GetTicks()};
    if (now >=
        GetSingleton<player>().GetTicksLastMove() +
            InvertMovementSpeed(GetSingleton<player>().GetMovementSpeed())) {
      auto dx{destination.x - playerPosition.x};
      auto dy{destination.y - playerPosition.y};
      if (dx < 0) {
        GetSingleton<player>().MoveWest();
      }
      if (dy < 0) {
        GetSingleton<player>().MoveNorth();
      }
      if (dx > 0) {
        GetSingleton<player>().MoveEast();
      }
      if (dy > 0) {
        GetSingleton<player>().MoveSouth();
      }
      if (destination == playerPosition) {
        GetSingleton<player>().SetDestination({-1, -1});
      }
      GetSingleton<player>().SetTicksLastMove(now);
    }
  }
}