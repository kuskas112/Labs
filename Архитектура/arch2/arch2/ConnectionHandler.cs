using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Reflection.Metadata;

namespace arch2
{
    internal class ConnectionHandler
    {
        public Socket socket;
        List<chatMember> clients = new List<chatMember>();
        public ConnectionHandler(Socket socket)
        {
            this.socket = socket;
            while (true)
            {
                Socket client = socket.Accept();
                Console.WriteLine($"Client address: {client.RemoteEndPoint}");
                Thread thread = new Thread(() => handleConnection(client));
                thread.Start();
            };

        }

        private void writeStream(NetworkStream ns, string message)
        {
            var data = Encoding.UTF8.GetBytes(message);
            ns.Write(data);

        }

        private string readStream(NetworkStream myNetworkStream, byte[] myReadBuffer)
        {
            try
            {
                string myCompleteMessage;
                int numberOfBytesRead = myNetworkStream.Read(myReadBuffer, 0, myReadBuffer.Length);
                myCompleteMessage = Encoding.ASCII.GetString(myReadBuffer, 0, numberOfBytesRead);
                    
                Console.WriteLine("Received the following message : " + myCompleteMessage);
                return myCompleteMessage;
            }
            catch (IOException e)
            {
                Console.WriteLine("Failed");
                Console.WriteLine(e.ToString);
                return "";
            }
        }

        private bool logIn(NetworkStream ns, byte[] buffer, string login, string pass)
        {
            
            foreach (var member in clients)
            {
                if (member.checkLogin(login))
                {
                    if (member.checkPassword(pass))
                    {
                        member.streams.Add(ns);
                        return true;
                    }
                    else
                    {
                        writeStream(ns, "msg:Wrong password!");
                        return false;
                    }
                }
            }
            chatMember newMember = new chatMember(login, pass);
            newMember.streams.Add(ns);
            clients.Add(newMember);
            writeStream(ns, "msg:Success!");
            return true;

        }

        private void sendMembers()
        {
            Thread.Sleep(1000);
            string members = "";
            foreach (var member in clients)
            {
                members += member.login + ' ';
            }

            foreach (var member in clients)
            {
                foreach (var stream in member.streams)
                {
                    writeStream(stream, "mmb:" + members);
                }
            }
        }

        private void handleConnection(Socket client)
        {
            byte[] buffer = new byte[1024];
            NetworkStream ns = new NetworkStream(client);
            string login, pass;

            do
            {
                writeStream(ns, "msg:Enter your login");

                login = readStream(ns, buffer);
                login = login.Substring(4, login.Length - 4);

                writeStream(ns, "msg:"+login);

                writeStream(ns, "msg:Enter yout password");
                pass = readStream(ns, buffer);
                writeStream(ns, pass);

            }
            while (!logIn(ns, buffer, login, pass));
           
            sendMembers();
            
            while (client.Connected)
            {
                string message = readStream(ns, buffer);
                if (message == "disconnect")
                {
                    chatMember mmbrToRemove = null;
                    foreach (var member in clients)
                    {
                        if (member.login == login)
                        {
                            mmbrToRemove = member;
                        }
                    }
                    clients.Remove(mmbrToRemove);
                    sendMembers();
                    client.Close();
                    return;
                }
                message = message.Substring(4, message.Length - 4);
                foreach (var member in clients)
                {
                    foreach (var stream in member.streams)
                    {
                        writeStream(stream, $"msg:[{login}]: {message}");
                    }
                }
            }
        }
    }
}
