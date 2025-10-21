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
            auto num_grid_rows{_<GameProperties>().k_num_grid_rows};

            auto tl_h{1.0f / num_grid_rows};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto tl_w{tl_h / asp_rat};

            return {tl_w, tl_h};
        }

        float CalcTileSizeNew()
        {
            return 1.0f / _<GameProperties>().k_num_grid_rows;
        }

        Size CalcGridSize()
        {
            auto tl_sz{CalcTileSizeNew()};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().GetWindow())};

            auto num_grid_cols{CInt(asp_rat / tl_sz) + 1};

            auto num_grid_rows{_<GameProperties>().k_num_grid_rows};

            return {num_grid_cols, num_grid_rows};
        }
    }

    namespace GameplayCore
    {
        namespace Player
        {
            void PlayerBody::Initialize()
            {
                parts_.insert({BodyPartTypes::overall_body, BodyPart()});
                parts_.insert({BodyPartTypes::right_arm, BodyPart()});
                parts_.insert({BodyPartTypes::left_arm, BodyPart()});
                parts_.insert({BodyPartTypes::legs, BodyPart()});
            }

            BodyPart *PlayerBody::GetBodyPartPtr(BodyPartTypes type)
            {
                if (parts_.contains(type))
                {
                    return &parts_.at(type);
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

                position_ = {sz.w / 2, sz.h / 2};

                while (w_area->GetTile(position_)->GetGround() == Hash("ground_water"))
                {
                    position_ = {GetRandomInt(sz.w), GetRandomInt(sz.h)};
                }
            }

            void PlayerCharacter::MoveNorth()
            {
                position_.y -= 1;
            }

            void PlayerCharacter::MoveEast()
            {
                position_.x += 1;
            }

            void PlayerCharacter::MoveSouth()
            {
                position_.y += 1;
            }

            void PlayerCharacter::MoveWest()
            {
                position_.x -= 1;
            }
        }
    }
}
_NS_END_