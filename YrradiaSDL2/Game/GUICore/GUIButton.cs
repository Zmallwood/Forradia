using System.Drawing;

namespace YrradiaSDL2.Game.GUICore
{
    public class GUIButton : GUIComponent
    {
        private string m_text;
        private bool m_centerAligned;
        private string m_backgroundImage;
        private string m_backgroundHoveredImage;
        private SizeF? m_size;
        private bool m_hovered = false;
        private Action m_action;

        public GUIButton(string text,
            PointF position,
            Action action,
            bool centerAligned = false,
            SizeF? size = null,
            string backgroundImage = "GUIButtonDefaultBackground",
            string backgroundHoveredImage = "GUIButtonDefaultBackgroundHovered")
        {
            m_text = text;
            m_position = position;
            m_action = action;
            m_backgroundImage = backgroundImage;
            m_backgroundHoveredImage = backgroundHoveredImage;
            m_centerAligned = centerAligned;
            m_size = size;
        }

        private SizeF GetSize()
        {
            return m_size != null ? (SizeF)m_size : new SizeF(0.14f, 0.07f);
        }

        protected override void UpdateDerived()
        {
            base.UpdateDerived();
            var finalSize = m_size == null ? GetSize() : (SizeF)m_size;
            var finalX = m_position.X - (m_centerAligned ? finalSize.Width / 2 : 0);
            var finalY = m_position.Y - (m_centerAligned ? finalSize.Height / 2 : 0);
            var mousePositionF = _.mouseUtilities.GetMousePositionF();
            var area = new RectangleF(finalX, finalY, finalSize.Width, finalSize.Height);
            m_hovered = area.Contains(mousePositionF);
            if (m_hovered)
            {
                _.cursor.SetToHovering();
                if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
                {
                    m_action();
                }
            }
        }

        protected override void RenderDerived()
        {
            base.RenderDerived();
            var finalSize = GetSize();
            var finalX = m_position.X - (m_centerAligned ? finalSize.Width/2 : 0);
            var finalY = m_position.Y - (m_centerAligned ? finalSize.Height/2 : 0);
            var imageName = m_hovered ? m_backgroundHoveredImage : m_backgroundImage;
            _.imageRenderer.DrawImage(imageName, finalX, finalY, finalSize.Width, finalSize.Height);

            var finalTextX = finalX + finalSize.Width / 2;
            var finalTextY = finalY + finalSize.Height / 2;

            _.textRenderer.DrawString(m_text, new PointF(finalTextX, finalTextY), Colors.wheat, FontSizes._20, true);
        }
    }
}
