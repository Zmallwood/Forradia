namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class ItemMoving
    {
        public TangibleObject? m_objectInAir = null;

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

                _.imageRenderer.DrawImage(m_objectInAir.m_type, mousePositionF.X - tileWidth, mousePositionF.Y - tileHeight, tileWidth, tileHeight);
            }
        }
    }
}
