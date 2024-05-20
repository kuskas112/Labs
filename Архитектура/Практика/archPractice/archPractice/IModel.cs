using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace archPractice
{
    internal interface IModel
    {
        public int[] Solve(out int bestDistance);
        public void setDistances(int[,] distances);
    }
}
