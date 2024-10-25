namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.Modules
{
    public class TileHovering
    {
        public void Update()
        {
            var mousePosition = _.mouseUtilities.GetMousePosition();

            var worldArea = _.world.GetCurrentWorldArea();
            var player = _.player;
            var gridSize = _.tileGridMath.GetTileGridSize();
            var tileSize = _.tileGridMath.GetTileSize();
            var canvasSize = _.canvasUtilities.GetCanvasSize();
            for (var y = 0; y < gridSize.Height; y++)
            {
                for (var x = 0; x < gridSize.Width; x++)
                {
                    var area = new Rectangle(x * tileSize, y * tileSize, tileSize, tileSize);

                    if (area.Contains(mousePosition))
                    {
                        var crdX = player.m_position.X - (gridSize.Width - 1) / 2 + x;
                        var crdY = player.m_position.Y - (gridSize.Height - 1) / 2 + y;

                        if (crdX < 0 || crdY < 0 || crdX >= 100 || crdY >= 100)
                        {
                            continue;
                        }

                        var tile = worldArea.GetTile(crdX, crdY);

                        if (tile.m_mob != null)
                        {
                            _.cursor.SetToAttack();
                        }
                    }
                }
            }
        }
    }
}
