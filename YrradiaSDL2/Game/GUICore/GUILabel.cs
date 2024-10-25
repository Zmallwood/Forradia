namespace YrradiaSDL2.Game.GUICore
{
    public class GUILabel : GUIComponent
    {
        private string m_text;
        private bool m_centerAligned;
        
        public GUILabel(string text, PointF position, bool centerAligned = false)
        {
            m_text = text;
            m_position = position;
            m_centerAligned = centerAligned;
        }

        protected override void RenderDerived()
        {
            base.RenderDerived();

            _.textRenderer.DrawString(m_text, m_position, Colors.wheat, FontSizes._20, m_centerAligned);
        }
    }
}
