using System.Data;
using System.Xml;
using System.Xml.Linq;
using CoreWCF;

namespace CoreWCFDemoServer
{
    public class Service : IService
    {
        public Race[] GetRacesByPlaces(string from, string to)
        {
            using (Context db = new Context())
            {
                var races = db.Races.Where(p => p.From == from && p.To == to);
                Race[] racs = new Race[races.Count()];
                for (int i = 0; i < races.Count(); i++)
                {
                    racs[i] = races.ElementAt(i);
                }
                return racs;
            }
        }

        public Race GetRaceById(int id)
        {
            using (Context db = new Context())
            {
                var races = db.Races.Where(p => p.Id == id);
                if (races.Count() > 0)
                {
                    return races.ElementAt(0);
                }
                else { return null; }
            }
        }

        public string OrderTicket(Ticket ticket)
        {
            if (ticket.PassportNumber.ToString().Length != 6)
            {
                return "Wrong passport number";
            }     
            if(ticket.Name == "")
            {
                return "Empty name";
            }
            using (Context db = new Context())
            {
                for (int i = 0; i < db.Races.Count(); i++)
                {
                    if (db.Races.ElementAt(i).Id == ticket.race.Id)
                    {
                        if(db.Races.ElementAt(i).FreeSeats <= 0)
                        {
                            return "No more free seats";
                        }

                        db.Races.ElementAt(i).FreeSeats -= 1;

                        ticket.race = db.Races.Where(p => p.Id == ticket.race.Id).First();
                        db.Tickets.Add(ticket);

                        db.SaveChanges();
                        break;
                    }
                }

                
            }
            return "Success";
        }


    }
}