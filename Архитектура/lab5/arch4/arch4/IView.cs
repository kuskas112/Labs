using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace arch4
{
    internal interface IView
    {
        public void showCurs(XDocument doc, int maxRowLen = 0);
        public void showMrrf(XDocument doc, int maxRowLen = 0);
        public void showReuters(XDocument doc, int maxRowLen = 0);
        public void showMainInfo(XDocument doc, int maxRowLen = 0);
        public void showMenuItem(MenuItem item);
        public void showLine(string line);
    }
}
