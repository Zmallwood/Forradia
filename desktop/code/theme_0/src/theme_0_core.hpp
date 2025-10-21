/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
namespace Theme0
{
    namespace TileGridMath
    {
        SizeF CalcTileSize();

        float CalcTileSizeNew();

        Size CalcGridSize();
    }
    using namespace TileGridMath;

    namespace GameplayCore
    {
        namespace Player
        {
            enum class BodyPartTypes
            {
                none,
                overall_body,
                right_arm,
                left_arm,
                legs
            };

            class BodyPart
            {
              public:
                auto GetStrength() const
                {
                    return strength_;
                }
                auto GetCurrentEnergy() const
                {
                    return current_energy_;
                }
                auto GetMaxEnergy() const
                {
                    return max_energy_;
                }
                auto GetTemperature() const
                {
                    return temperature_;
                }

              private:
                float strength_{0.1f};
                float current_energy_{1.0f};
                float max_energy_{1.0f};
                float temperature_{37.0f};
            };

            class PlayerBody
            {
              public:
                PlayerBody()
                {
                    Initialize();
                }

                BodyPart *GetBodyPartPtr(BodyPartTypes type);

              private:
                void Initialize();

                std::map<BodyPartTypes, BodyPart> parts_;
            };

            class PlayerCharacter
            {
              public:
                PlayerCharacter()
                {
                    Initialize();
                }

                void MoveNorth();

                void MoveEast();

                void MoveSouth();

                void MoveWest();

                auto GetName() const
                {
                    return name_;
                }

                auto GetPosition() const
                {
                    return position_;
                }

                auto GetMovementSpeed() const
                {
                    return movement_speed_;
                }

                auto GetTicksLastMovement() const
                {
                    return ticks_last_movement_;
                }

                void SetTicksLastMovement(int value)
                {
                    ticks_last_movement_ = value;
                }

                auto GetDestination() const
                {
                    return destination_;
                }

                void SetDestination(Point value)
                {
                    destination_ = value;
                }

                auto &GetBodyRef()
                {
                    return body_;
                }

                auto GetMoney() const
                {
                    return money_;
                }

              private:
                void Initialize();

                void MoveToSuitablePosition();

                String name_{"Unnamed Player"};
                Point position_{60, 50};
                float movement_speed_{5.0f};
                int ticks_last_movement_{0};
                Point destination_{-1, -1};
                PlayerBody body_;
                int money_{0};
            };
        }
        using namespace Player;
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_                             \
    }                                                                          \
    using namespace GameplayCore;
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_ }
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_
        using namespace Theme0;
        _NS_END_