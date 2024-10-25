namespace YrradiaSDL2.Common
{
    public class MouseUtilities
    {
        public System.Drawing.Point GetMousePosition()
        {
            int x;
            int y;
            SDL.GetMouseState(out x, out y);
            var scaledX = (int)(x/_.gameProperties.m_resolutionScaleDown);
            var scaledY = (int)(y/_.gameProperties.m_resolutionScaleDown);
            return new(scaledX, scaledY);
        }

        public PointF GetMousePositionF()
        {
            var mousePosition = GetMousePosition();
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            return new((float)mousePosition.X/canvasSize.Width, (float)mousePosition.Y/canvasSize.Height);
        }
    }
}
