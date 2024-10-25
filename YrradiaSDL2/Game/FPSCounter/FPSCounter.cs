namespace YrradiaSDL2.Game.FPSCounter
{
    public class FPSCounter
    {
        private int m_fps = 0;
        private int m_framesCount = 0;
        private int m_ticksLastUpdate = 0;
        public void Update()
        {
            if (Environment.TickCount >= m_ticksLastUpdate + 1000)
            {
                m_fps = m_framesCount;
                m_framesCount = 0;
                m_ticksLastUpdate = Environment.TickCount;
            }
            m_framesCount++;
        }

        public void Render()
        {
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            _.textRenderer.DrawString("FPS: " + m_fps, new (canvasSize.Width - 200, 10), Colors.wheat);
        }
    }
}
