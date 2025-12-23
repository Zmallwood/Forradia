/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Point.hpp"
#include "PlayerActions/PlayerActionTypes.hpp"
#include "PlayerMoveDirections.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Forradia::Theme0
{
    class PlayerObjectsInventory;
    class Spouse;

    /**
     * Represents the player character.
     */
    class Player
    {
      public:
        static Player &Instance()
        {
            static Player instance;
            return instance;
        }

        // Delete copy/move
        Player(const Player &) = delete;

        Player &operator=(const Player &) = delete;

        /**
         * Constructor.
         */
        Player()
        {
            // Initialize the player character.
            this->Initialize();
        }

        auto Update() -> void;

        auto StartMovingNorth() -> void;

        auto StartMovingEast() -> void;

        auto StartMovingSouth() -> void;

        auto StartMovingWest() -> void;

        auto StopMoving() -> void;

        /**
         * Moves the player north.
         */
        auto MoveNorth() -> void;

        /**
         * Moves the player east.
         */
        auto MoveEast() -> void;

        /**
         * Moves the player south.
         */
        auto MoveSouth() -> void;

        /**
         * Moves the player west.
         */
        auto MoveWest() -> void;

        /**
         * Adds experience to the player.
         *
         * @param experience The experience to add.
         */
        auto AddExperience(int experience) -> void;

        /**
         * Adds a player action to the player.
         *
         * @param playerAction The type of the player action.
         * @param actionFirstArgument The first argument of the player action.
         * @param actionSecondArgument The second argument of the player action.
         */
        auto AddPlayerAction(PlayerActionTypes playerAction,
                             std::string_view actionFirstArgument = "",
                             Point actionSecondArgument = {-1, -1}) -> void;

        /**
         * Gets the name of the player.
         *
         * @return The name of the player.
         */
        auto GetName() const
        {
            return m_name;
        }

        /**
         * Sets the position of the player.
         *
         * @param value The value to set.
         */
        auto SetPosition(Point value) -> void
        {
            m_position = value;
        }

        /**
         * Gets the position of the player.
         *
         * @return The position of the player.
         */
        auto GetPosition() const
        {
            return m_position;
        }

        /**
         * Gets the movement speed of the player.
         *
         * @return The movement speed of the player.
         */
        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        /**
         * Gets the ticks since last movement.
         *
         * @return The ticks since last movement.
         */
        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        /**
         * Sets the ticks since last movement.
         *
         * @param value The value to set.
         */
        auto SetTicksLastMovement(int value) -> void
        {
            m_ticksLastMovement = value;
        }

        /**
         * Gets the destination of the player.
         *
         * @return The destination of the player.
         */
        auto GetDestination() const
        {
            return m_destination;
        }

        /**
         * Sets the destination of the player.
         *
         * @param value The value to set.
         */
        auto SetDestination(Point value) -> void
        {
            m_destination = value;
        }

        /**
         * Gets the objects inventory of the player.
         *
         * @return The objects inventory of the player.
         */
        auto GetObjectsInventoryRef() const -> PlayerObjectsInventory &
        {
            return *m_playerObjectsInventory;
        }

        /**
         * Gets the experience of the player.
         *
         * @return The experience of the player.
         */
        auto GetExperience() const
        {
            return m_experience;
        }

        /**
         * Gets the well being of the player.
         *
         * @return The well being of the player.
         */
        auto GetWellBeing() const
        {
            return m_wellBeing;
        }

        /**
         * Gets the max well being of the player.
         *
         * @return The max well being of the player.
         */
        auto GetMaxWellBeing() const
        {
            return m_maxWellBeing;
        }

        /**
         * Gets the player actions of the player.
         *
         * @return The player actions of the player.
         */
        auto GetPlayerActionsRef() const
            -> const std::vector<std::tuple<PlayerActionTypes, std::string, Point>> &
        {
            return m_playerActions;
        }

        /**
         * Gets the quest completion points of the player.
         *
         * @return The quest completion points of the player.
         */
        auto GetQuestCompletionPointsRef() -> std::unordered_map<std::string, int> &
        {
            return m_questCompletionPoints;
        }

        /**
         * Gets the spouse of the player.
         *
         * @return The spouse of the player.
         */
        auto GetSpouse() const
        {
            return m_spouse;
        }

        void SetSpouse(std::shared_ptr<Spouse> value)
        {
            m_spouse = value;
        }

      private:
        auto Initialize() -> void;

        auto MoveToSuitablePosition() -> void;

        std::string m_name{"Unnamed Player"};
        Point m_position{60, 50};
        float m_movementSpeed{5.0F};
        int m_ticksLastMovement{0};
        Point m_destination{-1, -1};
        std::shared_ptr<PlayerObjectsInventory> m_playerObjectsInventory{};
        int m_experience{0};
        float m_wellBeing{10.0F};
        float m_maxWellBeing{10.0F};
        std::vector<std::tuple<PlayerActionTypes, std::string, Point>> m_playerActions{};
        std::unordered_map<std::string, int> m_questCompletionPoints{};
        PlayerMoveDirections m_playerMoveDirection{PlayerMoveDirections::None};
        std::shared_ptr<Spouse> m_spouse{};
    };
}
