//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "HashCodes.hpp"

namespace Forradia::Theme0
{
    template <>
    String GetNameFromHash<Hash("GroundGrass")>()
    {
        return "GroundGrass";
    }

    template <>
    String GetNameFromHash<Hash("GroundWater")>()
    {
        return "GroundWater";
    }

    template <>
    String GetNameFromHash<Hash("GroundRock")>()
    {
        return "GroundRock";
    }

    template <>
    String GetNameFromHash<Hash("GroundDirt")>()
    {
        return "GroundDirt";
    }

    template <>
    String GetNameFromHash<Hash("GroundCobbleStone")>()
    {
        return "GroundCobbleStone";
    }

    template <>
    String GetNameFromHash<Hash("ObjectFirTree")>()
    {
        return "ObjectFirTree";
    }

    template <>
    String GetNameFromHash<Hash("ObjectBirchTree")>()
    {
        return "ObjectBirchTree";
    }

    template <>
    String GetNameFromHash<Hash("ObjectBush1")>()
    {
        return "ObjectBush1";
    }

    template <>
    String GetNameFromHash<Hash("ObjectBush2")>()
    {
        return "ObjectBush2";
    }

    template <>
    String GetNameFromHash<Hash("ObjectStoneBoulder")>()
    {
        return "ObjectStoneBoulder";
    }

    template <>
    String GetNameFromHash<Hash("ObjectPinkFlower")>()
    {
        return "ObjectPinkFlower";
    }

    template <>
    String GetNameFromHash<Hash("ObjectTallGrass")>()
    {
        return "ObjectTallGrass";
    }

    template <>
    String GetNameFromHash<Hash("CreatureWhiteRabbit")>()
    {
        return "CreatureWhiteRabbit";
    }

    template <>
    String GetNameFromHash<Hash("RobotMechWolf")>()
    {
        return "RobotMechWolf";
    }

    String GetNameFromAnyHash(int hash)
    {
        static constexpr std::array<StringView, 14> names{
            "GroundGrass",         "GroundWater",
            "GroundRock",          "GroundDirt",
            "GroundCobbleStone",   "ObjectFirTree",
            "ObjectBirchTree",     "ObjectBush1",
            "ObjectBush2",         "ObjectStoneBoulder",
            "ObjectPinkFlower",    "ObjectTallGrass",
            "CreatureWhiteRabbit", "RobotMechWolf"};

        auto nameResults =
            [&]<std::size_t... I>(std::index_sequence<I...>)
        {
            return std::array<String, sizeof...(I)>{
                GetNameFromHash<Hash(names[I])>()...};
        }(std::make_index_sequence<names.size()>());

        for (auto i = 0; i < names.size(); i++)
        {
            if (hash == Hash(names[i]))
            {
                return nameResults[i];
            }
        }

        return "";
    }
}