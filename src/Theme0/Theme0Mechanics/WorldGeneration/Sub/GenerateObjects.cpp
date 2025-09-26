#include "GenerateObjects.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/ObjectsStack.hpp"

namespace Forradia
{
    void GenerateObjects()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        // auto numTree1s { 200 + RandomInt( 50 ) };

        // for (auto i = 0; i < numTree1s; i++)
        // {
        //     auto x { RandomInt( size.width ) };
        //     auto y { RandomInt( size.height ) };

        //     auto tile { worldArea->GetTile( x, y ) };

        //     if (tile && tile->GetGround() == Hash( "GroundGrass" ))
        //     {
        //         tile->GetObjectsStack()->ClearObjects();
        //         tile->GetObjectsStack()->AddObject( "ObjectTree1" );
        //     }
        // }

        auto numFirTrees{1800 + RandomInt(50)};

        for (auto i = 0; i < numFirTrees; i++)
        {
            auto x{RandomInt(size.width)};
            auto y{RandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (tile && tile->GetGround() == Hash("GroundGrass"))
            {
                tile->GetObjectsStack()->ClearObjects();
                tile->GetObjectsStack()->AddTreeObject("ObjectFirTree");
            }
        }
    }
}