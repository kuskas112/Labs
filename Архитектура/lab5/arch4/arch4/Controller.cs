using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace arch4
{
    internal class Controller : IController
    {
        IView view;
        IModel model;
        List<MenuItem> menuItems = new List<MenuItem>();
        public Controller()
        {
            view = new View();
            model = new Model();

            menuItems.Add(new MenuItem(1, "Получение ежедневных курсов валют"));
            menuItems.Add(new MenuItem(2, "Справочник по кодам редких валют от Thomson Reuters"));
            menuItems.Add(new MenuItem(3, "Получение основной информации"));
            menuItems.Add(new MenuItem(4, "Международные резервы Российской Федерации"));
            
            foreach (MenuItem item in menuItems)
            {
                view.showMenuItem(item);
            }
        }

        private DateTime inputDate()
        {
            try
            {
                view.showLine("Введите год");
                int year = Convert.ToInt32(Console.ReadLine());

                view.showLine("Введите месяц");
                int month = Convert.ToInt32(Console.ReadLine());

                view.showLine("Введите день");
                int day = Convert.ToInt32(Console.ReadLine());

                DateTime date = new DateTime(year, month, day);
                return date;
            }
            catch (Exception ex)
            {
                view.showLine("Неверно введённая дата");
                view.showLine("Вместо нее будет подставлена текущая дата");
                return DateTime.Now;
            }
        }

        public void mainLoop()
        {
            while (true)
            {
                Console.Clear();
                foreach (MenuItem item in menuItems)
                {
                    view.showMenuItem(item);
                }

                string? input = Console.ReadLine();
                if (input == "1")
                {
                    DateTime date = inputDate();
                    XDocument doc = model.GetCurseOnDate(date);
                    view.showCurs(doc);

                }
                else if (input == "2")
                {
                    XDocument doc = model.EnumReutersValutesXML();
                    view.showReuters(doc);
                }
                else if (input == "3")
                {
                    XDocument doc = model.MainInfoXML();
                    view.showMainInfo(doc);
                }
                else if (input == "4")
                {
                    DateTime fromDate = inputDate();
                    DateTime toDate = inputDate();
                    XDocument doc = model.mrrf7DXML(fromDate, toDate);
                    view.showMrrf(doc);
                }
                else
                {
                    continue;
                }
                Console.ReadKey(true);
            }
        }


        
        
        public static void Main(string[] args)
        {
            IController controller = new Controller();
            controller.mainLoop();
        }

    }
}
