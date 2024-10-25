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

            var xHP = 0.04f;
            var yHP = 0.07f;
            var heightHP = 0.03f;
            var widthHPFull = 0.13f;
            var widthHPCurrent = widthHPFull * (float)_.player.m_hp / _.player.m_maxHP;
            _.imageRenderer.DrawImage("Black", xHP, yHP, widthHPFull, heightHP);
            _.imageRenderer.DrawImage("Red", xHP, yHP, widthHPCurrent, heightHP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xHP, yHP, widthHPFull, heightHP);

            var xSP = 0.04f;
            var ySP = 0.11f;
            var heightSP = 0.03f;
            var widthSPFull = 0.13f;
            var widthSPCurrent = widthSPFull * (float)_.player.m_sp / _.player.m_maxSP;
            _.imageRenderer.DrawImage("Black", xSP, ySP, widthSPFull, heightSP);
            _.imageRenderer.DrawImage("Yellow", xSP, ySP, widthSPCurrent, heightSP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xSP, ySP, widthSPFull, heightSP);

            var xMP = 0.04f;
            var yMP = 0.15f;
            var heightMP = 0.03f;
            var widthMPFull = 0.13f;
            var widthMPCurrent = widthMPFull * (float)_.player.m_mp / _.player.m_maxMP;
            _.imageRenderer.DrawImage("Black", xMP, yMP, widthMPFull, heightMP);
            _.imageRenderer.DrawImage("Blue", xMP, yMP, widthMPCurrent, heightMP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xMP, yMP, widthMPFull, heightMP);
        }
    }
}
