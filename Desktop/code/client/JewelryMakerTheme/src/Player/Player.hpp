/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"
#include "PlayerActionTypes.hpp"
#include "PlayerMoveDirections.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class PlayerObjectsInventory;
    // TODO: Think about if this should be kept or not.
    // class Spouse;

    /**
     *  Represents the player character.
     */
    class Player
    {
      public:
        static auto instance() -> Player &
        {
            static Player instance;
            return instance;
        }

        Player(const Player &) = delete;

        auto operator=(const Player &) -> Player & = delete;

        Player() = default;

        /**
         *  Initializes the player.
         */
        auto initialize() -> void;

        /**
         *  Updates the player.
         */
        auto update() -> void;

        /**
         *  Starts moving the player north.
         */
        auto startMovingNorth() -> void;

        /**
         *  Starts moving the player east.
         */
        auto startMovingEast() -> void;

        /**
         *  Starts moving the player south.
         */
        auto startMovingSouth() -> void;

        /**
         *  Starts moving the player west.
         */
        auto startMovingWest() -> void;

        /**
         *  Starts moving the player north-west.
         */
        auto startMovingNorthWest() -> void;

        /**
         *  Starts moving the player north-east.
         */
        auto startMovingNorthEast() -> void;

        /**
         *  Starts moving the player south-west.
         */
        auto startMovingSouthWest() -> void;

        /**
         *  Starts moving the player south-east.
         */
        auto startMovingSouthEast() -> void;

        /**
         *  Stops the player from moving.
         */
        auto stopMoving() -> void;

        /**
         *  Moves the player north.
         */
        auto moveNorth() -> void;

        /**
         *  Moves the player east.
         */
        auto moveEast() -> void;

        /**
         *  Moves the player south.
         */
        auto moveSouth() -> void;

        /**
         *  Moves the player west.
         */
        auto moveWest() -> void;

        /**
         *  Moves the player north-east.
         */
        auto moveNorthEast() -> void;

        /**
         *  Moves the player south-east.
         */
        auto moveSouthEast() -> void;

        /**
         *  Moves the player south-west.
         */
        auto moveSouthWest() -> void;

        /**
         *  Moves the player north-west.
         */
        auto moveNorthWest() -> void;

        /**
         *  Adds experience to the player.
         *
         *  @param experience The experience to add.
         */
        auto addExperience(int experience) -> void;

        /**
         *  Adds a player action to the player.
         *
         *  @param playerAction The type of the player action.
         *  @param actionFirstArgument The first argument of the player action.
         *  @param actionSecondArgument The second argument of the player action.
         */
        auto addPlayerAction(PlayerActionTypes playerAction,
                             std::string_view actionFirstArgument = "",
                             Point actionSecondArgument = {-1, -1}) -> void;

        /**
         *  Gets the smooth position of the player, used for smooth movement.
         *
         *  @return The smooth position of the player.
         */
        auto getSmoothPosition() const -> PointF;

        /**
         *  Gets the name of the player.
         *
         *  @return The name of the player.
         */
        auto getName() const
        {
            return m_name;
        }

        /**
         *  Sets the position of the player.
         *
         *  @param value The value to set.
         */
        auto setPosition(Point value) -> void
        {
            m_position = value;
        }

        /**
         *  Gets the position of the player.
         *
         *  @return The position of the player.
         */
        auto getPosition() const
        {
            return m_position;
        }

        /**
         *  Gets the movement speed of the player.
         *
         *  @return The movement speed of the player.
         */
        auto getMovementSpeed() const
        {
            return m_movementSpeed;
        }

        /**
         *  Gets the ticks since last movement.
         *
         *  @return The ticks since last movement.
         */
        auto getTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        /**
         *  Sets the ticks since last movement.
         *
         *  @param value The value to set.
         */
        auto setTicksLastMovement(int value) -> void
        {
            m_ticksLastMovement = value;
        }

        /**
         *  Gets the destination of the player.
         *
         *  @return The destination of the player.
         */
        auto getDestination() const
        {
            return m_destination;
        }

        /**
         *  Sets the destination of the player.
         *
         *  @param value The value to set.
         */
        auto setDestination(Point value) -> void
        {
            m_destination = value;
        }

        /**
         *  Gets the objects inventory of the player.
         *
         *  @return The objects inventory of the player.
         */
        auto getObjectsInventoryRef() const -> PlayerObjectsInventory &
        {
            return *m_playerObjectsInventory;
        }

        /**
         *  Gets the experience of the player.
         *
         *  @return The experience of the player.
         */
        auto getExperience() const
        {
            return m_experience;
        }

        /**
         *  Gets the well-being of the player.
         *
         *  @return The well-being of the player.
         */
        auto getWellBeing() const
        {
            return m_wellBeing;
        }

        /**
         *  Gets the max well-being of the player.
         *
         *  @return The max well-being of the player.
         */
        auto getMaxWellBeing() const
        {
            return m_maxWellBeing;
        }

        /**
         *  Gets the player actions of the player.
         *
         *  @return The player actions of the player.
         */
        auto getPlayerActionsRef() const
            -> const std::vector<std::tuple<PlayerActionTypes, std::string, Point>> &
        {
            return m_playerActions;
        }

        /**
         *  Gets the quest completion points of the player.
         *
         *  @return The quest completion points of the player.
         */
        auto getQuestCompletionPointsRef() -> std::unordered_map<std::string, int> &
        {
            return m_questCompletionPoints;
        }

        // TODO: Think about if this should be kept or not.
        // /**
        //  *  Gets the spouse of the player.
        //  *
        //  *  @return The spouse of the player.
        //  */
        // auto getSpouse() const
        // {
        //     return m_spouse;
        // }

        // auto setSpouse(const std::shared_ptr<Spouse> &value) -> void
        // {
        //     m_spouse = value;
        // }

        /**
         *  Gets the world area coordinate of the player.
         *
         *  @return The world area coordinate of the player.
         */
        auto getWorldAreaCoordinate() const -> Point3
        {
            return m_worldAreaCoordinate;
        }

        /**
         *  Gets the rotation of the player in degrees.
         *
         *  @return The rotation of the player in degrees.
         */
        auto getRotationDegrees() const -> float
        {
            return m_rotationDegrees;
        }

      private:
        auto moveToSuitablePosition() -> void;

        auto moveToPositionPossible(Point position) -> bool;

        auto updateRotationDegrees() -> void;

        constexpr static Point k_defaultStartPosition{60, 50};
        constexpr static float k_defaultMovementSpeed{5.0F};
        constexpr static float k_defaultStartMaxWellBeing{10.0F};
        std::string m_name{"Unnamed Player"};
        Point m_position{k_defaultStartPosition};
        float m_movementSpeed{k_defaultMovementSpeed};
        int m_ticksLastMovement{0};
        Point m_destination{-1, -1};
        std::shared_ptr<PlayerObjectsInventory> m_playerObjectsInventory{};
        int m_experience{0};
        float m_wellBeing{k_defaultStartMaxWellBeing};
        float m_maxWellBeing{k_defaultStartMaxWellBeing};
        std::vector<std::tuple<PlayerActionTypes, std::string, Point>> m_playerActions{};
        std::unordered_map<std::string, int> m_questCompletionPoints{};
        PlayerMoveDirections m_playerMoveDirection{PlayerMoveDirections::None};
        // TODO: Think about if this should be kept or not.
        // std::shared_ptr<Spouse> m_spouse{};
        Point3 m_worldAreaCoordinate{0, 0, 0};
        float m_rotationDegrees{0.0F};
    };
}
