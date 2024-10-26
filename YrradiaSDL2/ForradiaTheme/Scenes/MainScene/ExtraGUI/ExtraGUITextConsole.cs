
namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUITextConsole
    {
        private RectangleF m_bounds = new(0, 0.8f, 0.3f, 0.21f);
        private const float k_lineHeight = 0.03f;

        public void Render()
        {
            _.imageRenderer.DrawImage("GUITextConsoleBackground", m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);

            var row = 0;
            foreach (var textLine in _.textOut.m_text)
            {
                _.textRenderer.DrawString(textLine, new PointF(m_bounds.X + 0.005f, m_bounds.Y + 0.02f + row * k_lineHeight), Colors.gold, FontSizes._18);
                row++;
            }
        }
    }
}
