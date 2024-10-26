namespace YrradiaSDL2.Game.Rendering
{
    public class TextRenderer
    {
        private Dictionary<FontSizes, OutlinedFont> m_fonts = new();
        private const int k_outlineSize = 2;

        public TextRenderer()
        {
            SDL_Sharp.Ttf.TTF.Init();

            AddFontSize(FontSizes._16);
            AddFontSize(FontSizes._18);
            AddFontSize(FontSizes._20);
            AddFontSize(FontSizes._24);
        }

        private void AddFontSize(FontSizes fontSize)
        {
            var font = SDL_Sharp.Ttf.TTF.OpenFont("Resources\\Fonts\\PixeloidSans.ttf", (int)((int)fontSize / _.gameProperties.m_resolutionScaleDown));
            var fontOutline = SDL_Sharp.Ttf.TTF.OpenFont("Resources\\Fonts\\PixeloidSans.ttf", (int)((int)fontSize / _.gameProperties.m_resolutionScaleDown));
            SDL_Sharp.Ttf.TTF.SetFontOutline(fontOutline, k_outlineSize);
            m_fonts.Add(fontSize, new(font, fontOutline));
        }

        public void DestroyFonts()
        {
            foreach (var font in m_fonts.Values)
            {
                SDL_Sharp.Ttf.TTF.CloseFont(font.font);
            }
        }

        public void DrawString(string text, System.Drawing.Point position, SDL_Sharp.Color color, FontSizes fontSize = FontSizes._24, bool centerAlign = false)
        {
            if (text == "")
            {
                return;
            }

            unsafe
            {
                var textOutlineSurface = SDL_Sharp.Ttf.TTF.RenderText_Blended(m_fonts[fontSize].fontOutline, text, Colors.black);
                var textSurface = SDL_Sharp.Ttf.TTF.RenderText_Blended(m_fonts[fontSize].font, text, color);

                SDL.SetSurfaceBlendMode(textSurface, BlendMode.Blend);
                var sourceRect = new Rect(0, 0, textSurface->W, textSurface->H);
                var destRect = new Rect(k_outlineSize, k_outlineSize, textSurface->W, textSurface->H);
                SDL.BlitSurface(textSurface, ref sourceRect, textOutlineSurface, ref destRect);
                SDL.FreeSurface(textSurface);

                var texture = SDL.CreateTextureFromSurface(_.sdlDevice.m_renderer, textOutlineSurface);
                var rect = new Rect(position.X, position.Y, textOutlineSurface->W, textOutlineSurface->H);

                if (centerAlign)
                {
                    rect.X -= rect.Width / 2;
                    rect.Y -= rect.Height / 2;
                }
                SDL.RenderCopy(_.sdlDevice.m_renderer, texture, null, &rect);
            }
        }

        public void DrawString(string text, System.Drawing.PointF position, SDL_Sharp.Color color, FontSizes fontSize = FontSizes._24, bool centerAlign = false)
        {
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            var nX = (int)(canvasSize.Width * position.X);
            var nY = (int)(canvasSize.Height * position.Y);
            DrawString(text, new(nX, nY), color, fontSize, centerAlign);
        }
    }
}
