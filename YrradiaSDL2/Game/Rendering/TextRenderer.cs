namespace YrradiaSDL2.Game.Rendering
{
    public class TextRenderer
    {
        Dictionary<FontSizes, SDL_Sharp.Ttf.Font> m_fonts = new();

        public TextRenderer()
        {
            SDL_Sharp.Ttf.TTF.Init();

            AddFontSize(FontSizes._16);
            AddFontSize(FontSizes._20);
            AddFontSize(FontSizes._24);
        }

        private void AddFontSize(FontSizes fontSize)
        {
            m_fonts.Add(fontSize, SDL_Sharp.Ttf.TTF.OpenFont("Resources\\Fonts\\PixeloidSans.ttf", (int)((int)fontSize / _.gameProperties.m_resolutionScaleDown)));
        }

        public void DestroyFonts()
        {
            foreach (var font in m_fonts.Values)
            {
                SDL_Sharp.Ttf.TTF.CloseFont(font);
            }
        }

        public void DrawString(string text, System.Drawing.Point position, SDL_Sharp.Color color, FontSizes fontSize = FontSizes._24, bool centerAlign = false)
        {
            unsafe
            {
                var textSurface =
                    SDL_Sharp.Ttf.TTF.RenderText_Solid(m_fonts[fontSize], text, color);

                var texture = SDL.CreateTextureFromSurface(_.sdlDevice.m_renderer, textSurface);
                var rect = new Rect(position.X, position.Y, textSurface->W, textSurface->H);

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
