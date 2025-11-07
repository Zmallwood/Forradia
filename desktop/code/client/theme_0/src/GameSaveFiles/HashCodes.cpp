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

    String GetNameFromAnyHash(int hash)
    {
        static constexpr std::array<StringView, 5> names{
            "GroundGrass", "GroundWater", "GroundRock",
            "GroundDirt", "GroundCobbleStone"};

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