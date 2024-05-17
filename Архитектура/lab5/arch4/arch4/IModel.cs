using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace arch4
{
    internal interface IModel
    {
        public XDocument GetCurseOnDate(DateTime dateTime);
        public XDocument EnumReutersValutesXML();
        public XDocument MainInfoXML();
        public XDocument mrrf7DXML(DateTime fromDate, DateTime toDate);
    }
}
