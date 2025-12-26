/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Coloring/Palette.hpp"
    #include "ForradiaEngine/GUICore/GUIMeter.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Represents the experience bar.
     */
    class GUIExperienceBar : public GUIMeter
    {
      public:
        static auto instancePtr() -> std::shared_ptr<GUIExperienceBar>
        {
            static std::shared_ptr<GUIExperienceBar> instancePtr =
                std::make_shared<GUIExperienceBar>();
            return instancePtr;
        }

        static auto instance() -> GUIExperienceBar &
        {
            return *instancePtr();
        }

        GUIExperienceBar(const GUIExperienceBar &) = delete;

        auto operator=(const GUIExperienceBar &) -> GUIExperienceBar & = delete;

        /**
         *  Constructor.
         */
        GUIExperienceBar()
            : GUIMeter("GUIExperienceBar", 0.0F, 1.0F - k_height, 1.0F, k_height, getFilledColor())
        {
        }

        /**
         *  Gets the height of the bar.
         *
         *  @return The height of the bar.
         */
        static auto getHeight()
        {
            return k_height;
        }

      protected:
        /**
         *  Does update logic that is specific to the experience bar.
         */
        auto updateDerived() -> void override;

        /**
         *  Gets the filled percentage of the bar.
         *
         *  @return The filled percentage of the bar.
         */
        auto getFilledPercentage() const -> float override;

        /**
         *  Gets the filled color of the bar.
         *
         *  @return The filled color of the bar.
         */
        static auto getFilledColor() -> Color
        {
            return Palette::getColor<hash("Gold")>();
        }

      private:
        constexpr static float k_height{0.012F};
        float m_filledPercentage{0.0F};
    };
}
