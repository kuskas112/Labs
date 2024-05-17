using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using ServiceReference1;

namespace arch6
{
    internal interface IView
    {
        public void showLine(string line);
        public void showRaces(Race[] races, int maxRowLen = 0);
    }
}
