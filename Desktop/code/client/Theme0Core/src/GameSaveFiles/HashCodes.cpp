/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "HashCodes.hpp"

namespace Forradia::Theme0 {
  template <>
  auto GetNameFromHash<Hash("GroundGrass")>() -> String {
    return "GroundGrass";
  }

  template <>
  auto GetNameFromHash<Hash("GroundWater")>() -> String {
    return "GroundWater";
  }

  template <>
  auto GetNameFromHash<Hash("GroundRock")>() -> String {
    return "GroundRock";
  }

  template <>
  auto GetNameFromHash<Hash("GroundDirt")>() -> String {
    return "GroundDirt";
  }

  template <>
  auto GetNameFromHash<Hash("GroundCobbleStone")>() -> String {
    return "GroundCobbleStone";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectFirTree")>() -> String {
    return "ObjectFirTree";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectBirchTree")>() -> String {
    return "ObjectBirchTree";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectBush1")>() -> String {
    return "ObjectBush1";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectBush2")>() -> String {
    return "ObjectBush2";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectStoneBoulder")>() -> String {
    return "ObjectStoneBoulder";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectPinkFlower")>() -> String {
    return "ObjectPinkFlower";
  }

  template <>
  auto GetNameFromHash<Hash("ObjectTallGrass")>() -> String {
    return "ObjectTallGrass";
  }

  template <>
  auto GetNameFromHash<Hash("CreatureWhiteRabbit")>() -> String {
    return "CreatureWhiteRabbit";
  }

  template <>
  auto GetNameFromHash<Hash("RobotMechWolf")>() -> String {
    return "RobotMechWolf";
  }

  auto GetNameFromAnyHash(int hash) -> String {
    static constexpr std::array<StringView, 14> names{
        "GroundGrass",         "GroundWater",        "GroundRock",       "GroundDirt",
        "GroundCobbleStone",   "ObjectFirTree",      "ObjectBirchTree",  "ObjectBush1",
        "ObjectBush2",         "ObjectStoneBoulder", "ObjectPinkFlower", "ObjectTallGrass",
        "CreatureWhiteRabbit", "RobotMechWolf"};

    auto nameResults = [&]<std::size_t... I>(std::index_sequence<I...>) {
      return std::array<String, sizeof...(I)>{GetNameFromHash<Hash(names[I])>()...};
    }(std::make_index_sequence<names.size()>());

    for (auto i = 0; i < names.size(); i++)
      if (hash == Hash(names[i]))
        return nameResults[i];

    return "";
  }
}
