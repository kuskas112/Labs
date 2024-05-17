using System;
using System.Xml;
using System.Xml.Linq;
using ServiceReference1;
using ServiceReference1;

namespace arch6
{
    class Model : IModel
    {
        ServiceClient client { get; set; }
        public Model(ServiceClient client) {
            this.client = client;
        }

        public Race[] getRacesByPlaces(string from, string to)
        {
            return client.GetRacesByPlaces(from, to);
        }

        public Race getRaceByID(int id)
        {
            return client.GetRaceById(id);
        }

        public string orderTicket(Ticket ticket)
        {
            return client.OrderTicket(ticket);
        }


    }
}
