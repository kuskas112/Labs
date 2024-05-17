namespace Sample
{
    using System;
    using System.Collections;
    using System.Diagnostics;
    using System.Numerics;
    using Nwc.XmlRpc;

    class SampleServer
    {
        const int PORT = 5050;

        static public void WriteEntry(String msg, LogLevel level)
        {
            if (level > LogLevel.Information) // ignore debug msgs
                Console.WriteLine("{0}: {1}", level, msg);
        }

        public static void Main()
        {
            Logger.Delegate = new Logger.LoggerDelegate(WriteEntry);

            XmlRpcServer server = new XmlRpcServer(PORT);
            server.Add("sample", new SampleServer());
            Console.WriteLine("Web Server Running on port {0} ... Press ^C to Stop...", PORT);
            server.Start();
        }

        
        public ArrayList MyFunc(ArrayList matrix, int size)
        {
            
            var min = new int[2];
            var minValue = 10000000;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if ((int)matrix[size*i+j] < minValue)
                    {
                        minValue = (int)matrix[size * i + j];
                        min[0] = i;
                        min[1] = j;
                    }
                }
            }

            int currentI = min[0], currentJ = min[1];

            do
            {
                matrix[size * currentI + currentJ] = 0;
                for (int j = 0; j < currentJ; j++)
                {
                    matrix[size * currentI + j] = (int)matrix[size * currentI + j] * (int)matrix[size * currentI + j];
                }
                currentJ--;
                currentI--;

            } while (currentI > 0 && currentJ > 0);
            currentI = min[0] + 1;
            currentJ = min[1] + 1;
            while (currentI < size && currentJ < size)
            {

                matrix[size * currentI + currentJ] = 0;
                for (int j = 0; j < currentJ; j++)
                {
                    matrix[size * currentI + j] = (int)matrix[size * currentI + j] * (int)matrix[size * currentI + j];
                }
                currentJ++;
                currentI++;

            }
            for (int i = currentI; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    matrix[i * size + j] = (int)matrix[i * size + j] * (int)matrix[i * size + j];
                }
            }

            return matrix;
        }
    }
}