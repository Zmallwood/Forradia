//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0::GameplayCore
{
    class WorldView
    {
      public:
        WorldView()
        {
            this->Initiallize();
        }

        void Render() const;

      private:
        void Initiallize();

        const int k_maxWaterDepthRendering{20};

        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};

        std::map<int, std::map<int, int>> m_renderIDsGround;

        std::map<int, std::map<int, std::map<int, int>>> m_renderIDsWaterDepth;
    };
}