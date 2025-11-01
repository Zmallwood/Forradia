//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Actions.hpp"

#include "GUIChatBox.hpp"

#include "GUIInteractionMenu.hpp"

#include "PlayerCharacter.hpp"

#include "ObjectsInventory.hpp"

namespace Forradia::Theme0
{
    static std::map<int, Function<void()>> s_timedActions;

    template <>
    Action GetAction<Hash("ActionForage")>();

    template <>
    Action GetAction<Hash("ActionForageContinue")>();

    template <>
    Action GetAction<Hash("ActionPickBranch")>();

    template <>
    Action GetAction<Hash("ActionForage")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{
                        _<GameplayCore::PlayerCharacter>()
                            .GetObjectsInventoryRef()};

                    inventory.AddObject(
                        "ObjectBlueberries");

                    _<GUIChatBox>().Print(
                        "Foraging... You found some "
                        "blueberries!");

                    s_timedActions.insert(
                        {GetTicks() + 1000,
                         GetAction<Hash(
                             "ActionForageContinue")>()
                             .action});
                    s_timedActions.insert(
                        {GetTicks() + 2000,
                         GetAction<Hash(
                             "ActionForageContinue")>()
                             .action});
                    s_timedActions.insert(
                        {GetTicks() + 3000,
                         GetAction<Hash(
                             "ActionForageContinue")>()
                             .action});
                }};
    }

    template <>
    Action GetAction<Hash("ActionForageContinue")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{
                        _<GameplayCore::PlayerCharacter>()
                            .GetObjectsInventoryRef()};

                    inventory.AddObject(
                        "ObjectBlueberries");

                    _<GUIChatBox>().Print(
                        "Continue foraging... You "
                        "found some blueberries!");
                }};
    }

    template <>
    Action GetAction<Hash("ActionPickBranch")>()
    {
        return
        {
            .groundMatches = {},
            .objectMatches = {Hash("ObjectFirTree"),
                              Hash("ObjectBirchTree")},
            .action = []()
            {
                auto &inventory{
                    _<GameplayCore::PlayerCharacter>()
                        .GetObjectsInventoryRef()};

                inventory.AddObject("ObjectBranch");

                    _<GUIChatBox>().Print(
                        "You picked a branch!");
            }
        };
    }

    void UpdateActions()
    {
        for (auto it = s_timedActions.begin();
             it != s_timedActions.end();)
        {
            if (GetTicks() > it->first)
            {
                it->second();
                it = s_timedActions.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}
