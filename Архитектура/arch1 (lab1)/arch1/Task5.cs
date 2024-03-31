using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch1
{
    internal class Task5
    {
        public Task5(int num)
        {
            bool[] arr = new bool[num-1];

            int i = 2;
            while (i*i<=num)
            {
                if (arr[i-2] == false)
                {
                    for (int j = 0; (i*i+j*i) <= num; j++)
                    {
                        arr[(i * i + j * i)-2] = true;
                    }
                }
                i++;
            }

            for (int j = 0; j < num-1; j++)
            {
                if (!arr[j])
                {
                    Console.WriteLine(j+2);
                }
            }

        }
    }
}