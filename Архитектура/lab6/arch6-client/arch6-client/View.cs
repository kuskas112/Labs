using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using ServiceReference1;

namespace arch6
{
    internal class View : IView
    {
        
        public void showRaces(Race[] races, int maxRowLen = 0)
        {
            if (maxRowLen == 0)
            {
                maxRowLen = 20;
            }
            showTable(races, maxRowLen);
        }

        private void showColumn(string col, int maxRowLen)
        {
            for (int i = 0; i < maxRowLen; i++)
            {
                if (i < col.Length)
                {
                    Console.Write(col[i]);
                }
                else
                {
                    Console.Write(' ');
                }
            }
        }
        private void showTable(Race[] races, int maxRowLen)
        {
            try
            {
                showColumn("ID", maxRowLen);
                showColumn("From", maxRowLen);
                showColumn("To", maxRowLen);
                showColumn("Company", maxRowLen);
                showColumn("Date", maxRowLen);
                showColumn("Free Seats", maxRowLen);
            
            Console.WriteLine('\n');
            foreach (var race in races)
            {
                    showColumn(race.Id.ToString(), maxRowLen);
                    showColumn(race.From, maxRowLen);
                    showColumn(race.To, maxRowLen);
                    showColumn(race.Company, maxRowLen);
                    showColumn(race.Date.ToString(), maxRowLen);
                    showColumn(race.FreeSeats.ToString(), maxRowLen);
                    Console.Write('\n');
            }


            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }


        public void showLine(string line)
        {
            Console.WriteLine(line);
        }
    }
}
