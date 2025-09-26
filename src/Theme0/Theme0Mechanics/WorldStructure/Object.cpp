#include "Object.hpp"

namespace Forradia
{
    Object::Object(std::string_view objectTypeName)
        : m_type(Hash(objectTypeName))
    {
    }
}