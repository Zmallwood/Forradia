namespace YrradiaSDL2.Game.Graphics
{
    public class SDLDevice
    {
        public Window m_window = 0;
        public Renderer m_renderer = 0;
        private Texture m_texture;
        private Size m_origCanvasSize;

        public void Initialize()
        {
            SDL.Init(SdlInitFlags.Everything);

            m_window = SDL.CreateWindow("Yrradia", SDL.WINDOWPOS_CENTERED, SDL.WINDOWPOS_CENTERED, 0, 0, WindowFlags.FullscreenDesktop);
            m_renderer = SDL.CreateRenderer(m_window, -1, RendererFlags.Accelerated | RendererFlags.TargetTexture);
            var desktopResolution = _.canvasUtilities.GetDesktopResolution();
            var scaledWidth = (int)(desktopResolution.Width / _.gameProperties.m_resolutionScaleDown);
            var scaledHeight = (int)(desktopResolution.Height / _.gameProperties.m_resolutionScaleDown);
            m_texture = SDL.CreateTexture(m_renderer, 0, TextureAccess.Target, scaledWidth, scaledHeight);
            m_origCanvasSize = _.canvasUtilities.GetCanvasSize();
            SDL.SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "best");
            SDL.SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        }

        public void Destroy()
        {
            SDL.DestroyRenderer(m_renderer);
            SDL.DestroyWindow(m_window);
            SDL.Quit();
        }

        public void ClearCanvas()
        {
            SDL.SetRenderTarget(m_renderer, m_texture);
            SDL.RenderClear(m_renderer);
        }

        public void PresentCanvas()
        {
            SDL.SetRenderTarget(m_renderer, 0);
            var desktopResolution = _.canvasUtilities.GetDesktopResolution();
            var scaledWidth = (int)(desktopResolution.Width / _.gameProperties.m_resolutionScaleDown);
            var scaledHeight = (int)(desktopResolution.Height / _.gameProperties.m_resolutionScaleDown);
            var sourceRect = new Rect(0, 0, scaledWidth, scaledHeight);
            var destRect = new Rect(0, 0, desktopResolution.Width, desktopResolution.Height);
            SDL.RenderCopy(m_renderer, m_texture, ref sourceRect, ref destRect);
            SDL.RenderPresent(m_renderer);
        }
    }
}
