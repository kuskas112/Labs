using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace arch4
{
    internal class MenuItem
    {
        public string description;
        public int id;
        public MenuItem(int id, string description)
        {
            this.id = id;
            this.description = description;
        }
        public void showItem()
        {
            Console.Write(id.ToString());
            Console.Write(". " + description + '\n');
        }
    }
}
