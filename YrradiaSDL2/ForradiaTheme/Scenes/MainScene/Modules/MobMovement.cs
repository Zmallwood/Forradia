namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class MobMovement
    {
        public void Update()
        {
            var worldArea = _.world.GetCurrentWorldArea();

            var mobsMirrorCopy = new Dictionary<Mob, System.Drawing.Point>(worldArea.m_mobsMirror);

            foreach (var entry in worldArea.m_mobsMirror)
            {
                var mob = entry.Key;
                var crd = entry.Value;

                if (mob.m_destination == new System.Drawing.Point(-1, -1))
                {
                    mob.ResetSpeed();
                    do
                    {
                        var dstnX = crd.X + Random.Shared.Next(12) - Random.Shared.Next(12);
                        var dstnY = crd.Y + Random.Shared.Next(12) - Random.Shared.Next(12);
                        mob.m_destination = new(dstnX, dstnY);
                    } while (mob.m_destination == crd);
                    mob.m_moveStartCrd = crd;
                }
                else
                {
                    if (Environment.TickCount > mob.m_ticksLastSpeedChange + 100)
                    {
                        var deltaX = mob.m_destination.X - crd.X;
                        var deltaY = mob.m_destination.Y - crd.Y;
                        var deltaR = Math.Sqrt(deltaX * deltaX + deltaY * deltaY);
                        var initialDeltaX = mob.m_destination.X - mob.m_moveStartCrd.X;
                        var initialDeltaY = mob.m_destination.Y - mob.m_moveStartCrd.Y;
                        var deltaInitialR = Math.Sqrt(initialDeltaX * initialDeltaX + initialDeltaY * initialDeltaY);
                        if (deltaR <= 3 && (deltaX < initialDeltaX / 2 && deltaY < initialDeltaY / 2))
                        {
                            mob.Decelerate();
                            if (mob.m_movementSpeed == 0.0f)
                            {
                                mob.m_destination = new(-1, -1);
                            }
                        }
                        else
                        {
                            mob.Accelerate();
                        }
                        mob.m_ticksLastSpeedChange = Environment.TickCount;
                    }
                    var dstn = mob.m_destination;
                    var dx = dstn.X - crd.X;
                    var dy = dstn.Y - crd.Y;

                    if (dx != 0 || dy != 0)
                        mob.StopMove();

                    if (dx < 0)
                        mob.MoveWest();

                    if (dx > 0)
                        mob.MoveEast();

                    if (dy < 0)
                        mob.MoveNorth();

                    if (dy > 0)
                        mob.MoveSouth();

                    if (Environment.TickCount > mob.m_ticksLastMove + 1000 / mob.m_movementSpeed)
                    {
                        if (dx != 0 || dy != 0)
                        {
                            var newX = crd.X + mob.m_movementDirection.X;
                            var newY = crd.Y + mob.m_movementDirection.Y;

                            if (newX < 0 || newY < 0 || newX >= 100 || newY >= 100)
                            {
                                mob.m_destination = new(-1, -1);
                                continue;
                            }

                            if (worldArea.GetTile(newX, newY).m_ground == "GroundWater".GetHashCode()
                                && !_.mobIndex.MobIsFlying(mob.m_type))
                            {
                                mob.m_destination = new(-1, -1);
                                continue;
                            }

                            if (worldArea.GetTile(newX, newY).m_mob != null)
                            {
                                mob.m_destination = new(-1, -1);
                                continue;
                            }

                            if (newX == _.player.m_position.X && newY == _.player.m_position.Y)
                            {
                                mob.m_destination = new(-1, -1);
                                continue;
                            }

                            mobsMirrorCopy.Remove(mob);
                            worldArea.GetTile(crd.X, crd.Y).m_mob = null;
                            worldArea.GetTile(newX, newY).m_mob = mob;
                            mobsMirrorCopy.Add(mob, new(newX, newY));

                            if (mob.m_destination == new System.Drawing.Point(newX, newY))
                            {
                                mob.m_destination = new(-1, -1);
                            }

                            mob.m_ticksLastMove = Environment.TickCount;
                        }
                    }
                }
            }

            worldArea.m_mobsMirror = mobsMirrorCopy;
        }
    }
}
