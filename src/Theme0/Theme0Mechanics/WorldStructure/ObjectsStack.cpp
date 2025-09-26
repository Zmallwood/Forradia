#include "ObjectsStack.hpp"
#include "Object.hpp"
#include "TreeObject.hpp"

namespace Forradia
{
    void ObjectsStack::ClearObjects()
    {
        m_objects.clear();
    }

    void ObjectsStack::AddObject( std::string_view objectTypeName )
    {
        m_objects.push_back(
            std::make_shared<Object>( objectTypeName )
        ); 
    }

    void ObjectsStack::AddTreeObject( std::string_view objectTypeName )
    {
        m_objects.push_back(
            std::make_shared<TreeObject>( objectTypeName )
        ); 
    }

    int ObjectsStack::GetSize() const
    {
        return m_objects.size();
    }
}