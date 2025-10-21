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
        SizeF calc_tl_sz()
        {
            auto num_grid_rows{_<GameProperties>().k_num_grid_rows};

            auto tl_h{1.0f / num_grid_rows};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().win())};

            auto tl_w{tl_h / asp_rat};

            return {tl_w, tl_h};
        }

        float calc_tl_sz_new()
        {
            return 1.0f / _<GameProperties>().k_num_grid_rows;
        }

        Size calc_grid_sz()
        {
            auto tl_sz{calc_tl_sz_new()};

            auto asp_rat{CalcAspectRatio(_<Engine::SDLDevice>().win())};

            auto num_grid_cols{CInt(asp_rat / tl_sz) + 1};

            auto num_grid_rows{_<GameProperties>().k_num_grid_rows};

            return {num_grid_cols, num_grid_rows};
        }
    }

    namespace GameplayCore
    {
        namespace Player
        {
            void PlayerBody::init()
            {
                parts_.insert({BodyPartTypes::overall_body, BodyPart()});
                parts_.insert({BodyPartTypes::right_arm, BodyPart()});
                parts_.insert({BodyPartTypes::left_arm, BodyPart()});
                parts_.insert({BodyPartTypes::legs, BodyPart()});
            }

            BodyPart *PlayerBody::body_part_ptr(BodyPartTypes type)
            {
                if (parts_.contains(type))
                {
                    return &parts_.at(type);
                }

                return nullptr;
            }

            void PlayerCharacter::init()
            {
                move_to_suitable_pos();
            }

            void PlayerCharacter::move_to_suitable_pos()
            {
                auto w_area{_<World>().curr_w_area()};

                auto sz{w_area->get_sz()};

                pos_ = {sz.w / 2, sz.h / 2};

                while (w_area->get_tl(pos_)->ground() == Hash("ground_water"))
                {
                    pos_ = {GetRandomInt(sz.w), GetRandomInt(sz.h)};
                }
            }

            void PlayerCharacter::move_n()
            {
                pos_.y -= 1;
            }

            void PlayerCharacter::move_e()
            {
                pos_.x += 1;
            }

            void PlayerCharacter::move_s()
            {
                pos_.y += 1;
            }

            void PlayerCharacter::move_w()
            {
                pos_.x -= 1;
            }
        }
    }
}
_NS_END_