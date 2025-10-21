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
        SizeF calc_tl_sz();

        float calc_tl_sz_new();

        Size calc_grid_sz();
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
                auto str() const
                {
                    return str_;
                }
                auto curr_energy() const
                {
                    return curr_energy_;
                }
                auto max_energy() const
                {
                    return max_energy_;
                }
                auto temp() const
                {
                    return temp_;
                }

              private:
                float str_{0.1f};
                float curr_energy_{1.0f};
                float max_energy_{1.0f};
                float temp_{37.0f};
            };

            class PlayerBody
            {
              public:
                PlayerBody()
                {
                    init();
                }

                BodyPart *body_part_ptr(BodyPartTypes type);

              private:
                void init();

                std::map<BodyPartTypes, BodyPart> parts_;
            };

            class PlayerCharacter
            {
              public:
                PlayerCharacter()
                {
                    init();
                }

                void move_n();

                void move_e();

                void move_s();

                void move_w();

                auto name() const
                {
                    return name_;
                }

                auto pos() const
                {
                    return pos_;
                }

                auto movem_spd() const
                {
                    return movem_spd_;
                }

                auto ticks_last_move() const
                {
                    return ticks_last_move_;
                }

                void set_ticks_last_move(int val)
                {
                    ticks_last_move_ = val;
                }

                auto dest() const
                {
                    return dest_;
                }

                void set_dest(Point val)
                {
                    dest_ = val;
                }

                auto &body_ref()
                {
                    return body_;
                }

                auto money() const
                {
                    return money_;
                }

              private:
                void init();

                void move_to_suitable_pos();

                String name_{"Unnamed Player"};
                Point pos_{60, 50};
                float movem_spd_{5.0f};
                int ticks_last_move_{0};
                Point dest_{-1, -1};
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