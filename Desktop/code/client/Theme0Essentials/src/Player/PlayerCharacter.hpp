//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "PlayerBody.hpp"

#include "PlayerModes.hpp"

namespace Forradia::Theme0::GameplayCore
{
    class PlayerObjectsInventory;

    ///
    /// Represents the player character.
    ///
    class PlayerCharacter
    {
      public:
        ///
        /// Constructor.
        ///
        PlayerCharacter()
        {
            // Initialize the player character.

            this->Initialize();
        }

        ///
        /// Moves the player north.
        ///
        void MoveNorth();

        ///
        /// Moves the player east.
        ///
        void MoveEast();

        ///
        /// Moves the player south.
        ///
        void MoveSouth();

        ///
        /// Moves the player west.
        ///
        void MoveWest();

        void AddExperience(int experience);

        ///
        /// Gets the name of the player.
        ///
        /// @return The name of the player.
        ///
        auto GetName() const
        {
            return m_name;
        }

        ///
        /// Gets the position of the player.
        ///
        /// @return The position of the player.
        ///
        auto GetPosition() const
        {
            return m_position;
        }

        ///
        /// Gets the movement speed of the player.
        ///
        /// @return The movement speed of the player.
        ///
        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        ///
        /// Gets the ticks since last movement.
        ///
        /// @return The ticks since last movement.
        ///
        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        ///
        /// Sets the ticks since last movement.
        ///
        /// @param value The value to set.
        ///
        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        ///
        /// Gets the destination of the player.
        ///
        /// @return The destination of the player.
        ///
        auto GetDestination() const
        {
            return m_destination;
        }

        ///
        /// Sets the destination of the player.
        ///
        /// @param value The value to set.
        ///
        void SetDestination(Point value)
        {
            m_destination = value;
        }

        ///
        /// Gets the body of the player.
        ///
        /// @return The body of the player.
        ///
        auto &GetBodyRef()
        {
            return m_playerBody;
        }

        ///
        /// Gets the objects inventory of the player.
        ///
        /// @return The objects inventory of the player.
        ///
        auto &GetObjectsInventoryRef() const
        {
            return *m_playerObjectsInventory;
        }

        ///
        /// Gets the experience of the player.
        ///
        /// @return The experience of the player.
        ///
        auto GetExperience() const
        {
            return m_experience;
        }

        auto GetPlayerMode() const
        {
            return m_playerMode;
        }

        void SetPlayerMode(PlayerModes playerMode)
        {
            m_playerMode = playerMode;
        }

      private:
        ///
        /// Initializes the player character.
        ///
        void Initialize();

        ///
        /// Moves the player to a suitable position.
        ///
        void MoveToSuitablePosition();

        String m_name{"Unnamed Player"}; ///< The name of the player.

        Point m_position{60, 50}; ///< The position of the player.

        float m_movementSpeed{5.0f}; ///< The movement speed of the player.

        int m_ticksLastMovement{0}; ///< The ticks since last movement.

        Point m_destination{-1, -1}; ///< The movement destination of the player.

        PlayerBody m_playerBody; ///< The body of the player.

        SharedPtr<PlayerObjectsInventory>
            m_playerObjectsInventory; ///< The objects inventory of the player.

        int m_experience{0}; ///< The experience of the player.

        PlayerModes m_playerMode{PlayerModes::Interaction}; ///< The mode of the player.
    };
}