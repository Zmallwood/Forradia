#include "GenerateWater.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateWater()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numLakes{20 + RandomInt(5)};

        for (auto i = 0; i < numLakes; i++)
        {
            auto xCenter{RandomInt(size.width)};
            auto yCenter{RandomInt(size.height)};
            auto radius{3 + RandomInt(5)};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile)
                        {
                            Point N{x, y - 1};
                            Point E{x + 1, y};
                            Point S{x, y + 1};
                            Point W{x - 1, y};
                            Point NW{x - 1, y - 1};
                            Point NE{x + 1, y - 1};
                            Point SE{x + 1, y + 1};
                            Point SW{x - 1, y + 1};

                            Point NN {x, y - 2};
                            Point WW {x - 2, y};
                            Point EE {x + 2, y};
                            Point SS {x, y + 2};
                            Point NWNW {x - 2, y - 2};
                            Point NENE {x + 2, y - 2};
                            Point SESE {x + 2, y + 2};
                            Point SWSW {x - 2, y + 2};

                            auto tileN{worldArea->GetTile(N)};
                            auto tileE{worldArea->GetTile(E)};
                            auto tileS{worldArea->GetTile(S)};
                            auto tileW{worldArea->GetTile(W)};
                            auto tileNW{worldArea->GetTile(NW)};
                            auto tileNE{worldArea->GetTile(NE)};
                            auto tileSE{worldArea->GetTile(SE)};
                            auto tileSW{worldArea->GetTile(SW)};

                            auto tileNN{worldArea->GetTile(NN)};
                            auto tileWW{worldArea->GetTile(WW)};
                            auto tileEE{worldArea->GetTile(EE)};
                            auto tileSS{worldArea->GetTile(SS)};
                            auto tileNWNW{worldArea->GetTile(NWNW)};
                            auto tileNENE{worldArea->GetTile(NENE)};
                            auto tileSESE{worldArea->GetTile(SESE)};
                            auto tileSWSW{worldArea->GetTile(SWSW)};

                            auto elevationN{tileN ? tileN->GetElevation() : 0};
                            auto elevationE{tileE ? tileE->GetElevation() : 0};
                            auto elevationS{tileS ? tileS->GetElevation() : 0};
                            auto elevationW{tileW ? tileW->GetElevation() : 0};
                            auto elevationNW{tileNW ? tileNW->GetElevation() : 0};
                            auto elevationNE{tileNE ? tileNE->GetElevation() : 0};
                            auto elevationSE{tileSE ? tileSE->GetElevation() : 0};
                            auto elevationSW{tileSW ? tileSW->GetElevation() : 0};

                            auto elevationNN{tileNN ? tileNN->GetElevation() : 0};
                            auto elevationWW{tileWW ? tileWW->GetElevation() : 0};
                            auto elevationEE{tileEE ? tileEE->GetElevation() : 0};
                            auto elevationSS{tileSS ? tileSS->GetElevation() : 0};
                            auto elevationNWNW{tileNWNW ? tileNWNW->GetElevation() : 0};
                            auto elevationNENE{tileNENE ? tileNENE->GetElevation() : 0};
                            auto elevationSESE{tileSESE ? tileSESE->GetElevation() : 0};
                            auto elevationSWSW{tileSWSW ? tileSWSW->GetElevation() : 0};

                            if (elevationN == 0
                            && elevationE == 0
                            && elevationS == 0
                            && elevationW == 0
                            && elevationNW == 0
                            && elevationNE == 0
                            && elevationSE == 0
                            && elevationSW == 0
                            && elevationNN == 0
                            && elevationWW == 0
                            && elevationEE == 0
                            && elevationSS == 0
                            && elevationNWNW == 0
                            && elevationNENE == 0
                            && elevationSESE == 0
                            && elevationSWSW == 0)
                            {     
                                tile->SetGround("GroundWater");
                            }
                        }
                    }
                }
            }
        }
    }
}