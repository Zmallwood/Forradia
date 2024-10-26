namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUIStatusPanel
    {
        private RectangleF m_bounds = new(0, 0, 0.2f, 0.22f);

        public void Render()
        {
            _.imageRenderer.DrawImage("GUIStatusPanelBackground", m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);
            _.textRenderer.DrawString(_.player.m_name, new PointF(0.01f, 0.015f), Colors.gold);
            _.textRenderer.DrawString("HP", new PointF(0.01f, 0.06f), Colors.wheat, FontSizes._18);
            _.textRenderer.DrawString("SP", new PointF(0.01f, 0.1f), Colors.wheat, FontSizes._18);
            _.textRenderer.DrawString("MP", new PointF(0.01f, 0.14f), Colors.wheat, FontSizes._18);

            var xHP = 0.04f;
            var yHP = 0.07f;
            var heightHP = 0.02f;
            var widthHPFull = 0.13f;
            var widthHPCurrent = widthHPFull * (float)_.player.m_hp / _.player.m_maxHP;
            _.imageRenderer.DrawImage("TransparentBlack", xHP, yHP, widthHPFull, heightHP);
            _.imageRenderer.DrawImage("TransparentRed", xHP, yHP, widthHPCurrent, heightHP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xHP, yHP, widthHPFull, heightHP);

            var xSP = 0.04f;
            var ySP = 0.11f;
            var heightSP = 0.02f;
            var widthSPFull = 0.13f;
            var widthSPCurrent = widthSPFull * (float)_.player.m_sp / _.player.m_maxSP;
            _.imageRenderer.DrawImage("TransparentBlack", xSP, ySP, widthSPFull, heightSP);
            _.imageRenderer.DrawImage("TransparentYellow", xSP, ySP, widthSPCurrent, heightSP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xSP, ySP, widthSPFull, heightSP);

            var xMP = 0.04f;
            var yMP = 0.15f;
            var heightMP = 0.02f;
            var widthMPFull = 0.13f;
            var widthMPCurrent = widthMPFull * (float)_.player.m_mp / _.player.m_maxMP;
            _.imageRenderer.DrawImage("TransparentBlack", xMP, yMP, widthMPFull, heightMP);
            _.imageRenderer.DrawImage("TransparentBlue", xMP, yMP, widthMPCurrent, heightMP);
            _.imageRenderer.DrawImage("BlackMeterBorders", xMP, yMP, widthMPFull, heightMP);
        }
    }
}
