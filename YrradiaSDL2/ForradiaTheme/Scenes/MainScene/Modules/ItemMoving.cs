namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class ItemMoving
    {
        public TangibleObject? m_objectInAir = null;
        private PointF m_drawOffset = new PointF(0.0f, 0.0f);

        public void Update()
        {
            if (m_objectInAir == null)
            {
                if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
                {
                    var tile = _.world.GetCurrentWorldArea().GetTile(_.tileHovering.m_hoveredCoordinate);
                    var topObject = tile?.m_objects.Pop();
                    if (topObject != null)
                    {
                        m_objectInAir = topObject;
                        var mousePosition = _.mouseUtilities.GetMousePosition();
                        var tileSize = _.tileGridMath.GetTileSize();
                        var drawOffsetX = mousePosition.X % tileSize;
                        var drawOffsetY = mousePosition.Y % tileSize;
                        var canvasSize = _.canvasUtilities.GetCanvasSize();
                        m_drawOffset = new(-(float)drawOffsetX / canvasSize.Width, -(float)drawOffsetY / canvasSize.Height);
                    }
                }
            }
            else
            {
                if (_.mouseInput.m_leftButton.GetHasBeenReleasedLeaveResult())
                {
                    var tile = _.world.GetCurrentWorldArea().GetTile(_.tileHovering.m_hoveredCoordinate);
                    tile?.m_objects.Add(m_objectInAir);
                    m_objectInAir = null;
                }
            }
        }

        public void Render()
        {
            if (m_objectInAir != null)
            {
                var mousePositionF = _.mouseUtilities.GetMousePositionF();
                var tileSize = _.tileGridMath.GetTileSize();
                var tileWidth = (float)tileSize/_.canvasUtilities.GetCanvasSize().Width;
                var tileHeight = _.canvasUtilities.ConvertWidthToHeight(tileWidth);

                _.imageRenderer.DrawImage(m_objectInAir.m_type, mousePositionF.X + m_drawOffset.X, mousePositionF.Y + m_drawOffset.Y, tileWidth, tileHeight);
            }
        }
    }
}
