/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "CursorStyles.hpp"
#include "Hash.hpp"

namespace Forradia
{
    /**
     *  Class for the game cursor, which replaces the default system cursor.
     */
    class Cursor
    {
      public:
        static auto instance() -> Cursor &
        {
            static Cursor instance;
            return instance;
        }

        Cursor(const Cursor &) = delete;

        auto operator=(const Cursor &) -> Cursor & = delete;

        /**
         *  Default constructor
         */
        Cursor()
        {
            Cursor::initialize();
        }

        /**
         *  Resets the cursor style to normal.
         */
        auto resetStyleToNormal() -> void;

        /**
         *  Renders the cursor.
         */
        auto render() const -> void;

        /**
         *  Sets the cursor style.
         *
         *  @param value New cursor style.
         */
        auto setCursorStyle(CursorStyles value) -> void
        {
            m_cursorStyle = value;
        }

      private:
        static auto initialize() -> void;

        static auto disableSystemCursor() -> void;

        constexpr static float k_cursorSize{0.05F};
        const int k_renderID{hash("RenderIDCursor")};
        CursorStyles m_cursorStyle{CursorStyles::Normal};
    };
}
