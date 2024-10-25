namespace YrradiaSDL2.Game.Rendering
{
    public class ImageRenderer
    {
        public void DrawImage(int imageNameHash, int x, int y, int width, int height)
        {
            var image = _.imageBank.GetImage(imageNameHash);
            var imageSize = _.imageBank.GetImageSize(imageNameHash);
            var sourceRect = new Rect(0, 0, imageSize.Width, imageSize.Height);
            var destRect = new Rect(x, y, width, height);
            SDL.RenderCopy(_.sdlDevice.m_renderer, image, ref sourceRect, ref destRect);
        }

        public void DrawImage(string imageName, int x, int y, int width, int height)
        {
            DrawImage(imageName.GetHashCode(), x, y, width, height);
        }

        public void DrawImage(int imageNameHash, float x, float y, float width, float height)
        {
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            var nX = (int)(canvasSize.Width * x);
            var nY = (int)(canvasSize.Height * y);
            var nWidth = (int)(canvasSize.Width * width);
            var nHeight = (int)(canvasSize.Height * height);
            DrawImage(imageNameHash, nX, nY, nWidth, nHeight);
        }

        public void DrawImage(string imageName, float x, float y, float width, float height)
        {
            DrawImage(imageName.GetHashCode(), x, y, width, height);
        }
    }
}
