/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "theme_0_core.hpp"
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
            auto num_grid_rows{_<GameProperties>().k_numGridRows};

            auto tl_h{1.0f / num_grid_rows};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto tl_w{tl_h / asp_rat};

            return {tl_w, tl_h};
        }

        float CalcTileSizeNew()
        {
            return 1.0f / _<GameProperties>().k_numGridRows;
        }

        Size CalcGridSize()
        {
            auto tl_sz{CalcTileSizeNew()};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto num_grid_cols{CInt(asp_rat / tl_sz) + 1};

            auto num_grid_rows{_<GameProperties>().k_numGridRows};

            return {num_grid_cols, num_grid_rows};
        }
    }

    namespace GameplayCore
    {
        namespace Player
        {
            void PlayerBody::Initialize()
            {
                m_bodyParts.insert({BodyPartTypes::overall_body, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::right_arm, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::left_arm, BodyPart()});
                m_bodyParts.insert({BodyPartTypes::legs, BodyPart()});
            }

            BodyPart *PlayerBody::GetBodyPartPtr(BodyPartTypes type)
            {
                if (m_bodyParts.contains(type))
                {
                    return &m_bodyParts.at(type);
                }

                return nullptr;
            }

            void PlayerCharacter::Initialize()
            {
                MoveToSuitablePosition();
            }

            void PlayerCharacter::MoveToSuitablePosition()
            {
                auto w_area{_<World>().GetCurrentWorldArea()};

                auto sz{w_area->GetSize()};

                m_position = {sz.width / 2, sz.height / 2};

                while (w_area->GetTile(m_position)->GetGround() == Hash("ground_water"))
                {
                    m_position = {GetRandomInt(sz.width), GetRandomInt(sz.height)};
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