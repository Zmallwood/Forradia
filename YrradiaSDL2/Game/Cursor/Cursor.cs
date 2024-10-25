namespace YrradiaSDL2.Game.Cursor
{
    public class Cursor
    {
        private const float k_cursorSize = 0.02f;
        private CursorTypes m_currentCursorType = CursorTypes.Default;
        private Dictionary<CursorTypes, string> m_cursorImageNames = new
        () {
            { CursorTypes.Default, "CursorDefault" },
            { CursorTypes.Hovering, "CursorHovering" },
            { CursorTypes.Attack, "CursorAttack" }
        };

        public void HideSystemCursor()
        {
            SDL.ShowCursor(0);
        }

        public void ResetType()
        {
            m_currentCursorType = CursorTypes.Default;
        }

        public void SetToHovering()
        {
            m_currentCursorType = CursorTypes.Hovering;
        }

        public void SetToAttack()
        {
            m_currentCursorType = CursorTypes.Attack;
        }

        public void Render()
        {
            var mousePositionF = _.mouseUtilities.GetMousePositionF();
            var cursorWidth = k_cursorSize;
            var cursorHeight = _.canvasUtilities.ConvertWidthToHeight(cursorWidth);
            var imageName = m_cursorImageNames[m_currentCursorType];
            _.imageRenderer.DrawImage(imageName, mousePositionF.X - cursorWidth, mousePositionF.Y - cursorHeight, cursorWidth * 2, cursorHeight  * 2);
        }
    }
}
