namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class KeyBindings
    {
        public void Update()
        {
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.D1))
            {
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_elevation++;
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_layer = "LayerForestThick".GetHashCode();
            }
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.D2))
            {
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_elevation--;
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_layer = "LayerForestThick".GetHashCode();
            }

            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.D3))
            {
                _.world.GetCurrentWorldArea().GetTile(_.player.m_position).m_layer = "LayerForestThick".GetHashCode();
            }


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
