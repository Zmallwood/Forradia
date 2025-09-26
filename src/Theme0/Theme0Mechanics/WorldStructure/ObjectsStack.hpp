#pragma once

namespace Forradia
{
    class Object;

    class ObjectsStack
    {
    public:
        void ClearObjects();

        void AddObject(std::string_view objectTypeName);

        void AddTreeObject(std::string_view objectTypeName);

        int GetSize() const;

        auto GetObjects() const
        {
            return m_objects;
        }

    private:
        std::vector<std::shared_ptr<Object>> m_objects;
    };
}