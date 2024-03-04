using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch1
{
    internal class Task4
    {
        public Task4(int num)
        {
            Console.WriteLine("Факториал: "+factorial(num));
        }

        private int factorial(int num)
        {
            if (num == 1)
            {
                return 1;
            }
            if (num <= 0)
            {
                return 0;
            }
            
            return num*factorial(num - 1);
        }


    }
}
