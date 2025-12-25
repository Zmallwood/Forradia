/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "Action.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    /**
     *  Gets the action for the given action type. The action name hash is passed as a template
     *  parameter.
     *
     *  @tparam N The action name hash.
     *  @return The action for the given action type.
     */
    template <int N>
    // ReSharper disable once CppFunctionIsNotImplemented
    auto getAction() -> Action;

    /**
     *  Updates the actions which are timed actions.
     */
    auto updateActions() -> void;
}
