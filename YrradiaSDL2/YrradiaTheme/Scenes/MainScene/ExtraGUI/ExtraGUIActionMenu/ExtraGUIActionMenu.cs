using System;
using System.Linq;

namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu
{
    public class ExtraGUIActionMenu
    {
        private bool m_open = false;
        private PointF m_position;
        private const float k_width = 0.12f;
        private const float k_lineHeight = 0.5f;
        private Dictionary<int, PlayerAction> m_currentPlayerActions = new();
        private System.Drawing.Point m_clickedCoordinate;

        public void Update()
        {
            if (_.mouseInput.m_rightButton.GetHasBeenFiredPickResult())
            {
                m_position = _.mouseUtilities.GetMousePositionF();
                m_open = true;
                m_clickedCoordinate = _.tileHovering.m_hoveredCoordinate;
                PopulateMenu();
            }

            var mousePositionF = _.mouseUtilities.GetMousePositionF();

            var row = 0;
            foreach (var action in m_currentPlayerActions)
            {
                var menuRowPosition = new PointF(m_position.X + 0.005f, m_position.Y + 0.01f + row * k_lineHeight);
                var menuRowRect = new RectangleF(menuRowPosition.X, menuRowPosition.Y, k_width, k_lineHeight);
                action.Value.m_hovered = menuRowRect.Contains(mousePositionF);
                if (action.Value.m_hovered)
                {
                    _.cursor.SetToHovering();

                    if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
                    {
                        action.Value.Perform(m_clickedCoordinate);
                        m_open = false;
                        return;
                    }
                }
                row++;
            }

            if (m_open && _.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
            {
                m_open = false;
            }
        }

        public void Render()
        {
            if (m_open)
            {
                _.imageRenderer.DrawImage("GUIMenuDefaultBackground", m_position.X, m_position.Y, k_width, 0.2f);

                var row = 0;
                foreach (var action in m_currentPlayerActions)
                {
                    var menuRowPosition = new PointF(m_position.X + 0.005f, m_position.Y + 0.01f + row * k_lineHeight);
                    var menuRowRect = new RectangleF(menuRowPosition.X, menuRowPosition.Y, k_width, k_lineHeight);
                    var color = action.Value.m_hovered ? Colors.yellow : Colors.wheat;
                    _.textRenderer.DrawString(action.Value.GetLabel(), menuRowPosition, color, FontSizes._18);
                    row++;
                }
            }
        }

        private void PopulateMenu()
        {
            m_currentPlayerActions.Clear();

            var tile = _.world.GetCurrentWorldArea().GetTile(_.tileHovering.m_hoveredCoordinate);

            if (tile != null)
            {
                foreach (var tangibleObject in tile.m_objects.m_objects)
                {
                    var newAction = new PlayerActionChopDownTree();
                    var actionHash = newAction.GetLabel().GetHashCode();
                    if (!m_currentPlayerActions.ContainsKey(actionHash))
                    {
                        m_currentPlayerActions.Add(actionHash, newAction);
                    }
                }
            }
        }
    }
}
