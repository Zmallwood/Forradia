/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

 #pragma once

 #include "ForradiaEngine/Common/Matter/Coloring.hpp"
 #include "ForradiaEngine/GUICore/GUIMeter.hpp"
 
 namespace ForradiaEngine::JewelryMakerTheme
 {
     /**
      *  Represents the experience bar.
      */
     class GUITimedActionBar : public GUIMeter
     {
       public:
         static auto instancePtr() -> std::shared_ptr<GUITimedActionBar>
         {
             static std::shared_ptr<GUITimedActionBar> instancePtr =
                 std::make_shared<GUITimedActionBar>();
             return instancePtr;
         }
 
         static auto instance() -> GUITimedActionBar &
         {
             return *instancePtr();
         }
 
         GUITimedActionBar(const GUITimedActionBar &) = delete;
 
         auto operator=(const GUITimedActionBar &) -> GUITimedActionBar & = delete;
 
         /**
          *  Constructor.
          */
          GUITimedActionBar()
             : GUIMeter("GUITimedActionBar", 0.4F, 0.5F, 0.2F, k_height, getFilledColor())
         {
         }
 
       protected:
         /**
          *  Does update logic that is specific to the experience bar.
          */
         auto update() -> void override;

         /**
          *  Does update logic that is specific to the timed action bar.
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
             return Palette::getColor<hash("Wheat")>();
         }
 
       private:
         constexpr static float k_height{0.012F};
         float m_filledPercentage{0.0F};
     };
 }
 