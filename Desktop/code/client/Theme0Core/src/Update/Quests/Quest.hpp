/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  /**
   * A quest is a task that the player can complete to progress the game.
   */
  class Quest {
   public:
    /**
     * Updates the quest.
     */
    virtual auto Update() -> void = 0;

    /**
     * Gets the status of the quest.
     */
    virtual auto GetStatus() const -> std::string = 0;

    /**
     * The name of the quest.
     */
    std::string name;

    /**
     * The description of the quest.
     */
    std::string description;

    /**
     * Whether the quest is completed.
     */
    bool isCompleted{false};
  };
}
