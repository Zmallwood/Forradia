namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUISystemMenu : GUI
    {
        public ExtraGUISystemMenu()
        {
            AddComponent(new GUIButton("Main menu", new PointF(0.5f, 0.3f), () => { _.sceneManager.GoToScene("MainMenuScene"); }, true));
            AddComponent(new GUIButton("Quit", new PointF(0.5f, 0.38f), () => { _.engine.Stop(); }, true));
            AddComponent(new GUIButton("Resume", new PointF(0.5f, 0.5f), () => { ToggleVisibility(); }, true));

            m_visible = false;
        }

        public void ToggleVisibility()
        {
            m_visible = !m_visible;
            _.mainScene.m_paused = m_visible;
        }

        public new void Update()
        {
            if (_.keyboardInput.KeyIsPressedPickResult(Keycode.Escape))
            {
                ToggleVisibility();
            }
            base.Update();
        }

        public new void Render()
        {
            if (m_visible)
            {
                _.imageRenderer.DrawImage("TransparentSteelBlue", 0.0f, 0.0f, 1.0f, 1.0f);
            }
            base.Render();
        }
    }
}
