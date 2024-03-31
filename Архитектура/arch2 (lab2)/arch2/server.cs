using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace arch2
{
    internal class Server
    {
        public Socket socket;
        
        
        public Server()
        {
            Console.WriteLine("start server");
            byte[] addressByte = {127,0,0,1 };
            IPAddress address = new IPAddress(addressByte);
            IPEndPoint ipPoint = new IPEndPoint(address, 8888);

            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Bind(ipPoint);

            socket.Listen();
            Console.WriteLine(socket.LocalEndPoint);
            Console.WriteLine("Сервер запущен. Ожидание подключений...");
        }
    }


}
