//using System;
using arch1;

namespace arch1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var task = new Task1(args);
            var task2 = new Task2();
            var task3 = new Task3(100);
            var task4 = new Task4(6);
            var task5 = new Task5(100);
        }
    }
}