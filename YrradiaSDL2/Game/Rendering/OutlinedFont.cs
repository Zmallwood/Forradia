namespace YrradiaSDL2.Game.Rendering
{
    public class OutlinedFont
    {
        public SDL_Sharp.Ttf.Font font;
        public SDL_Sharp.Ttf.Font fontOutline;

        public OutlinedFont(SDL_Sharp.Ttf.Font font, SDL_Sharp.Ttf.Font fontOutline)
        {
            this.font = font;
            this.fontOutline = fontOutline;
        }
    }
}
