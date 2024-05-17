using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using ServiceReference1;

namespace arch6
{
    internal class Controller : IController
    {
        IView view;
        IModel model;
        String menu;
        public Controller(ServiceClient client)
        {
            view = new View();
            model = new Model(client);
            menu = "1. Посмотреть рейсы по направлениям\n2. Посмотреть рейс по ID\n3. Заказать билет на рейс";
            view.showLine(menu);
        }

        private Ticket inputTicket()
        {
            try
            {
                view.showLine("Введите ID рейса");
                int raceId = Convert.ToInt32(Console.ReadLine());

                view.showLine("Введите ваше ФИ");
                string? name = Console.ReadLine();

                view.showLine("Введите номер паспорта");
                int passport = Convert.ToInt32(Console.ReadLine());

                Ticket ticket = new Ticket();
                ticket.race = new Race() { Id = raceId };
                ticket.Name = name;
                ticket.PassportNumber = passport;
                return ticket;
            }
            catch (Exception ex)
            {
                view.showLine("Неверно заполнен билет");
                view.showLine(ex.ToString());
                return null;
            }
        }

        public void mainLoop()
        {
            while (true)
            {
                Console.Clear();
                view.showLine(menu);

                string? input = Console.ReadLine();
                if (input == "1")
                {
                    view.showLine("Введите город отлета");
                    string from = Console.ReadLine();
                    view.showLine("Введите город прилета");
                    string to = Console.ReadLine();
                    var races = model.getRacesByPlaces(from, to);
                    view.showRaces(races);
                }
                else if (input == "2")
                {
                    view.showLine("Введите ID рейса");
                    int id = Convert.ToInt32(Console.ReadLine());
                    Race race = model.getRaceByID(id);
                    Race[] races = { race };
                    view.showRaces(races);
                }
                else if (input == "3")
                {
                    Ticket tick = inputTicket();
                    string resp = model.orderTicket(tick);
                    view.showLine(resp);
                }
                else
                {
                    continue;
                }
                Console.ReadKey(true);
            }
        }


        

    }
}
