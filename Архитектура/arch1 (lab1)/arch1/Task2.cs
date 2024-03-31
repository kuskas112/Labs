using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch1
{
    internal class Task2
    {
        public Task2()
        {
            for (int year = 1900; year <= 2000; year++)
            {
                if (year%400 == 0)
                {
                    Console.WriteLine("Год " + year.ToString() + ": високосный\n");
                }
                else if (year%100==0)
                {
                    Console.WriteLine("Год " + year.ToString() + ": не високосный\n");
                }
                else if (year % 4 == 0)
                {
                    Console.WriteLine("Год " + year.ToString() + ": високосный\n");
                }
                else
                {
                    Console.WriteLine("Год " + year.ToString() + ": не високосный\n");
                }
            }
        }
    }
}
