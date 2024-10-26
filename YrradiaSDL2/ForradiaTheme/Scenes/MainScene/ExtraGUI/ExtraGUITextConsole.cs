
namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUITextConsole
    {
        private RectangleF m_bounds = new(0, 0.7f, 0.4f, 0.31f);
        private const float k_lineHeight = 0.03f;

        public void Render()
        {
            _.imageRenderer.DrawImage("GUITextConsoleBackground", m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);

            var row = 0;
            foreach (var textLine in _.textOut.m_text)
            {
                _.textRenderer.DrawString(textLine, new PointF(m_bounds.X + 0.01f, m_bounds.Y + 0.03f + row * k_lineHeight), Colors.wheat);
                row++;
            }
        }
    }
}
