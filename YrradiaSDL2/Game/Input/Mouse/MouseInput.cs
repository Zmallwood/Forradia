namespace YrradiaSDL2.Game.Input.Mouse
{
    public class MouseInput
    {
        public MouseButton m_leftButton = new();
        public MouseButton m_rightButton = new();

        public void RegisterButtonPress(SDL_Sharp.MouseButton button)
        {
            switch (button)
            {
                case SDL_Sharp.MouseButton.Left:
                    m_leftButton.RegisterPress();
                    break;
                case SDL_Sharp.MouseButton.Right:
                    m_rightButton.RegisterPress();
                    break;
            }
        }

        public void RegisterButtonRelease(SDL_Sharp.MouseButton button)
        {
            switch (button)
            {
                case SDL_Sharp.MouseButton.Left:
                    m_leftButton.RegisterRelease();
                    break;
                case SDL_Sharp.MouseButton.Right:
                    m_rightButton.RegisterRelease();
                    break;
            }
        }

        public bool AnyButtonHasBeenFiredPickResult()
        {
            var leftButtonResult = m_leftButton.GetHasBeenFiredPickResult();
            var rightButtonResult = m_rightButton.GetHasBeenFiredPickResult();
            return leftButtonResult || rightButtonResult;
        }
    }
}
