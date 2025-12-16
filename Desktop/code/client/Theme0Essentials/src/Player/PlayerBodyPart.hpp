//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia ::Theme0 {
///
/// Represents a body part of the player.
/// TODO: Decide if should be used also for other entities.
///
class PlayerBodyPart {
 public:
  ///
  /// Gets the strength of the body part.
  ///
  /// @return The strength of the body part.
  ///
  auto GetStrength() const {
    return m_strength;
  }

  ///
  /// Gets the current energy of the body part.
  ///
  /// @return The current energy of the body part.
  ///
  auto GetCurrentEnergy() const {
    return m_currentEnergy;
  }

  ///
  /// Gets the max energy of the body part.
  ///
  /// @return The max energy of the body part.
  ///
  auto GetMaxEnergy() const {
    return m_maxEnergy;
  }

  ///
  /// Gets the temperature of the body part.
  ///
  /// @return The temperature of the body part.
  ///
  auto GetTemperature() const {
    return m_temperature;
  }

 private:
  float m_strength{0.1f};      ///< The strength of the body part.
  float m_currentEnergy{1.0f}; ///< The current energy of the body part.
  float m_maxEnergy{1.0f};     ///< The max energy of the body part.
  float m_temperature{37.0f};  ///< The temperature of the body part.
};
}