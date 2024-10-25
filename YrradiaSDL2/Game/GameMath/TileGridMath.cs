namespace YrradiaSDL2.Game.GameMath
{
    public class TileGridMath
    {
        public Size GetTileGridSize()
        {
            var rows = _.gameProperties.m_numTileGridRows;
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            var tileSize = GetTileSize();
            var columns = canvasSize.Width / tileSize + 1;

            return new Size(columns, rows);
        }

        public int GetTileSize()
        {
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            return canvasSize.Height / _.gameProperties.m_numTileGridRows + 1;
        }
    }
}
