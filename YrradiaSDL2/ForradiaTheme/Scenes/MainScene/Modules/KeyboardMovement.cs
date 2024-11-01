﻿namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class KeyboardMovement
    {
        public void Update()
        {

            var wPressed = _.keyboardInput.KeyIsPressed(Keycode.W);
            var aPressed = _.keyboardInput.KeyIsPressed(Keycode.A);
            var sPressed = _.keyboardInput.KeyIsPressed(Keycode.S);
            var dPressed = _.keyboardInput.KeyIsPressed(Keycode.D);


            if (wPressed || aPressed || sPressed || dPressed)
                _.player.m_destination = new System.Drawing.Point(-1, -1);

            if (_.player.m_destination != new System.Drawing.Point(-1, -1))
            {
                return;
            }

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
        }
    }
}
