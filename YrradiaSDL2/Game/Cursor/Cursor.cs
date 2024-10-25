namespace YrradiaSDL2.Game.Cursor
{
    public class Cursor
    {
        private const int k_cursorSize = 30;

        public void HideSystemCursor()
        {
            SDL.ShowCursor(0);
        }

        public void Render()
        {
            var mousePosition = _.mouseUtilities.GetMousePosition();
            _.imageRenderer.DrawImage("CursorDefault", mousePosition.X, mousePosition.Y, (int)(k_cursorSize / _.gameProperties.m_resolutionScaleDown), (int)(k_cursorSize / _.gameProperties.m_resolutionScaleDown));
        }
    }
}
