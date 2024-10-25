namespace YrradiaSDL2.Game.Assets
{
    public class ImageBank
    {
        unsafe private Dictionary<int, ImageEntry> m_images = new();

        public void LoadImages()
        {
            var files = Directory.GetFiles("Resources\\Images");

            foreach (var file in files)
            {
                unsafe
                {
                    var image = SDL_Sharp.Image.IMG.LoadTexture(_.sdlDevice.m_renderer, file);
                    var fileName = Path.GetFileName(file);
                    var imageName = fileName.Substring(0, fileName.LastIndexOf('.'));
                    uint format;
                    TextureAccess access;
                    int width;
                    int height;
                    var size = SDL.QueryTexture(image, out format, out access, out width, out height);
                    m_images.Add(imageName.GetHashCode(), new(image, new(width, height)));
                }
            }
        }

        public void DestroyImages()
        {
            unsafe
            {
                foreach (var imageEntry in m_images)
                {
                    SDL.DestroyTexture(imageEntry.Value.texture);
                }
            }
        }

        public Texture GetImage(string imageName)
        {
            return GetImage(imageName.GetHashCode());
        }

        public Texture GetImage(int imageNameHash)
        {
            return m_images[imageNameHash].texture;
        }

        public Size GetImageSize(int imageNameHash)
        {
            return m_images[imageNameHash].size;
        }
    }
}
