using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace arch2_ClientGUI
{
    public partial class Form1 : Form
    {
        private byte[] buffer = new byte[1024];
        private string[] members;
        NetworkStream ns;
        public Form1()
        {
            InitializeComponent();
        }

        private void writeLine(string line)
        {
            chatText.Text += line + "\r\n";
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            IPAddress ip = IPAddress.None;
            int port;
            if (   int.TryParse(portText.Text, out port) == false ||
                IPAddress.TryParse(ipText.Text, out ip) == false  )
            { return; }
            writeLine($"Trying to connect {ip.ToString()}:{port.ToString()}");

            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                socket.Connect(ip, port);
            }
            catch (SocketException)
            {
                writeLine($"Failed to connect {ip.ToString()}:{port.ToString()}");
                return;
            }
            ns = new NetworkStream(socket);
            Thread messageReceive = new Thread(readStream);
            messageReceive.Start();
        }

        private void readStream()
        {
            try
            {
                while (true)
                {
                    string myCompleteMessage;
                    int numberOfBytesRead = ns.Read(buffer, 0, buffer.Length);
                    myCompleteMessage = Encoding.ASCII.GetString(buffer, 0, numberOfBytesRead);

                    if (myCompleteMessage.Substring(0,4) == "msg:")
                    {
                        writeLine(myCompleteMessage.Substring(4, myCompleteMessage.Length-4));
                        continue;
                    }

                    if (myCompleteMessage.Substring(0, 4) == "mmb:")
                    {
                        myCompleteMessage = myCompleteMessage.Substring(4, myCompleteMessage.Length - 4);
                        members = myCompleteMessage.Split(' ');
                        peopleList.Items.Clear();
                        foreach (var member in members)
                        {
                            peopleList.Items.Add(member);
                        }
                    }
                }
            }
            catch (IOException e)
            {
                Console.WriteLine("Failed");
                Console.WriteLine(e.ToString());
            }
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            string message = textToSend.Text;
            var data = Encoding.UTF8.GetBytes("msg:"+message);
            ns.Write(data);
        }

        

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                var data = Encoding.UTF8.GetBytes("disconnect");
                ns.Write(data);
            }
            catch (Exception){}
        }
    }
}