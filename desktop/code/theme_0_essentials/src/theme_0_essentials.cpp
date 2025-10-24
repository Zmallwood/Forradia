/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "theme_0_essentials.hpp"
#include "core.hpp"
#include "game_props.hpp"
#include "world_struct.hpp"

_NS_START_
namespace Theme0
{
    namespace TileGridMath
    {
        SizeF CalcTileSize()
        {
            auto numGridRows{_<GameProperties>().k_numGridRows};

            auto tileHeight{1.0f / numGridRows};

            auto aspectRatio{
                CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto tileWidth{tileHeight / aspectRatio};

            return {tileWidth, tileHeight};
        }

        float CalcTileSizeNew()
        {
            return 1.0f / _<GameProperties>().k_numGridRows;
        }

        Size CalcGridSize()
        {
            auto tileSize{CalcTileSizeNew()};

            auto aspectRatio{
                CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto numGridColumns{CInt(aspectRatio / tileSize) + 1};

            auto numGridRows{_<GameProperties>().k_numGridRows};

            return {numGridColumns, numGridRows};
        }
    }

    namespace GameplayCore
    {
        namespace Player
        {
            void PlayerBody::Initialize()
            {
                m_bodyParts.insert({BodyPartTypes::OverallBody, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::RightArm, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::LeftArm, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::Legs, BodyPart()});
            }

            BodyPart *PlayerBody::GetBodyPartPtr(BodyPartTypes bodyPartType)
            {
                if (m_bodyParts.contains(bodyPartType))
                {
                    return &m_bodyParts.at(bodyPartType);
                }

                return nullptr;
            }

            void PlayerCharacter::Initialize()
            {
                MoveToSuitablePosition();
            }

            void PlayerCharacter::MoveToSuitablePosition()
            {
                auto worldArea{_<World>().GetCurrentWorldArea()};

                auto size{worldArea->GetSize()};

                m_position = {size.width / 2, size.height / 2};

                while (worldArea->GetTile(m_position)->GetGround() ==
                       Hash("ground_water"))
                {
                    m_position = {GetRandomInt(size.width),
                                  GetRandomInt(size.height)};
                }
            }

            void PlayerCharacter::MoveNorth()
            {
                m_position.y -= 1;
            }

            void PlayerCharacter::MoveEast()
            {
                m_position.x += 1;
            }

            void PlayerCharacter::MoveSouth()
            {
                m_position.y += 1;
            }

            void PlayerCharacter::MoveWest()
            {
                m_position.x -= 1;
            }
        }
    }
}
_NS_END_