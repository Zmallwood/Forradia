/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "PlayerBodyPartTypes.hpp"

namespace Forradia::Theme0 {
class PlayerBodyPart;

/**
 * Represents the body of the player.
 */
class PlayerBody {
 public:
  /**
   * Constructor.
   */
  PlayerBody() {
    this->Initialize();
  }

  /**
   * Gets a pointer to the body part.
   *
   * @param bodyPartType The type of the body part.
   * @return A pointer to the body part.
   */
  SharedPtr<PlayerBodyPart> GetBodyPartPtr(PlayerBodyPartTypes bodyPartType);

 private:
  void Initialize();

  std::map<PlayerBodyPartTypes, SharedPtr<PlayerBodyPart>> m_bodyParts;
};
}