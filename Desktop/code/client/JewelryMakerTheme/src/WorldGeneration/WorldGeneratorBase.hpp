/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <unordered_map>
#include <variant>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;

    /**
     *  Base class for world generators.
     */
    class WorldGeneratorBase
    {
      public:
        /**
         *  Prepare the world generator.
         */
        static auto prepare() -> void;

        template <typename T>
        [[nodiscard]] static auto getParam(std::string_view name) -> T
        {
            if (m_parameters.contains(hash(name)))
            {
                auto ptr{std::get_if<T>(&m_parameters.at(hash(name)))};

                if (ptr)
                {
                    return *ptr;
                }
            }

            throw std::runtime_error("Parameter not found: " + std::string(name));
        }

      protected:
        /**
         *  Get the default ground elevation.
         *
         *  @return The default ground elevation.
         */
        [[nodiscard]] constexpr static auto getDefaultGroundElevation()
        {
            return k_defaultGroundElevation;
        }

        /**
         *  Get the world area.
         *
         *  @return The world area.
         */
        [[nodiscard]] static auto getWorldArea()
        {
            return m_worldArea;
        }

        /**
         *  Get the size of the world area.
         *
         *  @return The size of the world area.
         */
        [[nodiscard]] static auto getWorldAreaSize()
        {
            return m_worldAreaSize;
        }

        /**
         *  Get the scale factor of the world.
         *
         *  @return The scale factor of the world.
         */
        [[nodiscard]] static auto getWorldScaling()
        {
            return m_worldScaling;
        }

        /**
         *  Get the world area lower floors.
         *
         *  @return The world area lower floors.
         */
        [[nodiscard]] static auto getWorldAreaLowerFloors()
        {
            return m_worldAreaLowerFloors;
        }

        /**
         *  Get the size of the world area lower floors.
         *
         *  @return The size of the world area lower floors.
         */
        [[nodiscard]] static auto getWorldAreaLowerFloorsSize()
        {
            return m_worldAreaLowerFloorsSize;
        }

        /**
         *  Get the scale factor of the world area lower floors.
         *
         *  @return The scale factor of the world area lower floors.
         */
        [[nodiscard]] static auto getWorldScalingLowerFloors()
        {
            return m_worldScalingLowerFloors;
        }

      private:
        static auto loadParameters() -> void;

        constexpr static int k_defaultGroundElevation{10};
        inline static std::shared_ptr<WorldArea> m_worldArea{};
        inline static std::shared_ptr<WorldArea> m_worldAreaLowerFloors{};
        inline static Size m_worldAreaSize{};
        inline static Size m_worldAreaLowerFloorsSize{};
        inline static float m_worldScaling{};
        inline static float m_worldScalingLowerFloors{};
        inline static std::unordered_map<int, std::variant<int, float>> m_parameters{};
    };
}
