namespace YrradiaSDL2.YrradiaTheme.Scenes.IntroScene
{
    public class IntroScene : Scene
    {
        private GUIComponent m_labelStartText;

        public override void Initialize()
        {
            m_labelStartText = m_gui.AddComponent(new GUILabel("Press to start", new(0.5f, 0.55f), true));
        }

        protected override void UpdateDerived()
        {
            if (_.mouseInput.AnyButtonHasBeenFiredPickResult() || _.keyboardInput.AnyKeyIsPressed())
            {
                _.sceneManager.GoToScene("MainMenuScene");
            }

            m_labelStartText.m_visible = Environment.TickCount % 800 > 400;
        }

        protected override void RenderDerived()
        {
            _.imageRenderer.DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
            _.imageRenderer.DrawImage("ForradiaLogo", 0.4f, 0.25f, 0.2f, 0.1f);
        }
    }
}
