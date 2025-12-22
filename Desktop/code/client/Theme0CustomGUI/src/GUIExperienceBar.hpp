/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Palette.hpp"
#include "GUIMeter.hpp"

namespace Forradia::Theme0 {
    /**
     * Represents the experience bar.
     */
    class GUIExperienceBar : public GUIMeter {
      public:
        static auto InstancePtr() -> std::shared_ptr<GUIExperienceBar> {
            static std::shared_ptr<GUIExperienceBar> instancePtr =
                std::make_shared<GUIExperienceBar>();
            return instancePtr;
        }

        static auto Instance() -> GUIExperienceBar & {
            return *InstancePtr();
        }

        // Delete copy/move
        GUIExperienceBar(const GUIExperienceBar &) = delete;
        GUIExperienceBar &operator=(const GUIExperienceBar &) = delete;

        /**
         * Constructor.
         */
        GUIExperienceBar()
            : GUIMeter("GUIExperienceBar", 0.0f, 1.0f - k_height, 1.0f, k_height,
                       GetFilledColor()) {
        }

        /**
         * Gets the height of the bar.
         *
         * @return The height of the bar.
         */
        auto GetHeight() const {
            return k_height;
        }

      protected:
        /**
         * Does update logic that is specific to the experience bar.
         */
        auto UpdateDerived() -> void override;

        /**
         * Gets the filled percentage of the bar.
         *
         * @return The filled percentage of the bar.
         */
        auto GetFilledPercentage() const -> float override;

        /**
         * Gets the filled color of the bar.
         *
         * @return The filled color of the bar.
         */
        auto GetFilledColor() const -> Color {
            return Palette::GetColor<Hash("Gold")>();
        }

      private:
        constexpr static float k_height{0.012f};
        float m_filledPercentage{0.0f};
    };
}
