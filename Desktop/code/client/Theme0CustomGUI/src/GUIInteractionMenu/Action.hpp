/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  /**
   * Represents an action that can be performed by the player.
   */
  class Action {
   public:
    /**
     * The types of ground that the action can be performed on.
     */
    std::vector<int> groundMatches;

    /**
     * The types of objects that the action can be performed on.
     */
    std::vector<int> objectMatches;

    /**
     * The function that performs the action.
     */
    std::function<void()> action;
  };
}
