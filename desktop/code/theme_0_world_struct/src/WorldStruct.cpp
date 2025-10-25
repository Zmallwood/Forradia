//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldStruct.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void Creature::Initialize()
        {
            m_movementSpeed *= (GetRandomInt(3) + 1) / 2.0f;
        }

        void NPC::Initialize()
        {
            GenerateName();

            m_ticksNextSpontaneousSpeech =
                GetTicks() +
                GetRandomInt(300 * k_oneSecMillis);
        }

        void NPC::GenerateName()
        {
            Vector<char> vowels{'a', 'e', 'i',
                                'o', 'u', 'y'};

            Vector<char> consonants{
                'q', 'w', 'r', 't', 'p', 's', 'd',
                'f', 'g', 'h', 'j', 'k', 'l', 'z',
                'x', 'c', 'v', 'b', 'n', 'm'};

            char c0{vowels.at(GetRandomInt(vowels.size()))};

            char c1{consonants.at(
                GetRandomInt(consonants.size()))};

            char c2{consonants.at(
                GetRandomInt(consonants.size()))};

            char c3{vowels.at(GetRandomInt(vowels.size()))};

            char c4{consonants.at(
                GetRandomInt(consonants.size()))};

            char c5{consonants.at(
                GetRandomInt(consonants.size()))};

            char c6{vowels.at(GetRandomInt(vowels.size()))};

            m_name =
                String() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
        }

        void
        TreeObject::Initialize(StringView objectTypeName)
        {
            if (objectTypeName != "object_fir_tree" &&
                objectTypeName != "object_birch_tree")
            {
                return;
            }

            int numTrunkParts;

            if (objectTypeName == "object_fir_tree")
            {
                numTrunkParts = 25 + GetRandomInt(44);
            }

            else if (objectTypeName == "object_birch_tree")
            {
                numTrunkParts = 25 + GetRandomInt(14);
            }

            m_widthFactor *=
                (GetRandomInt(5) + 1) / 2.0f + 1.0f;

            auto offsetX{0.0f};

            for (auto i = 0; i < numTrunkParts; i++)
            {
                offsetX += (GetRandomInt(20) - 10) / 100.0f;

                auto offsetY{i * 1.0f};

                auto position{PointF{offsetX, offsetY}};

                auto needlesType{GetRandomInt(5)};

                m_trunkParts.push_back(position);

                if (i < 20)
                {
                    m_needleTypes.push_back(0);

                    continue;
                }

                String needlesName;

                if (objectTypeName == "object_fir_tree")
                {
                    needlesName =
                        "object_fir_tree_needles_";
                }
                else if (objectTypeName ==
                         "object_birch_tree")
                {
                    if (i % 8 != 0)
                    {
                        m_needleTypes.push_back(0);

                        continue;
                    }

                    needlesName =
                        "object_birch_tree_branch_";
                }

                m_needleTypes.push_back(
                    needlesType
                        ? Hash(needlesName +
                               std::to_string(needlesType))
                        : 0);
            }
        }

        void ObjectsStack::ClearObjects()
        {
            m_objects.clear();
        }

        void
        ObjectsStack::AddObject(StringView objectTypeName)
        {
            m_objects.push_back(
                std::make_shared<Object>(objectTypeName));
        }

        void ObjectsStack::AddTreeObject(
            StringView objectTypeName)
        {
            m_objects.push_back(
                std::make_shared<TreeObject>(
                    objectTypeName));
        }

        void ObjectsStack::RemoveObjectOfType(
            StringView objectTypeName)
        {
            for (auto it = m_objects.begin();
                 it != m_objects.end();)
            {
                if ((*it)->GetType() ==
                    Hash(objectTypeName))
                {
                    it = m_objects.erase(it);

                    return;
                }
                else
                {
                    it++;
                }
            }
        }

        int ObjectsStack::GetSize() const
        {
            return m_objects.size();
        }

        void Tile::Initialize()
        {
            m_objectsStack = std::make_shared<
                Forradia::Theme0::ObjectsStack>();
        }

        void Tile::SetGround(StringView ground_name)
        {
            m_ground = Hash(ground_name);
        }

        void WorldArea::Initialize(Size w_area_sz,
                                   float world_scaling)
        {
            auto size{w_area_sz};

            size.width *= world_scaling;

            size.height *= world_scaling;

            for (auto x = 0; x < size.width; x++)
            {
                m_tiles.push_back(
                    Vector<std::shared_ptr<Tile>>());

                for (auto y = 0; y < size.height; y++)
                {
                    m_tiles[x].push_back(
                        std::make_shared<Tile>());
                }
            }
        }

        Size WorldArea::GetSize() const
        {
            auto width{CInt(m_tiles.size())};

            auto height{0};

            if (width)
            {
                height = m_tiles.at(0).size();
            }

            return {width, height};
        }

        bool WorldArea::IsValidCoordinate(int x,
                                          int y) const
        {
            auto size{GetSize()};

            return x >= 0 && y >= 0 && x < size.width &&
                   y < size.height;
        }

        bool WorldArea::IsValidCoordinate(Point coord) const
        {
            return IsValidCoordinate(coord.x, coord.y);
        }

        SharedPtr<Tile> WorldArea::GetTile(int x,
                                           int y) const
        {
            if (IsValidCoordinate(x, y))
            {
                return m_tiles.at(x).at(y);
            }

            return nullptr;
        }

        SharedPtr<Tile>
        WorldArea::GetTile(Point coord) const
        {
            return GetTile(coord.x, coord.y);
        }

        void World::Initialize(Size w_area_sz,
                               float world_scaling)
        {
            m_currentWorldArea =
                std::make_shared<WorldArea>(w_area_sz,
                                            world_scaling);
        }
    }
}