/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "HashCodes.hpp"

#include <array>

#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    template <>
    auto getNameFromHash<ForradiaEngine::hash("GroundGrass")>() -> std::string
    {
        return "GroundGrass";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("GroundWater")>() -> std::string
    {
        return "GroundWater";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("GroundRock")>() -> std::string
    {
        return "GroundRock";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("GroundDirt")>() -> std::string
    {
        return "GroundDirt";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("GroundCobbleStone")>() -> std::string
    {
        return "GroundCobbleStone";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectFirTree")>() -> std::string
    {
        return "ObjectFirTree";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectBirchTree")>() -> std::string
    {
        return "ObjectBirchTree";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectBush1")>() -> std::string
    {
        return "ObjectBush1";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectBush2")>() -> std::string
    {
        return "ObjectBush2";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectStoneBoulder")>() -> std::string
    {
        return "ObjectStoneBoulder";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectPinkFlower")>() -> std::string
    {
        return "ObjectPinkFlower";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("ObjectTallGrass")>() -> std::string
    {
        return "ObjectTallGrass";
    }

    template <>
    auto getNameFromHash<ForradiaEngine::hash("CreatureWhiteRabbit")>() -> std::string
    {
        return "CreatureWhiteRabbit";
    }

    auto getNameFromAnyHash(int hashCode) -> std::string
    {
        static constexpr std::array<std::string_view, 13> names{
            "GroundGrass",        "GroundWater",        "GroundRock",       "GroundDirt",
            "GroundCobbleStone",  "ObjectFirTree",      "ObjectBirchTree",  "ObjectBush1",
            "ObjectBush2",        "ObjectStoneBoulder", "ObjectPinkFlower", "ObjectTallGrass",
            "CreatureWhiteRabbit"};

        auto nameResults = [&]<std::size_t... I>(std::index_sequence<I...>)
        {
            return std::array<std::string, sizeof...(I)>{getNameFromHash<hash(names[I])>()...};
        }(std::make_index_sequence<names.size()>());

        for (auto i = 0; i < names.size(); i++)
        {
            if (hashCode == hash(names[i]))
            {
                return nameResults[i];
            }
        }

        return "";
    }
}
