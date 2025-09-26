#include "NumbersUtilities.hpp"

namespace Forradia
{
    float InvertMovementSpeed(float number)
    {
        if (number)
        {
            return k_oneSecondMillis / number;
        }
        else
        {
            return 0.0f;
        }
    }
}