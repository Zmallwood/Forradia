namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUIStatusPanel
    {
        private RectangleF m_bounds = new(0, 0, 0.2f, 0.22f);

        public void Render()
        {
            _.imageRenderer.DrawImage("GUIPanelDefaultBackground", m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);
            _.textRenderer.DrawString(_.player.m_name, new PointF(0.01f, 0.015f), Colors.wheat);
            _.textRenderer.DrawString("HP", new PointF(0.01f, 0.06f), Colors.wheat);
            _.textRenderer.DrawString("SP", new PointF(0.01f, 0.1f), Colors.wheat);
            _.textRenderer.DrawString("MP", new PointF(0.01f, 0.14f), Colors.wheat);
        }
    }
}
