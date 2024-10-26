namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.Modules
{
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
                        var animIndex = ((Environment.TickCount/4 + crdX * crdY) % 1200) / 400;

                        ground = ("GroundWater_" + animIndex).GetHashCode();
                    }


                    _.imageRenderer.DrawImage(ground, area.X, area.Y, area.Width, area.Height);


                    if (tile.m_layer != 0)
                    {
                        _.imageRenderer.DrawImage(tile.m_layer, area.X, area.Y, area.Width, area.Height);
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
                        _.imageRenderer.DrawImage(tangibleObject.m_type, area.X, area.Y, area.Width, area.Height);
                    }

                    if (tile.m_mob != null)
                    {
                        var mobType = tile.m_mob.m_type;
                        _.imageRenderer.DrawImage(mobType, area.X, area.Y, area.Width, area.Height);
                        _.textRenderer.DrawString(_.mobProperties.GetMobName(mobType) + " Lvl " + _.mobProperties.GetMobLevel(mobType), new(area.X + area.Width/2, area.Y - area.Height/2), Colors.wheat, FontSizes._18, true);
                    }

                    if (crdX == _.player.m_position.X && crdY == _.player.m_position.Y)
                    {
                        _.imageRenderer.DrawImage("Player", area.X, area.Y, area.Width, area.Height);
                    }

                    var dx = crdX - _.player.m_position.X;
                    var dy = crdY - _.player.m_position.Y;

                    var sightDist = Math.Sqrt(dx*dx + dy*dy) - 10;

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
    }
}
