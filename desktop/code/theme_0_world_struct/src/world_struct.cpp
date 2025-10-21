/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_struct.hpp"

_NS_START_
namespace Theme0
{
    namespace WorldStructure
    {
        void creature::init()
        {
            movem_spd_ *= (rand_int(3) + 1) / 2.0f;
        }

        void npc::init()
        {
            gen_name();

            ticks_next_spontaneous_speech_ =
                ticks() + rand_int(300 * k_one_sec_millis);
        }

        void npc::gen_name()
        {
            Vector<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};

            Vector<char> consonants{'q', 'w', 'r', 't', 'p', 's', 'd',
                                 'f', 'g', 'h', 'j', 'k', 'l', 'z',
                                 'x', 'c', 'v', 'b', 'n', 'm'};

            char c0{vowels.at(rand_int(vowels.size()))};

            char c1{consonants.at(rand_int(consonants.size()))};
            char c2{consonants.at(rand_int(consonants.size()))};

            char c3{vowels.at(rand_int(vowels.size()))};

            char c4{consonants.at(rand_int(consonants.size()))};
            char c5{consonants.at(rand_int(consonants.size()))};

            char c6{vowels.at(rand_int(vowels.size()))};

            name_ = String() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
        }

        void tree_object::init(StringView obj_type_name)
        {
            if (obj_type_name != "object_fir_tree" &&
                obj_type_name != "object_birch_tree")
            {
                return;
            }

            int num_trunk_parts;

            if (obj_type_name == "object_fir_tree")
            {
                num_trunk_parts = 55 + rand_int(44);
            }

            else if (obj_type_name == "object_birch_tree")
            {
                num_trunk_parts = 25 + rand_int(14);
            }

            w_factor_ *= (rand_int(5) + 1) / 2.0f + 1.0f;

            auto offs_x{0.0f};

            for (auto i = 0; i < num_trunk_parts; i++)
            {
                offs_x += (rand_int(20) - 10) / 100.0f;

                auto offset_y{i * 0.1f};

                auto pos{pt_f{offs_x, offset_y}};

                auto needles_type{rand_int(5)};

                trunk_parts_.push_back(pos);

                String needles_name;

                if (obj_type_name == "object_fir_tree")
                {
                    needles_name = "object_fir_tree_needles_";
                }
                else if (obj_type_name == "object_birch_tree")
                {
                    if (i % 4 != 0)
                    {
                        needle_types_.push_back(0);

                        continue;
                    }

                    needles_name = "object_birch_tree_branch_";
                }

                needle_types_.push_back(
                    needles_type
                        ? hash(needles_name + std::to_string(needles_type))
                        : 0);
            }
        }

        void objects_stack::clear_objs()
        {
            objects_.clear();
        }

        void objects_stack::add_obj(StringView obj_type_name)
        {
            objects_.push_back(std::make_shared<object>(obj_type_name));
        }

        void objects_stack::add_tree_obj(StringView obj_type_name)
        {
            objects_.push_back(std::make_shared<tree_object>(obj_type_name));
        }

        int objects_stack::get_sz() const
        {
            return objects_.size();
        }

        void tile::init()
        {
            objects_stack_ = std::make_shared<
                Forradia::Theme0::WorldStructure::objects_stack>();
        }

        void tile::set_ground(StringView ground_name)
        {
            ground_ = hash(ground_name);
        }

        void world_area::init(sz w_area_sz, float world_scaling)
        {
            auto sz{w_area_sz};

            sz.w *= world_scaling;
            sz.h *= world_scaling;

            for (auto x = 0; x < sz.w; x++)
            {
                tiles_.push_back(Vector<std::shared_ptr<tile>>());

                for (auto y = 0; y < sz.h; y++)
                {
                    tiles_[x].push_back(std::make_shared<tile>());
                }
            }
        }

        sz world_area::get_sz() const
        {
            auto w{c_int(tiles_.size())};

            auto h{0};

            if (w)
            {
                h = tiles_.at(0).size();
            }

            return {w, h};
        }

        bool world_area::is_valid_coord(int x, int y) const
        {
            auto sz{get_sz()};

            return x >= 0 && y >= 0 && x < sz.w && y < sz.h;
        }

        bool world_area::is_valid_coord(pt coord) const
        {
            return is_valid_coord(coord.x, coord.y);
        }

        SharedPtr<tile> world_area::get_tl(int x, int y) const
        {
            if (is_valid_coord(x, y))
            {
                return tiles_.at(x).at(y);
            }

            return nullptr;
        }

        SharedPtr<tile> world_area::get_tl(pt coord) const
        {
            return get_tl(coord.x, coord.y);
        }

        void world::init(sz w_area_sz, float world_scaling)
        {
            curr_w_area_ =
                std::make_shared<world_area>(w_area_sz, world_scaling);
        }
    }
}
_NS_END_