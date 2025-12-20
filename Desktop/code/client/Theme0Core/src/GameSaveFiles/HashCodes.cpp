/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "HashCodes.hpp"

namespace Forradia::Theme0 {
    template <>
    auto GetNameFromHash<Hash("GroundGrass")>() -> std::string {
        return "GroundGrass";
    }

    template <>
    auto GetNameFromHash<Hash("GroundWater")>() -> std::string {
        return "GroundWater";
    }

    template <>
    auto GetNameFromHash<Hash("GroundRock")>() -> std::string {
        return "GroundRock";
    }

    template <>
    auto GetNameFromHash<Hash("GroundDirt")>() -> std::string {
        return "GroundDirt";
    }

    template <>
    auto GetNameFromHash<Hash("GroundCobbleStone")>() -> std::string {
        return "GroundCobbleStone";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectFirTree")>() -> std::string {
        return "ObjectFirTree";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectBirchTree")>() -> std::string {
        return "ObjectBirchTree";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectBush1")>() -> std::string {
        return "ObjectBush1";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectBush2")>() -> std::string {
        return "ObjectBush2";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectStoneBoulder")>() -> std::string {
        return "ObjectStoneBoulder";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectPinkFlower")>() -> std::string {
        return "ObjectPinkFlower";
    }

    template <>
    auto GetNameFromHash<Hash("ObjectTallGrass")>() -> std::string {
        return "ObjectTallGrass";
    }

    template <>
    auto GetNameFromHash<Hash("CreatureWhiteRabbit")>() -> std::string {
        return "CreatureWhiteRabbit";
    }

    template <>
    auto GetNameFromHash<Hash("RobotMechWolf")>() -> std::string {
        return "RobotMechWolf";
    }

    auto GetNameFromAnyHash(int hash) -> std::string {
        static constexpr std::array<std::string_view, 14> names{
            "GroundGrass",         "GroundWater",        "GroundRock",       "GroundDirt",
            "GroundCobbleStone",   "ObjectFirTree",      "ObjectBirchTree",  "ObjectBush1",
            "ObjectBush2",         "ObjectStoneBoulder", "ObjectPinkFlower", "ObjectTallGrass",
            "CreatureWhiteRabbit", "RobotMechWolf"};

        auto nameResults = [&]<std::size_t... I>(std::index_sequence<I...>) {
            return std::array<std::string, sizeof...(I)>{GetNameFromHash<Hash(names[I])>()...};
        }(std::make_index_sequence<names.size()>());

        for (auto i = 0; i < names.size(); i++)
            if (hash == Hash(names[i]))
                return nameResults[i];

        return "";
    }
}
