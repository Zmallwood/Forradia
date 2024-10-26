namespace YrradiaSDL2.Game.GUICore
{
    public abstract class GUIWindow : GUIMovablePanel
    {
        private string m_title = string.Empty;

        protected abstract PointF GetInitialPosition();
        protected abstract string GetTitle();
        protected abstract Size GetSize();

        public GUIWindow() : base(new(0.0f, 0.0f), null)
        {
            m_position = GetInitialPosition();
            m_title = GetTitle();
            m_size = GetSize();
            m_visible = false;
        }

        protected override void UpdateDerived()
        {
            base.UpdateDerived();
        }

        protected override void RenderDerived()
        {
            base.RenderDerived();
        }
    }
}
