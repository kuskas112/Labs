using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace archPractice
{
    internal class Model
    {
        public int[,] distances;

     
        public int[] Solve()
        {
            int n = distances.GetLength(0);
            int[] cities = Enumerable.Range(0, n).ToArray(); // Создаем массив городов от 0 до n-1
            int[] bestPath = null;
            int bestDistance = int.MaxValue;

            do
            {
                int currentDistance = GetTotalDistance(cities); // Вычисляем общее расстояние текущего пути
                if (currentDistance < bestDistance) // Если общее расстояние меньше лучшего найденного до этого
                {
                    bestDistance = currentDistance; // Обновляем лучшее расстояние
                    bestPath = cities.ToArray(); // Запоминаем текущий путь как лучший
                }
            } while (NextPermutation(cities)); // Генерируем следующую перестановку городов

            return bestPath; // Возвращаем лучший найденный путь
        }

        private int GetTotalDistance(int[] path)
        {
            int totalDistance = 0;
            for (int i = 0; i < path.Length - 1; i++)
            {
                totalDistance += distances[path[i], path[i + 1]]; // Суммируем расстояния между соседними городами
            }
            totalDistance += distances[path[path.Length - 1], path[0]]; // Добавляем расстояние от последнего города к начальному
            return totalDistance; // Возвращаем общее расстояние пути
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
                return false; // Нет следующей перестановки
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

            return true; // Есть следующая перестановка
        }
    }
}
