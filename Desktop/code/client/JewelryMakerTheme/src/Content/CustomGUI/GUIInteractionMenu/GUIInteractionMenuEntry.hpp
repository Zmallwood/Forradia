/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0
{
    class Tile;
    class Object;

    /**
     *  Represents an entry in the interaction menu.
     */
    class GUIInteractionMenuEntry
    {
      public:
        /**
         *  Constructor.
         *
         *  @param label The label of the entry.
         *  @param action The action to perform when the entry is clicked.
         */
        GUIInteractionMenuEntry(
            std::string_view label,
            const std::function<void(std::shared_ptr<Tile>, std::vector<std::shared_ptr<Object> *>)>
                &action)
            : m_label(label), m_action(action)
        {
        }

        /**
         *  Gets the label of the entry.
         *
         *  @return The label of the entry.
         */
        [[nodiscard]] auto getLabel() const
        {
            return m_label;
        }

        /**
         *  Gets the action of the entry.
         *
         *  @return The action of the entry.
         */
        [[nodiscard]] auto getAction() const
        {
            return m_action;
        }

      private:
        std::string m_label{};
        std::function<void(std::shared_ptr<Tile>, std::vector<std::shared_ptr<Object> *>)>
            m_action{};
    };
}
