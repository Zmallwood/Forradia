namespace YrradiaSDL2.Common
{
    public class CanvasUtilities
    {
        public Size GetCanvasSize()
        {
            int width;
            int height;
            SDL.GetWindowSize(_.sdlDevice.m_window, out width, out height);
            var scaledWidth = (int)(width / _.gameProperties.m_resolutionScaleDown);
            var scaledHeight = (int)(height / _.gameProperties.m_resolutionScaleDown);
            return new Size(scaledWidth, scaledHeight);
        }

        public Size GetDesktopResolution()
        {
            DisplayMode displayMode;
            SDL.GetDesktopDisplayMode(0, out displayMode);
            return new(displayMode.Width, displayMode.Height);
        }

        public float GetAspectRatio()
        {
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            return (float)canvasSize.Width / canvasSize.Height;
        }

        public float ConvertWidthToHeight(float width)
        {
            return width * GetAspectRatio();
        }

        public float ConvertHeightToWidth(float height)
        {
            return height / GetAspectRatio();
        }
    }
}
