﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace archPractice
{
    internal interface IForm
    {
        public void addMouseListener(MouseEventHandler handler);
        public void addClearButtonListener(EventHandler handler);
        public int[,] getDataMatrix(out bool boolResult);
        public void addMatrixColumn(string name);
        public void drawCity(int x, int y);
        public void drawCityConnection(Point city1, Point city2);
        public void drawSolutionCityConnection(Point city1, Point city2);
        public void clear();
        public void addSolveButtonListener(EventHandler handler);
        public void showError(string err);
        public void showSolution(string sol);
    }
}
