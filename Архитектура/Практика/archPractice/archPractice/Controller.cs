using System;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace archPractice
{
    internal class Controller
    {
        public IForm form1;
        public Model model;
        private LinkedList<Point> cities = new LinkedList<Point>();
        
        public Controller()
        {
            form1 = new Form1();
            form1.addMouseListener(new MouseEventHandler(mouseClick));
            form1.addClearButtonListener(new EventHandler(clearButton_Click));
            form1.addSolveButtonListener(new EventHandler(solveButton_Click));
            model = new Model();
        }
        private void mouseClick(object sender, MouseEventArgs e)
        {
            form1.drawCity(e.X, e.Y);
            Point city = new Point(e.X, e.Y);

            foreach (var existingCity in cities)
            {
                if (city.X == existingCity.X && city.Y == existingCity.Y)
                {
                    return;
                }
                form1.drawCityConnection(city, existingCity);
            }
            cities.AddLast(city);

            form1.addMatrixColumn(cities.Count().ToString());

        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            cities.Clear();
            form1.clear();
        }
        private void solveButton_Click(object sender, EventArgs e)
        {
            model.distances = new int[,] {
            {0,6,4,8,7,14},
            {6,0,7,11,7,10},
            {4,7,0,4,3,10},
            {8,11,4,0,5,11},
            {7,7,3,5,0,7},
            {14,10,10,11,7,0}
            };
            int[] res = model.Solve();
        }
    }
}
