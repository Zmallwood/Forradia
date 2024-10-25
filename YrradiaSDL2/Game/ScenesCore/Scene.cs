namespace YrradiaSDL2.Game.ScenesCore
{
    public abstract class Scene
    {
        protected GUI m_gui = new();

        public void Update()
        {
            m_gui.Update();
            UpdateDerived();
        }

        public void Render()
        {
            RenderDerived();
            m_gui.Render();
        }

        public virtual void OnEnter() { }

        protected abstract void UpdateDerived();
        protected abstract void RenderDerived();
    }
}
