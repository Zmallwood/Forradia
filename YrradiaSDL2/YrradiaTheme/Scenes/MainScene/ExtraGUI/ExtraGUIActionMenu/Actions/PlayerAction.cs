namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu.Actions
{
    public abstract class PlayerAction
    {
        public bool m_hovered = false;

        public abstract string GetLabel();
        public abstract void Perform(System.Drawing.Point coordinate);
    }
}
