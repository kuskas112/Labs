using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace arch2
{
    internal class chatMember
    {
        public string login;
        public string password;
        public List<NetworkStream> streams = new List<NetworkStream>();

        public chatMember(string login, string password)
        {
            this.login = login;
            this.password = password;
        }

        public bool checkPassword(string pass)
        {
            if (this.password == pass)
            {
                return true;
            }
            return false;
        }
        public bool checkLogin(string login)
        {
            if (this.login == login)
            {
                return true;
            }
            return false;
        }
    }
}
