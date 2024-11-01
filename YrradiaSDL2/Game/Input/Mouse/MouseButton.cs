namespace YrradiaSDL2.Game.Input.Mouse
{
    public class MouseButton
    {
        private bool m_pressed = false;
        private bool m_hasBeenFired = false;
        private bool m_hasBeenReleased = false;

        public void RegisterPress()
        {
            m_pressed = true;
            m_hasBeenFired = true;
            m_hasBeenReleased = false;
        }

        public void RegisterRelease()
        {
            m_pressed = false;
            m_hasBeenReleased = true;
            m_hasBeenFired = false;
        }

        public bool IsPressed()
        {
            return m_pressed;
        }

        public bool GetHasBeenFiredLeaveResult()
        {
            return m_hasBeenFired;
        }

        public bool GetHasBeenReleasedLeaveResult()
        {
            return m_hasBeenReleased;
        }

        public bool GetHasBeenFiredPickResult()
        {
            var result = m_hasBeenFired;
            m_hasBeenFired = false;
            return result;
        }

        public bool GetHasBeenReleasedPickResult()
        {
            var result = m_hasBeenReleased;
            m_hasBeenReleased = false;
            return result;
        }
    }
}
