using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch1
{
    internal class Task3
    {
        public Task3(int num)
        {
            int a = 1, b = 0, c = 1;
            if (num > 0)
            {
                Console.WriteLine(b);
                Console.WriteLine(a);
            }
            while (a+b<=num)
            {
                c = a + b;
                b = a;
                a = c;
                Console.WriteLine(c);
            }
        }
    }
}
