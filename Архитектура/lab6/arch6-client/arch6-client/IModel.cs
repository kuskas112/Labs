using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using ServiceReference1;

namespace arch6
{
    internal interface IModel
    {
        public Race[] getRacesByPlaces(string from, string to);
        public Race getRaceByID(int id);
        public string orderTicket(Ticket ticket);

    }
}
