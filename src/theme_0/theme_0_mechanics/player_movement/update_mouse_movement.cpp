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
    if (GetSingleton<MouseInput>()
            .GetLeftMouseButtonRef()
            .GetHasBeenFiredPickResult()) {
      auto newDestination{GetSingleton<TileHovering>().GetHoveredCoordinate()};
      GetSingleton<Player>().SetDestination(newDestination);
    }
    auto playerPosition{GetSingleton<Player>().GetPosition()};
    auto destination{GetSingleton<Player>().GetDestination()};
    if (destination == Point{-1, -1}) {
      return;
    }
    auto now{GetTicks()};
    if (now >=
        GetSingleton<Player>().GetTicksLastMove() +
            InvertMovementSpeed(GetSingleton<Player>().GetMovementSpeed())) {
      auto dx{destination.x - playerPosition.x};
      auto dy{destination.y - playerPosition.y};
      if (dx < 0) {
        GetSingleton<Player>().MoveWest();
      }
      if (dy < 0) {
        GetSingleton<Player>().MoveNorth();
      }
      if (dx > 0) {
        GetSingleton<Player>().MoveEast();
      }
      if (dy > 0) {
        GetSingleton<Player>().MoveSouth();
      }
      if (destination == playerPosition) {
        GetSingleton<Player>().SetDestination({-1, -1});
      }
      GetSingleton<Player>().SetTicksLastMove(now);
    }
  }
}