﻿using YrradiaSDL2.Game.WorldStructure;

namespace YrradiaSDL2.ForradiaTheme.Scenes.WorldGenerationScene.Modules
{
    public class WorldGenerator
    {
        public void GenerateWorld()
        {
            ClearWithGrass();
            GenerateWater();
            GenerateForests();
            GenerateObjects();
            GenerateMountains();
            GenerateTrainObjects();
            GenerateMobs();
        }

        private void ClearWithGrass()
        {
            var worldArea = _.world.GetCurrentWorldArea();

            worldArea.m_mobsMirror.Clear();

            for (var y = 0; y < 100; y++)
            {
                for (var x = 0; x < 100; x++)
                {
                    var tile = worldArea.GetTile(x, y);
                    tile.m_ground = "GroundGrass".GetHashCode();
                    tile.m_layer = 0;
                    tile.m_objects.Clear();
                    tile.m_mob = null;
                }
            }
        }

        private void GenerateWater()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            var numLakes = 15 + Random.Shared.Next(15);

            for (var i = 0; i < numLakes; i++)
            {
                var xCenter = Random.Shared.Next(100);
                var yCenter = Random.Shared.Next(100);
                var r = 3 + Random.Shared.Next(12);

                for (var y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (var x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (x < 0 || y < 0 || x >= 100 || y >= 100)
                        {
                            continue;
                        }

                        var dx = x - xCenter;
                        var dy = y - yCenter;

                        if (dx * dx + dy * dy <= r * r)
                        {
                            var tile = worldArea.GetTile(x, y);
                            tile.m_ground = "GroundWater".GetHashCode();
                        }
                    }
                }
            }
        }

        private void GenerateForests()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            var numForests = 70 + Random.Shared.Next(25);

            for (var i = 0; i < numForests; i++)
            {
                var xCenter = Random.Shared.Next(100);
                var yCenter = Random.Shared.Next(100);
                var r = 7 + Random.Shared.Next(17);

                for (var y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (var x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (x < 0 || y < 0 || x >= 100 || y >= 100)
                        {
                            continue;
                        }

                        var dx = x - xCenter;
                        var dy = y - yCenter;

                        if (dx * dx + dy * dy <= r * r)
                        {
                            var tile = worldArea.GetTile(x, y);
                            tile.m_objects.Clear();
                            if (tile.m_ground == "GroundGrass".GetHashCode())
                            {
                                if (dx * dx + dy * dy > (r - 3) * (r - 3))
                                {
                                    tile.m_layer = "LayerForestSparse".GetHashCode();
                                }
                                else if (dx * dx + dy * dy > (r - 6) * (r - 6))
                                {
                                    tile.m_layer = "LayerForestMedium".GetHashCode();
                                }
                                else
                                {
                                    tile.m_layer = "LayerForestThick".GetHashCode();
                                    if (Random.Shared.Next(100) < 5)
                                    {
                                        tile.m_objects.Clear();
                                        tile.m_objects.Add("ObjectTree1");
                                    }
                                    else if (Random.Shared.Next(100) < 5)
                                    {
                                        tile.m_objects.Clear();
                                        tile.m_objects.Add("ObjectTree2");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void GenerateObjects()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            var numBush1s = 100 + Random.Shared.Next(50);

            for (var i = 0; i < numBush1s; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectBush1");
                }
            }
            var numBush2s = 100 + Random.Shared.Next(50);

            for (var i = 0; i < numBush2s; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectBush2");
                }
            }

            var numPinkFlowers = 100;

            for (var i = 0; i < numPinkFlowers; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectPinkFlower");
                }
            }

            var numStoneBoulders = 100;

            for (var i = 0; i < numStoneBoulders; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectStoneBoulder");
                }
            }

            var numBranches = 100;

            for (var i = 0; i < numBranches; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectBranch");
                }
            }

            var numTallGrasses = 400;

            for (var i = 0; i < numTallGrasses; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground == "GroundGrass".GetHashCode())
                {
                    tile.m_objects.Clear();
                    tile.m_objects.Add("ObjectTallGrass");
                }
            }
        }

        private void GenerateMountains()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            var numMountains = 10 + Random.Shared.Next(10);

            for (var i = 0; i < numMountains; i++)
            {
                var xCenter = Random.Shared.Next(100);
                var yCenter = Random.Shared.Next(100);
                var r = 3 + Random.Shared.Next(7);

                for (var y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (var x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (x < 0 || y < 0 || x >= 100 || y >= 100)
                        {
                            continue;
                        }

                        var dx = x - xCenter;
                        var dy = y - yCenter;

                        if (dx * dx + dy * dy <= r * r)
                        {
                            var tile = worldArea.GetTile(x, y);
                            tile.m_objects.Clear();
                            tile.m_ground = "GroundRock".GetHashCode();
                            tile.m_layer = 0;

                            if (dx * dx + dy * dy <= (r - 2) * (r - 2))
                            {
                                if (dx * dx + dy * dy > (r - 4) * (r - 4))
                                {
                                    tile.m_layer = "LayerMountainSparse".GetHashCode();
                                }
                                else if (dx * dx + dy * dy > (r - 6) * (r - 6))
                                {
                                    tile.m_layer = "LayerMountainMedium".GetHashCode();
                                }
                                else
                                {
                                    tile.m_layer = "LayerMountainThick".GetHashCode();
                                    if (Random.Shared.Next(100) < 10)
                                    {
                                        tile.m_objects.Clear();
                                        tile.m_objects.Add("ObjectStoneBoulder");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void GenerateTrainObjects()
        {
            var worldArea = _.world.GetCurrentWorldArea();

            for (var x = 0; x < 100; x++)
            {
                worldArea.GetTile(x, 50).m_objects.Clear();
                worldArea.GetTile(x, 49).m_ground = "GroundDirt".GetHashCode();
                worldArea.GetTile(x, 50).m_ground = "GroundDirt".GetHashCode();
                worldArea.GetTile(x, 51).m_ground = "GroundDirt".GetHashCode();
                worldArea.GetTile(x, 50).m_objects.Add("ObjectTrainRail");
            }

            worldArea.GetTile(50, 50).m_objects.Add("ObjectTrain");

            for (var x = 51; x < 58; x++)
            {
                worldArea.GetTile(x, 50).m_objects.Add("ObjectTrainWagon");
            }
        }

        private void GenerateMobs()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            var numMobs = 100 + Random.Shared.Next(50);
            var mobIndex = Random.Shared.Next(_.mobIndex.m_properties.Count);
            var mobType = _.mobIndex.m_properties.ElementAt(mobIndex).Key;

            for (var i = 0; i < numMobs; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                if (tile.m_ground != "GroundWater".GetHashCode())
                {
                    var newMob = new Mob(mobType);
                    tile.m_mob = newMob;
                    worldArea.m_mobsMirror.Add(newMob, new(x, y));
                }
            }

            var numRedBirds = 100;

            for (var i = 0; i < numRedBirds; i++)
            {
                var x = Random.Shared.Next(100);
                var y = Random.Shared.Next(100);

                var tile = worldArea.GetTile(x, y);

                var newBird = new Mob("MobRedBird");
                tile.m_mob = newBird;
                worldArea.m_mobsMirror.Add(newBird, new(x, y));
            }
        }
    }
}