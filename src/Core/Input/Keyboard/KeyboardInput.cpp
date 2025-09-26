#include "KeyboardInput.hpp"

namespace Forradia
{
    void KeyboardInput::Reset()
    {
        m_pressedKeys.clear();
    }

    void KeyboardInput::RegisterKeyPress( SDL_Keycode key )
    {
        m_pressedKeys.insert( key );
    }

    void KeyboardInput::RegisterKeyRelease( SDL_Keycode key )
    {
        m_pressedKeys.erase( key );
    }

    bool KeyboardInput::KeyIsPressed( SDL_Keycode key ) const
    {
        return m_pressedKeys.contains( key );
    }

    bool KeyboardInput::KeyIsPressedPickResult( SDL_Keycode key )
    {
        auto result { m_pressedKeys.contains( key ) };

        m_pressedKeys.erase( key );

        return result;
    }

    bool KeyboardInput::AnyKeyIsPressedPickResult()
    {
        auto result { m_pressedKeys.size() > 0 };

        m_pressedKeys.clear();

        return result;
    }
}
