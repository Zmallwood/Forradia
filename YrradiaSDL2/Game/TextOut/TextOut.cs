namespace YrradiaSDL2.Game.TextOut
{
    public class TextOut
    {
        public List<string> m_text = new();

        public void Print(string text)
        {
            m_text.Add(text);
        }
    }
}
