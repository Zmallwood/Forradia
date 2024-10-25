namespace YrradiaSDL2.Game.Input.Keyboard
{
    public class KeyboardInput
    {
        private HashSet<Keycode> m_pressedKeys = new HashSet<Keycode>();

        public void Reset()
        {
            m_pressedKeys.Clear();
        }

        public void RegisterKeyPress(Keycode key)
        {
            m_pressedKeys.Add(key);
        }

        public void RegisterKeyRelease(Keycode key)
        {
            m_pressedKeys.Remove(key);
        }

        public bool KeyIsPressed(Keycode key)
        {
            return m_pressedKeys.Contains(key);
        }

        public bool AnyKeyIsPressed()
        {
            return m_pressedKeys.Count > 0;
        }
    }
}
