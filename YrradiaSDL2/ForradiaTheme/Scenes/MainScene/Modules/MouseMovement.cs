namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class MouseMovement
    {
        public void Update()
        {
            if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
            {
                var destination = _.tileHovering.m_hoveredCoordinate;
                _.player.m_destination = destination;
            }

            if (_.player.m_destination != new System.Drawing.Point(-1, -1))
            {
                if (Environment.TickCount > _.player.m_ticksLastSpeedChange + 100)
                {
                    _.player.Accelerate();
                    _.player.m_ticksLastSpeedChange = Environment.TickCount;
                }

                var dx = _.player.m_destination.X - _.player.m_position.X;
                var dy = _.player.m_destination.Y - _.player.m_position.Y;

                if (dx < 0)
                {
                    _.player.MoveWest();
                }

                if (dy < 0)
                {
                    _.player.MoveNorth();
                }

                if (dx > 0)
                {
                    _.player.MoveEast();
                }

                if (dy > 0)
                {
                    _.player.MoveSouth();
                }

                if (dx == 0 && dy == 0)
                {
                    _.player.m_destination = new(-1, -1);
                    _.player.ResetMovementSpeed();
                }
            }
            else
            {
                if (Environment.TickCount > _.player.m_ticksLastSpeedChange + 100)
                {
                    _.player.Decelerate();
                    _.player.m_ticksLastSpeedChange = Environment.TickCount;
                }
            }
        }
    }
}
