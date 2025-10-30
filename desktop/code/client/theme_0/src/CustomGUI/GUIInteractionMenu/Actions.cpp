//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Actions.hpp"

#include "GUIChatBox.hpp"

#include "GUIInteractionMenu.hpp"

namespace Forradia::Theme0
{

    static std::map<int, Function<void()>> s_timedActions;

    template <>
    Action GetAction<Hash("ActionTestContinue")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                { _<GUIChatBox>().Print("Mer Test!!"); }};
    }

    template <>
    Action GetAction<Hash("ActionTest")>()
    {
        return {
            .groundMatches = {Hash("GroundGrass")},
            .objectMatches = {},
            .action = []()
            {
                _<GUIChatBox>().Print("Test!!");

                // GetAction<Hash("ActionTestContinue")>()
                //     .action();

                s_timedActions.insert(
                    {GetTicks() + 1000,
                     GetAction<Hash("ActionTestContinue")>()
                         .action});

                // static constexpr int
                // k_ActionTestContinue{
                //     Hash("ActionTestContinue")};

                // _<GUIInteractionMenu>().nextAction =
                //     &k_ActionTestContinue;

                // _<GUIInteractionMenu>()
                //     .GetTimedActionsRef()
                //     .insert({GetTicks() + 1000,
                //              Hash("ActionTestContinue")});
            }};
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
