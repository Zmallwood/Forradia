namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class KeyboardMovement
    {
        public void Update()
        {
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.D1))
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position ).m_elevation++;
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.D2))
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_elevation--;

            var wPressed = _.keyboardInput.KeyIsPressed(Keycode.W);
            var aPressed = _.keyboardInput.KeyIsPressed(Keycode.A);
            var sPressed = _.keyboardInput.KeyIsPressed(Keycode.S);
            var dPressed = _.keyboardInput.KeyIsPressed(Keycode.D);

            if (Environment.TickCount > _.player.m_ticksLastSpeedChange + 100)
            {
                if (wPressed || aPressed || sPressed || dPressed)
                {
                    _.player.Accelerate();
                }
                else
                {
                    _.player.Decelerate();
                }
                _.player.m_ticksLastSpeedChange = Environment.TickCount;
            }

            if (wPressed || aPressed || sPressed || dPressed)
                _.player.StopMove();

            if (wPressed)
                _.player.MoveNorth();

            if (aPressed)
                _.player.MoveWest();

            if (sPressed)
                _.player.MoveSouth();

            if (dPressed)
                _.player.MoveEast();

            if (Environment.TickCount > _.player.m_ticksLastMove + 1000 / _.player.m_movementSpeed)
            {
                _.player.UpdateMovement();

                _.player.m_ticksLastMove = Environment.TickCount;
            }
        }
    }
}
