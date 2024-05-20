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
        public IModel model;
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
            int[,] distances = form1.getDataMatrix(out bool boolReuslt);
            if (boolReuslt == false)
            {
                form1.showError("Не введено ни одного значения");
                return;
            }
            
            if(validateDataMatrix(distances, out string message) == false)
            {
                form1.showError(message);
                return;
            }
            model.setDistances(distances);
            int[] resultArray = model.Solve(out int distance);
            string responce = "Найденный путь: ";
            foreach (var cityIndex in resultArray)
            {
                responce += (cityIndex + 1).ToString() + " ";
            }
            responce += "\nСумма: " + distance.ToString();
            form1.showSolution(responce);
            showSolutionPath(resultArray);
        }
        private void showSolutionPath(int[] solution)
        {
            for (int i = 0; i < solution.Length - 1; i++)
            {
                form1.drawSolutionCityConnection(cities.ElementAt(i), cities.ElementAt(i + 1));
            }
            form1.drawSolutionCityConnection(cities.ElementAt(0), cities.Last());
        }
        private bool validateDataMatrix(int[,] dataMatrix, out string message)
        {
            int size = dataMatrix.GetLength(0);
            for (int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    if(i != j && dataMatrix[i,j] <= 0)
                    {
                        message = "Расстояния должны быть строго больше нуля";
                        return false;
                    }
                }
            }
            message = "";
            return true;
        }
    }
}
