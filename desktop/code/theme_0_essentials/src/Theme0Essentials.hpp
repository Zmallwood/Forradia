/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Common.hpp"

namespace Forradia
{
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
                    None,
                    OverallBody,
                    RightArm,
                    LeftArm,
                    Legs
                };

                class BodyPart
                {
                  public:
                    auto GetStrength() const
                    {
                        return m_strength;
                    }
                    auto GetCurrentEnergy() const
                    {
                        return m_currentEnergy;
                    }
                    auto GetMaxEnergy() const
                    {
                        return m_maxEnergy;
                    }
                    auto GetTemperature() const
                    {
                        return m_temperature;
                    }

                  private:
                    float m_strength{0.1f};
                    float m_currentEnergy{1.0f};
                    float m_maxEnergy{1.0f};
                    float m_temperature{37.0f};
                };

                class PlayerBody
                {
                  public:
                    PlayerBody()
                    {
                        Initialize();
                    }

                    BodyPart *GetBodyPartPtr(BodyPartTypes bodyPartType);

                  private:
                    void Initialize();

                    std::map<BodyPartTypes, BodyPart> m_bodyParts;
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
                        return m_name;
                    }

                    auto GetPosition() const
                    {
                        return m_position;
                    }

                    auto GetMovementSpeed() const
                    {
                        return m_movementSpeed;
                    }

                    auto GetTicksLastMovement() const
                    {
                        return m_ticksLastMovement;
                    }

                    void SetTicksLastMovement(int value)
                    {
                        m_ticksLastMovement = value;
                    }

                    auto GetDestination() const
                    {
                        return m_destination;
                    }

                    void SetDestination(Point value)
                    {
                        m_destination = value;
                    }

                    auto &GetBodyRef()
                    {
                        return m_body;
                    }

                    auto GetMoney() const
                    {
                        return m_money;
                    }

                  private:
                    void Initialize();

                    void MoveToSuitablePosition();

                    String m_name{"Unnamed Player"};
                    Point m_position{60, 50};
                    float m_movementSpeed{5.0f};
                    int m_ticksLastMovement{0};
                    Point m_destination{-1, -1};
                    PlayerBody m_body;
                    int m_money{0};
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
        }