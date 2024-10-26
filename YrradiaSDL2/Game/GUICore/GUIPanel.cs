namespace YrradiaSDL2.Game.GUICore
{
    public class GUIPanel : GUIComponent
    {
        protected SizeF? m_size;

        public GUIPanel(PointF position, SizeF? size = null) : base(position)
        {
            m_size = size;
        }
    }
}
