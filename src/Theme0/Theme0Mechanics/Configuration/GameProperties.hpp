#pragma once

namespace Forradia
{
    class GameProperties
    {
    public:
        static constexpr Color k_clearColor{0.0f, 0.5f, 1.0f, 1.0f};

        static constexpr int k_numGridRows{15};

        static constexpr Size k_worldAreaSize{120, 100};
    };
}