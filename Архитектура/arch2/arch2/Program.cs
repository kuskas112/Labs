using System;

namespace arch2
{
    internal class Program
    {
        static void Main(string[] args)
        {

            Server server = new Server();
            ConnectionHandler hndlr = new ConnectionHandler(server.socket);
        }
    }
}