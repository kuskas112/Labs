using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using Google.Protobuf.WellKnownTypes;

namespace arch4
{
    internal class View : IView
    {
        public void showCurs(XDocument doc, int maxRowLen = 0)
        {
            if(maxRowLen == 0)
            {
                maxRowLen = 20;
            }
            var query = from c in doc.Descendants("ValuteCursOnDate") select c;
            showTable(query, maxRowLen);
        }
            
        public void showMrrf(XDocument doc, int maxRowLen = 0)
        {
            if (maxRowLen == 0)
            {
                maxRowLen = 35;
            }
            var query = from c in doc.Descendants("mr") select c;
            showTable(query, maxRowLen);
        }

        public void showReuters(XDocument doc, int maxRowLen = 0)
        {
            if (maxRowLen == 0)
            {
                maxRowLen = 30;
            }
            var query = from c in doc.Descendants("EnumRValutes") select c;
            showTable(query, maxRowLen);
        }

        public void showMainInfo(XDocument doc, int maxRowLen = 0)
        {
            if (maxRowLen == 0)
            {
                maxRowLen = 30;
            }
            var query = from c in doc.Descendants("RegData") select c;
            showTable(query, maxRowLen);
        }

        private void showTable(IEnumerable<XElement> query, int maxRowLen)
        {
            try
            {

            foreach (var item in query.First().Elements())
            {
                String val = item.Name.ToString();
                for (int i = 0; i < maxRowLen; i++)
                {
                    if (i < val.Length)
                    {
                        Console.Write(val[i]);
                    }
                    else
                    {
                        Console.Write(' ');
                    }
                }
            }
            Console.WriteLine('\n');
            foreach (var valute in query)
            {
                foreach (var elem in valute.Elements())
                {
                    String val = elem.Value.ToString();
                    for (int i = 0; i < maxRowLen; i++)
                    {
                        if (i < val.Length)
                        {
                            Console.Write(val[i]);
                        }
                        else
                        {
                            Console.Write(' ');
                        }
                    }
                }
                Console.Write('\n');
            }


            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        public void showMenuItem(MenuItem item)
        {
            item.showItem();
        }

        public void showLine(string line)
        {
            Console.WriteLine(line);
        }
    }
}
