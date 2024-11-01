using System;
using System.Linq;

namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu
{
    public class ExtraGUIActionMenu
    {
        private bool m_open = false;
        private PointF m_position;
        private const float k_width = 0.16f;
        private const float k_lineHeight = 0.05f;
        private Dictionary<int, PlayerAction> m_currentPlayerActions = new();
        public System.Drawing.Point m_clickedCoordinate;

        public void Update()
        {
            if (m_open)
            {
                var mousePositionF = _.mouseUtilities.GetMousePositionF();

                var row = 0;
                foreach (var action in m_currentPlayerActions)
                {
                    var menuRowPosition = new PointF(m_position.X + 0.013f, m_position.Y + 0.01f + row * k_lineHeight);
                    var menuRowRect = new RectangleF(menuRowPosition.X, menuRowPosition.Y, k_width, k_lineHeight);
                    action.Value.m_hovered = menuRowRect.Contains(mousePositionF);
                    if (action.Value.m_hovered)
                    {
                        _.cursor.SetToHovering();

                        if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
                        {
                            action.Value.Perform(m_clickedCoordinate);
                            m_open = false;
                            m_clickedCoordinate = new(-1, -1);
                            return;
                        }
                    }
                    row++;
                }

                if (_.mouseInput.m_leftButton.GetHasBeenFiredPickResult())
                {
                    m_open = false;
                    return;
                }
            }

            if (_.mouseInput.m_leftButton.GetHasBeenDoubleClickedPickResult())
            {
                m_position = _.mouseUtilities.GetMousePositionF();
                m_open = true;
                m_clickedCoordinate = _.tileHovering.m_hoveredCoordinate;
                PopulateMenu();
            }
        }

        public void Render()
        {
            if (m_open)
            {
                var height = 0.01f + m_currentPlayerActions.Count * k_lineHeight;
                _.imageRenderer.DrawImage("GUIMenuDefaultBackground", m_position.X, m_position.Y, k_width, height);

                var row = 0;
                foreach (var action in m_currentPlayerActions)
                {
                    var menuRowPosition = new PointF(m_position.X + 0.013f, m_position.Y + 0.01f + row * k_lineHeight);
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
                    if (tangibleObject.m_type == "ObjectTree1".GetHashCode()
                        || tangibleObject.m_type == "ObjectTree2".GetHashCode())
                    {
                        var newAction = new PlayerActionChopDownTree();
                        var actionHash = newAction.GetLabel().GetHashCode();
                        if (!m_currentPlayerActions.ContainsKey(actionHash))
                        {
                            m_currentPlayerActions.Add(actionHash, newAction);
                        }
                    }
                    else if (tangibleObject.m_type == "ObjectTrain".GetHashCode()
                        || tangibleObject.m_type == "ObjectTrainWagon".GetHashCode())
                    {
                        var newAction = new PlayerActionRideTrain();
                        var actionHash = newAction.GetLabel().GetHashCode();
                        if (!m_currentPlayerActions.ContainsKey(actionHash))
                        {
                            m_currentPlayerActions.Add(actionHash, newAction);
                        }
                    }
                    else if (tangibleObject.m_type == "ObjectWoodLog".GetHashCode())
                    {
                        {
                            var newAction = new PlayerActionCreateCampfire();
                            var actionHash = newAction.GetLabel().GetHashCode();
                            if (!m_currentPlayerActions.ContainsKey(actionHash))
                            {
                                m_currentPlayerActions.Add(actionHash, newAction);
                            }
                        }
                        {
                            var newAction = new PlayerActionCreateWoodPlank();
                            var actionHash = newAction.GetLabel().GetHashCode();
                            if (!m_currentPlayerActions.ContainsKey(actionHash))
                            {
                                m_currentPlayerActions.Add(actionHash, newAction);
                            }
                        }
                    }
                    else if (tangibleObject.m_type == "ObjectWoodPlank".GetHashCode())
                    {

                        {
                            var newAction = new PlayerActionLayWooodFloor();
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
    }
}
