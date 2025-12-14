//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:
// Consider adding something like m_mindState = "Normal"

#pragma once

#include "PlayerActions/PlayerActionTypes.hpp"
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

        void AddPlayerAction(PlayerActionTypes playerAction, StringView actionArgument = "");

        ///
        /// Gets the name of the player.
        ///
        /// @return The name of the player.
        ///
        auto GetName() const
        {
            return m_name;
        }

        void SetPosition(Point value)
        {
            m_position = value;
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

        auto GetWellBeing() const
        {
            return m_wellBeing;
        }

        auto GetMaxWellBeing() const
        {
            return m_maxWellBeing;
        }

        auto GetAttackSpeed() const
        {
            return m_attackSpeed;
        }

        auto GetTicksLastHitAnother() const
        {
            return m_ticksLastHitAnother;
        }

        void SetTicksLastHitAnother(int value)
        {
            m_ticksLastHitAnother = value;
        }

        auto &GetPlayerActionsRef() const
        {
            return m_playerActions;
        }

        auto &GetQuestCompletionPointsRef()
        {
            return m_questCompletionPoints;
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

        float m_wellBeing{10.0f}; ///< The well being of the player.

        float m_maxWellBeing{10.0f}; ///< The max well being of the player.

        float m_attackSpeed{3.0f}; ///< The attack speed of the player.

        int m_ticksLastHitAnother{0}; ///< The ticks since last hit another entity.

        Vector<std::pair<PlayerActionTypes, String>>
            m_playerActions; ///< The actions of the player.

        std::map<String, int>
            m_questCompletionPoints; ///< The quest completion points of the player.
    };
}