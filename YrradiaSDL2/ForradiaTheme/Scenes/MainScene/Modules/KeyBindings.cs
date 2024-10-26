namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class KeyBindings
    {
        public void Update()
        {
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.C))
            {
                _.mainScene.m_windowCharacter?.ToggleVisibility();
            }
            else if (_.keyboardInput.KeyIsPressedPickResult(Keycode.B))
            {
                _.mainScene.m_windowInventory?.ToggleVisibility();
            }
        }
    }
}
