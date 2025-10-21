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
        void Creature::Initialize()
        {
            movement_speed_ *= (GetRandomInt(3) + 1) / 2.0f;
        }

        void NPC::Initialize()
        {
            GenerateName();

            ticks_next_spontaneous_speech_ =
                GetTicks() + GetRandomInt(300 * k_one_sec_millis);
        }

        void NPC::GenerateName()
        {
            Vector<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};

            Vector<char> consonants{'q', 'w', 'r', 't', 'p', 's', 'd',
                                 'f', 'g', 'h', 'j', 'k', 'l', 'z',
                                 'x', 'c', 'v', 'b', 'n', 'm'};

            char c0{vowels.at(GetRandomInt(vowels.size()))};

            char c1{consonants.at(GetRandomInt(consonants.size()))};
            char c2{consonants.at(GetRandomInt(consonants.size()))};

            char c3{vowels.at(GetRandomInt(vowels.size()))};

            char c4{consonants.at(GetRandomInt(consonants.size()))};
            char c5{consonants.at(GetRandomInt(consonants.size()))};

            char c6{vowels.at(GetRandomInt(vowels.size()))};

            name_ = String() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
        }

        void TreeObject::Initialize(StringView obj_type_name)
        {
            if (obj_type_name != "object_fir_tree" &&
                obj_type_name != "object_birch_tree")
            {
                return;
            }

            int num_trunk_parts;

            if (obj_type_name == "object_fir_tree")
            {
                num_trunk_parts = 55 + GetRandomInt(44);
            }

            else if (obj_type_name == "object_birch_tree")
            {
                num_trunk_parts = 25 + GetRandomInt(14);
            }

            width_factor_ *= (GetRandomInt(5) + 1) / 2.0f + 1.0f;

            auto offs_x{0.0f};

            for (auto i = 0; i < num_trunk_parts; i++)
            {
                offs_x += (GetRandomInt(20) - 10) / 100.0f;

                auto offset_y{i * 0.1f};

                auto pos{PointF{offs_x, offset_y}};

                auto needles_type{GetRandomInt(5)};

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
                        ? Hash(needles_name + std::to_string(needles_type))
                        : 0);
            }
        }

        void ObjectsStack::ClearObjects()
        {
            objects_.clear();
        }

        void ObjectsStack::AddObject(StringView obj_type_name)
        {
            objects_.push_back(std::make_shared<Object>(obj_type_name));
        }

        void ObjectsStack::AddTreeObject(StringView obj_type_name)
        {
            objects_.push_back(std::make_shared<TreeObject>(obj_type_name));
        }

        int ObjectsStack::GetSize() const
        {
            return objects_.size();
        }

        void Tile::Initialize()
        {
            objects_stack_ = std::make_shared<
                Forradia::Theme0::WorldStructure::ObjectsStack>();
        }

        void Tile::SetGround(StringView ground_name)
        {
            ground_ = Hash(ground_name);
        }

        void WorldArea::Initialize(Size w_area_sz, float world_scaling)
        {
            auto sz{w_area_sz};

            sz.w *= world_scaling;
            sz.h *= world_scaling;

            for (auto x = 0; x < sz.w; x++)
            {
                tiles_.push_back(Vector<std::shared_ptr<Tile>>());

                for (auto y = 0; y < sz.h; y++)
                {
                    tiles_[x].push_back(std::make_shared<Tile>());
                }
            }
        }

        Size WorldArea::GetSize() const
        {
            auto w{CInt(tiles_.size())};

            auto h{0};

            if (w)
            {
                h = tiles_.at(0).size();
            }

            return {w, h};
        }

        bool WorldArea::IsValidCoordinate(int x, int y) const
        {
            auto sz{GetSize()};

            return x >= 0 && y >= 0 && x < sz.w && y < sz.h;
        }

        bool WorldArea::IsValidCoordinate(Point coord) const
        {
            return IsValidCoordinate(coord.x, coord.y);
        }

        SharedPtr<Tile> WorldArea::GetTile(int x, int y) const
        {
            if (IsValidCoordinate(x, y))
            {
                return tiles_.at(x).at(y);
            }

            return nullptr;
        }

        SharedPtr<Tile> WorldArea::GetTile(Point coord) const
        {
            return GetTile(coord.x, coord.y);
        }

        void World::Initialize(Size w_area_sz, float world_scaling)
        {
            current_world_area_ =
                std::make_shared<WorldArea>(w_area_sz, world_scaling);
        }
    }
}
_NS_END_