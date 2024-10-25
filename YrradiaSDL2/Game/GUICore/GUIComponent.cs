namespace YrradiaSDL2.Game.GUICore
{
    public class GUIComponent
    {
        private List<GUIComponent> m_components = new();
        protected PointF m_position = new(0,0);
        public bool m_visible = true;

        public void Update()
        {
            if (!m_visible)
            {
                return;
            }

            UpdateDerived();

            foreach (var component in m_components)
            {
                component.Update();
            }
        }

        public void Render()
        {
            if (!m_visible)
            {
                return;
            }

            RenderDerived();

            foreach (var component in m_components)
            {
                component.Render();
            }
        }

        protected virtual void UpdateDerived() { }

        protected virtual void RenderDerived() { }

        public GUIComponent AddComponent(GUIComponent newComponent)
        {
            m_components.Add(newComponent);

            return newComponent;
        }
    }
}
