/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Action.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Gets the action for the given action type. The action name hash is passed as a template
     *  parameter.
     *
     *  @tparam N The action name hash.
     *  @return The action for the given action type.
     */
    template <int N>
    auto getAction() -> Action;

    /**
     *  Updates the timed action if there is one.
     */
    auto updateTimedAction() -> void;

    /**
     *  Gets the progress of the timed action.
     *
     *  @return The progress of the timed action.
     */
    auto getTimedActionProgress() -> float;
}
