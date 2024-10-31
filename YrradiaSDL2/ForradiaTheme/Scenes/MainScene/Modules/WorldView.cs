namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    enum Comps
    {
        EQ,
        GT,
        LT,
        GTEQ,
        LTEQ,
        ANY
    }


    public class WorldView
    {
        public void Render()
        {
            var sourceRect = new Rect(0, 0, 60, 60);
            var worldArea = _.world.GetCurrentWorldArea();
            var player = _.player;
            var gridSize = _.tileGridMath.GetTileGridSize();
            var tileSize = _.tileGridMath.GetTileSize();
            for (var y = 0; y < gridSize.Height; y++)
            {
                for (var x = 0; x < gridSize.Width; x++)
                {
                    var area = new Rectangle(x * tileSize, y * tileSize, tileSize, tileSize);

                    var crdX = player.m_position.X - (gridSize.Width - 1) / 2 + x;
                    var crdY = player.m_position.Y - (gridSize.Height - 1) / 2 + y;

                    if (crdX < 0 || crdY < 0 || crdX >= 100 || crdY >= 100) { continue; }

                    var tile = worldArea.GetTile(crdX, crdY);
                    var ground = tile.m_ground;

                    if (ground == "GroundWater".GetHashCode())
                    {
                        var animIndex = ((Environment.TickCount / 4 + crdX * crdY) % 1200) / 400;

                        ground = ("GroundWater_" + animIndex).GetHashCode();
                    }


                    _.imageRenderer.DrawImage(ground, area.X, area.Y, area.Width, area.Height);


                    if (tile.m_layer != 0)
                    {
                        _.imageRenderer.DrawImage(tile.m_layer, area.X, area.Y, area.Width, area.Height);
                    }

                    var elev = tile.m_elevation;
                    var elevN = elev;
                    var elevNE = elev;
                    var elevE = elev;
                    var elevSE = elev;
                    var elevS = elev;
                    var elevSW = elev;
                    var elevW = elev;
                    var elevNW = elev;

                    if (crdX > 0)
                        elevW = worldArea.GetTile(crdX - 1, crdY).m_elevation;

                    if (crdY > 0)
                        elevN = worldArea.GetTile(crdX, crdY - 1).m_elevation;

                    if (crdX < 100 - 1)
                        elevE = worldArea.GetTile(crdX + 1, crdY).m_elevation;

                    if (crdY < 100 - 1)
                        elevS = worldArea.GetTile(crdX, crdY + 1).m_elevation;

                    if (crdX < 100 - 1 && crdY > 0)
                        elevNE = worldArea.GetTile(crdX + 1, crdY - 1).m_elevation;

                    if (crdX < 100 - 1 && crdY < 100 - 1)
                        elevSE = worldArea.GetTile(crdX + 1, crdY + 1).m_elevation;

                    if (crdX > 0 && crdY < 100 - 1)
                        elevSW = worldArea.GetTile(crdX - 1, crdY + 1).m_elevation;

                    if (crdX > 0 && crdY > 0)
                        elevNW = worldArea.GetTile(crdX - 1, crdY - 1).m_elevation;


                    var elevDiffs = new int[][] {
                        new int[] {elevNW - elev, elevN - elev, elevNE - elev},
                        new int[] {elevW - elev, elev - elev, elevE - elev},
                        new int[] {elevSW - elev, elevS - elev, elevSE - elev},
                    };

                    if (tile.m_ground != "GroundWater".GetHashCode())
                    {

                        var elevDiffsSWComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.GTEQ, Comps.GTEQ},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.GT},
                            new Comps[] { Comps.ANY, Comps.LTEQ, Comps.LTEQ }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsSWComp))
                        {
                            _.imageRenderer.DrawImage("ElevSW", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsSComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.ANY},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.EQ},
                            new Comps[] { Comps.LTEQ, Comps.LT, Comps.LT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsSComp))
                        {
                            _.imageRenderer.DrawImage("ElevS", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsSEComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.LTEQ},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.LT},
                            new Comps[] { Comps.LT, Comps.LT, Comps.LT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsSEComp))
                        {
                            _.imageRenderer.DrawImage("ElevSE", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsEComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.LTEQ},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.LT},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.LT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsEComp))
                        {
                            _.imageRenderer.DrawImage("ElevE", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsNEComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.LTEQ, Comps.LTEQ},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.LTEQ},
                            new Comps[] { Comps.ANY, Comps.GT, Comps.LTEQ }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsNEComp))
                        {
                            _.imageRenderer.DrawImage("ElevNE", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsNComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.ANY},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.EQ},
                            new Comps[] { Comps.ANY, Comps.GT, Comps.GT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsNComp))
                        {
                            _.imageRenderer.DrawImage("ElevN", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsNWComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.ANY},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.EQ},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.GT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsNWComp))
                        {
                            _.imageRenderer.DrawImage("ElevNW", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsNWInvComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.ANY},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.GT},
                            new Comps[] { Comps.GTEQ, Comps.GT, Comps.GT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsNWInvComp))
                        {
                            _.imageRenderer.DrawImage("ElevNWInv", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsWComp = new Comps[][]
                        {
                            new Comps[] { Comps.ANY, Comps.ANY, Comps.ANY},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.GT},
                            new Comps[] { Comps.ANY, Comps.EQ, Comps.GT }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsWComp))
                        {
                            _.imageRenderer.DrawImage("ElevW", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsSWInvComp = new Comps[][]
                        {
                            new Comps[] { Comps.LTEQ, Comps.LTEQ, Comps.LTEQ},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.GTEQ},
                            new Comps[] { Comps.LTEQ, Comps.LT, Comps.GTEQ }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsSWInvComp))
                        {
                            _.imageRenderer.DrawImage("ElevSWInv", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsSEInvComp = new Comps[][]
                        {
                            new Comps[] { Comps.LT, Comps.LT, Comps.LT},
                            new Comps[] { Comps.LT, Comps.EQ, Comps.EQ},
                            new Comps[] { Comps.LT, Comps.EQ, Comps.LTEQ }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsSEInvComp))
                        {
                            _.imageRenderer.DrawImage("ElevSEInv", area.X, area.Y, area.Width, area.Height);
                        }

                        var elevDiffsNEInvComp = new Comps[][]
                        {
                            new Comps[] { Comps.LTEQ, Comps.LTEQ, Comps.LT},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.LT},
                            new Comps[] { Comps.LTEQ, Comps.EQ, Comps.EQ }
                        };

                        if (CompElevDiffs(elevDiffs, elevDiffsNEInvComp))
                        {
                            _.imageRenderer.DrawImage("ElevNEInv", area.X, area.Y, area.Width, area.Height);
                        }
                    }

                    if (tile.m_ground == "GroundWater".GetHashCode())
                    {
                        if (crdX > 0)
                        {
                            if (worldArea.GetTile(crdX - 1, crdY).m_ground != "GroundWater".GetHashCode())
                            {
                                _.imageRenderer.DrawImage("EdgeWest", area.X, area.Y, area.Width, area.Height);
                            }
                        }

                        if (crdY > 0)
                        {
                            if (worldArea.GetTile(crdX, crdY - 1).m_ground != "GroundWater".GetHashCode())
                            {
                                _.imageRenderer.DrawImage("EdgeNorth", area.X, area.Y, area.Width, area.Height);
                            }
                        }

                        if (crdX < 100 - 1)
                        {
                            if (worldArea.GetTile(crdX + 1, crdY).m_ground != "GroundWater".GetHashCode())
                            {
                                _.imageRenderer.DrawImage("EdgeEast", area.X, area.Y, area.Width, area.Height);
                            }
                        }

                        if (crdY < 100 - 1)
                        {
                            if (worldArea.GetTile(crdX, crdY + 1).m_ground != "GroundWater".GetHashCode())
                            {
                                _.imageRenderer.DrawImage("EdgeSouth", area.X, area.Y, area.Width, area.Height);
                            }
                        }

                    }

                    if (crdX == _.extraGUIActionMenu.m_clickedCoordinate.X && crdY == _.extraGUIActionMenu.m_clickedCoordinate.Y)
                    {
                        _.imageRenderer.DrawImage("ClickedTile", area.X, area.Y, area.Width, area.Height);
                    }

                    if (crdX == _.tileHovering.m_hoveredCoordinate.X && crdY == _.tileHovering.m_hoveredCoordinate.Y)
                    {
                        _.imageRenderer.DrawImage("HoveredTile", area.X, area.Y, area.Width, area.Height);
                    }

                    foreach (var tangibleObject in tile.m_objects.All())
                    {
                        var objectType = tangibleObject.m_type;
                        if (objectType == "ObjectTallGrass".GetHashCode())
                        {
                            var animIndex = ((Environment.TickCount + crdX * crdY) % 1200) / 300;
                            objectType = ("ObjectTallGrass_" + animIndex).GetHashCode();
                        }
                        else if (objectType == "ObjectTrain".GetHashCode())
                        {
                            var animIndex = ((Environment.TickCount + crdX * crdY) % 1200) / 400;
                            objectType = ("ObjectTrain_" + animIndex).GetHashCode();
                        }
                        _.imageRenderer.DrawImage(objectType, area.X, area.Y, area.Width, area.Height);
                    }

                    if (crdX == _.player.m_position.X && crdY == _.player.m_position.Y)
                    {
                        _.imageRenderer.DrawImage("Player", area.X, area.Y, area.Width, area.Height);
                    }

                    if (tile.m_mob != null)
                    {
                        var mobType = tile.m_mob.m_type;
                        if (mobType == "MobRedBird".GetHashCode())
                        {
                            var animIndex = ((Environment.TickCount + crdX * crdY) % 800) / 400;
                            mobType = ("MobRedBird_" + animIndex).GetHashCode();
                        }
                        _.imageRenderer.DrawImage(mobType, area.X, area.Y, area.Width, area.Height);
                        if (!_.mobIndex.MobIsUnlabeled(tile.m_mob.m_type))
                        {
                            _.textRenderer.DrawString(_.mobIndex.GetMobName(tile.m_mob.m_type) + " Lvl " + _.mobIndex.GetMobLevel(tile.m_mob.m_type), new(area.X + area.Width / 2, area.Y - area.Height / 2), Colors.lightPink, FontSizes._18, true);
                        }
                    }

                    var dx = crdX - _.player.m_position.X;
                    var dy = crdY - _.player.m_position.Y;

                    var sightDist = Math.Sqrt(dx * dx + dy * dy) - 10;

                    var sightFadeAmount = (int)(sightDist / 2);
                    sightFadeAmount /= 2;
                    sightFadeAmount *= 2;

                    for (var i = 0; i < sightFadeAmount; i++)
                    {
                        _.imageRenderer.DrawImage("SightFade", area.X, area.Y, area.Width, area.Height);
                    }
                }
            }
        }

        private bool CompElevDiffs(int[][] lhs, Comps[][] comps)
        {
            var results = new bool[3,3];

            for (var x = 0; x < 3; x++)
            {
                for (var y = 0; y < 3; y++)
                {
                    switch (comps[x][y])
                    {
                        case Comps.EQ:
                            results[x, y] = lhs[x][y] == 0;
                            break;
                        case Comps.GT:
                            results[x, y] = lhs[x][y] > 0;
                            break;
                        case Comps.LT:
                            results[x, y] = lhs[x][y] < 0;
                            break;
                        case Comps.GTEQ:
                            results[x, y] = lhs[x][y] >= 0;
                            break;
                        case Comps.LTEQ:
                            results[x, y] = lhs[x][y] <= 0;
                            break;
                        case Comps.ANY:
                            results[x, y] =  true;
                            break;
                    }

                }
            }

            if (results[0,0] && results[0, 1] && results[0, 2] &&
                results[1, 0] && results[1, 1] && results[1, 2] &&
                results[2, 0] && results[2, 1] && results[2,2])
                return true;

            return false;
        }
    }
}
