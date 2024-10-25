namespace YrradiaSDL2.YrradiaTheme.Scenes.MainMenuScene
{
    public class MainMenuScene : Scene
    {
        public MainMenuScene()
        {
            m_gui.AddComponent(new GUIButton("New game", new(0.5f, 0.33f), new(() => { _.sceneManager.GoToScene("WorldGenerationScene"); }), true));
            m_gui.AddComponent(new GUIButton("Quit", new(0.5f, 0.45f), new(() => { _.engine.Stop(); }), true));
        }

        protected override void UpdateDerived()
        {
        }

        protected override void RenderDerived()
        {
            _.imageRenderer.DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
            _.imageRenderer.DrawImage("ForradiaLogo", 0.45f, 0.15f, 0.1f, 0.05f);
        }
    }
}
