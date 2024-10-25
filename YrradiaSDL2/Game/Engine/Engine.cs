namespace YrradiaSDL2.Game.Engine
{
    public class Engine
    {
        private bool m_running = true;

        public void Run()
        {
            _.sdlDevice.Initialize();
            _.sceneManager.InitializeScenes();
            _.imageBank.LoadImages();
            _.cursor.HideSystemCursor();

            while (m_running)
            {
                PollEvents();
                _.cursor.ResetType();
                _.sceneManager.UpdateCurrentScene();
                _.fpsCounter.Update();
                _.sdlDevice.ClearCanvas();
                _.sceneManager.RenderCurrentScene();
                _.fpsCounter.Render();
                _.cursor.Render();
                _.sdlDevice.PresentCanvas();
            }

            _.imageBank.DestroyImages();
            _.textRenderer.DestroyFonts();
            _.sdlDevice.Destroy();
        }

        public void Stop()
        {
            m_running = false;
        }

        private void PollEvents()
        {
            var ev = new Event();

            while (SDL.PollEvent(out ev) != 0)
            {
                switch (ev.Type)
                {
                    case EventType.Quit:
                        m_running = false;
                        return;
                        break;
                    case EventType.KeyDown:
                        _.keyboardInput.RegisterKeyPress(ev.Keyboard.Keysym.Sym);
                        break;
                    case EventType.KeyUp:
                        _.keyboardInput.RegisterKeyRelease(ev.Keyboard.Keysym.Sym);
                        break;
                    case EventType.MouseButtonDown:
                        _.mouseInput.RegisterButtonPress(ev.Button.Button);
                        break;
                    case EventType.MouseButtonUp:
                        _.mouseInput.RegisterButtonRelease(ev.Button.Button);
                        break;
                }
            }
        }
    }
}
