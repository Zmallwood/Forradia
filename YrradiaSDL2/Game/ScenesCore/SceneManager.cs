namespace YrradiaSDL2.Game.ScenesCore
{
    public class SceneManager
    {
        private Dictionary<int, Scene> m_scenes = new Dictionary<int, Scene>();
        private int m_currentScene = 0;

        public void InitializeScenes()
        {
            m_scenes.Add("IntroScene".GetHashCode(), _.introScene);
            m_scenes.Add("MainMenuScene".GetHashCode(), _.mainMenuScene);
            m_scenes.Add("MainScene".GetHashCode(), _.mainScene);
            m_scenes.Add("WorldGenerationScene".GetHashCode(), _.worldGenerationScene);
            GoToScene("IntroScene");
        }

        public void GoToScene(string sceneName)
        {
            m_currentScene = sceneName.GetHashCode();
            _.keyboardInput.Reset();
            m_scenes[m_currentScene].OnEnter();
        }

        public void UpdateCurrentScene()
        {
            if (m_scenes.ContainsKey(m_currentScene))
            {
                m_scenes[m_currentScene].Update();
            }
        }

        public void RenderCurrentScene()
        {
            if (m_scenes.ContainsKey(m_currentScene))
            {
                m_scenes[m_currentScene].Render();
            }
        }
    }
}
