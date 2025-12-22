/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0
{
    class ContainedObjects;

    /**
     * An object, either in the game world, a container or inventory.
     */
    class Object
    {
      public:
        /**
         * Constructor.
         *
         * @param objectNameHash The object name as a hash.
         */
        Object(int objectNameHash) : m_type(objectNameHash)
        {
            // Initialize the object.
            this->Initialize();
        }

        /**
         * Constructor.
         *
         * @param objectTypeName The object type by name.
         */
        Object(std::string_view objectTypeName) : m_type(Hash(objectTypeName))
        {
            // Initialize the object.
            this->Initialize();
        }

        /**
         * Gets the object type.
         *
         * @return The object type as a hash.
         */
        auto GetType() const
        {
            return m_type;
        }

        auto SetType(int value) -> void
        {
            m_type = value;
        }

        /**
         * Gets the model scaling of the object.
         *
         * @return The model scaling of the object.
         */
        auto GetModelScaling() const
        {
            return m_modelScaling;
        }

        auto GetContainedObjects() const -> std::shared_ptr<ContainedObjects>
        {
            return m_containedObjects;
        }

      private:
        auto Initialize() -> void;

        int m_type{0};
        float m_modelScaling{1.0F};
        std::shared_ptr<ContainedObjects> m_containedObjects{};
    };
}
