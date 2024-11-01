namespace YrradiaSDL2.Game.Input.Mouse
{
    public class MouseButton
    {
        private bool m_pressed = false;
        private bool m_hasBeenFired = false;
        private bool m_hasBeenReleased = false;
        private int m_ticksLastClick = 0;
        private bool m_hasBeenDoubleClicked = false;
        private const int k_doubleClickSpeed = 300;

        public void RegisterPress()
        {
            m_pressed = true;
            m_hasBeenFired = true;
            m_hasBeenReleased = false;
            if (Environment.TickCount - m_ticksLastClick < k_doubleClickSpeed)
            {
                m_hasBeenDoubleClicked = true;
            }
            else
            {
                m_hasBeenDoubleClicked = false;
            }
            m_ticksLastClick = Environment.TickCount;
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

        public bool GetHasBeenDoubleClickedLeaveResult()
        {
            return m_hasBeenDoubleClicked;
        }

        public bool GetHasBeenDoubleClickedPickResult()
        {
            var result = m_hasBeenDoubleClicked;
            m_hasBeenDoubleClicked = false;
            return result;
        }
    }
}
