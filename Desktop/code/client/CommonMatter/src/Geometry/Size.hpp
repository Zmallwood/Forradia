/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia {
    /**
     * Size in 2D space, with the dimensions as int values.
     */
    class Size {
      public:
        /**
         * The width.
         */
        int width{0};

        /**
         * The height.
         */
        int height{0};
    };
}
