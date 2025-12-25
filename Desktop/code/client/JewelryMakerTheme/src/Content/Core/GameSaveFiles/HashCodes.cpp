/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "HashCodes.hpp"
    #include "ForradiaEngine/Common/General/Hash.hpp"
    #include <array>
// clang-format on

namespace Forradia::Theme0
{
    template <>
    auto getNameFromHash<hash("GroundGrass")>() -> std::string
    {
        return "GroundGrass";
    }

    template <>
    auto getNameFromHash<hash("GroundWater")>() -> std::string
    {
        return "GroundWater";
    }

    template <>
    auto getNameFromHash<hash("GroundRock")>() -> std::string
    {
        return "GroundRock";
    }

    template <>
    auto getNameFromHash<hash("GroundDirt")>() -> std::string
    {
        return "GroundDirt";
    }

    template <>
    auto getNameFromHash<hash("GroundCobbleStone")>() -> std::string
    {
        return "GroundCobbleStone";
    }

    template <>
    auto getNameFromHash<hash("ObjectFirTree")>() -> std::string
    {
        return "ObjectFirTree";
    }

    template <>
    auto getNameFromHash<hash("ObjectBirchTree")>() -> std::string
    {
        return "ObjectBirchTree";
    }

    template <>
    auto getNameFromHash<hash("ObjectBush1")>() -> std::string
    {
        return "ObjectBush1";
    }

    template <>
    auto getNameFromHash<hash("ObjectBush2")>() -> std::string
    {
        return "ObjectBush2";
    }

    template <>
    auto getNameFromHash<hash("ObjectStoneBoulder")>() -> std::string
    {
        return "ObjectStoneBoulder";
    }

    template <>
    auto getNameFromHash<hash("ObjectPinkFlower")>() -> std::string
    {
        return "ObjectPinkFlower";
    }

    template <>
    auto getNameFromHash<hash("ObjectTallGrass")>() -> std::string
    {
        return "ObjectTallGrass";
    }

    template <>
    auto getNameFromHash<hash("CreatureWhiteRabbit")>() -> std::string
    {
        return "CreatureWhiteRabbit";
    }

    template <>
    auto getNameFromHash<hash("RobotMechWolf")>() -> std::string
    {
        return "RobotMechWolf";
    }

    auto getNameFromAnyHash(int hashCode) -> std::string
    {
        static constexpr std::array<std::string_view, 14> names{
            "GroundGrass",         "GroundWater",        "GroundRock",       "GroundDirt",
            "GroundCobbleStone",   "ObjectFirTree",      "ObjectBirchTree",  "ObjectBush1",
            "ObjectBush2",         "ObjectStoneBoulder", "ObjectPinkFlower", "ObjectTallGrass",
            "CreatureWhiteRabbit", "RobotMechWolf"};

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
