using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch1
{
    internal class Task1
    {
        public Task1(string[] args)
        {
            foreach (var item in args)
            {
                Console.WriteLine(item);
            }
        }
    }
}
