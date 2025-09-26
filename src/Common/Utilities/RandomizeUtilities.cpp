#include "RandomizeUtilities.hpp"

namespace Forradia
{
    void Randomize()
    {
        srand(time(nullptr));
    }

    int RandomInt(int upperLimit)
    {
        return rand() % upperLimit;
    }
}
