using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace archPractice
{
    internal class Model : IModel
    {
        public int[,] distances;
        public void setDistances(int[,] distances)
        {
            this.distances = distances;
        }
        public int[] Solve(out int bestDistance)
        {
            int n = distances.GetLength(0);
            int[] cities = Enumerable.Range(0, n).ToArray();
            int[] bestPath = null;
            bestDistance = int.MaxValue;

            do
            {
                int currentDistance = GetTotalDistance(cities);
                if (currentDistance < bestDistance)
                {
                    bestDistance = currentDistance;
                    bestPath = cities.ToArray();
                }
            } while (NextPermutation(cities));

            return bestPath;
        }
        private int GetTotalDistance(int[] path)
        {
            int totalDistance = 0;
            for (int i = 0; i < path.Length - 1; i++)
            {
                totalDistance += distances[path[i], path[i + 1]];
            }
            totalDistance += distances[path[path.Length - 1], path[0]];
            return totalDistance;
        }
        private bool NextPermutation(int[] sequence)
        {
            int i = sequence.Length - 1;
            while (i > 0 && sequence[i - 1] >= sequence[i])
            {
                i--;
            }
            if (i <= 0)
            {
                return false;
            }

            int j = sequence.Length - 1;
            while (sequence[j] <= sequence[i - 1])
            {
                j--;
            }

            int temp = sequence[i - 1];
            sequence[i - 1] = sequence[j];
            sequence[j] = temp;

            j = sequence.Length - 1;
            while (i < j)
            {
                temp = sequence[i];
                sequence[i] = sequence[j];
                sequence[j] = temp;
                i++;
                j--;
            }

            return true;
        }
    }
}
