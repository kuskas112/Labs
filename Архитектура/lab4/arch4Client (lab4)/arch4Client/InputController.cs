using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sample
{
    internal class InputController
    {
        static public void parseInt(ref int num)
        {
            while (true)
            {
                try
                {
                    num = int.Parse(Console.ReadLine());
                }
                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                    continue;
                }
                break;

            }
        }

        public static void fillMatrix(int size, ref ArrayList matrix)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    Console.WriteLine("Введите элемент с индексом " + (i + 1) + " " + (j + 1));
                    int item = 0;
                    parseInt(ref item);
                    matrix.Add(item);
                }
            }
        }

        public static void printMatrix(int size, ref ArrayList matrix)
        {
            for (int i = 0; i < size; i++)
            {
                string row = "";
                for (int j = 0; j < size; j++)
                {
                    row += matrix[i * size + j].ToString() + ' ';

                }
                Console.WriteLine(row);
            }
        }
    }
}
