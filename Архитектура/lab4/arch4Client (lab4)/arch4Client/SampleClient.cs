namespace Sample
{
    using System;
    using System.Collections;
    using System.Diagnostics;
    using System.Numerics;
    using Nwc.XmlRpc;
    
    class SampleClient
    {
        private static String URL = "http://127.0.0.1:5050";

        public SampleClient()
        {
            Console.WriteLine("Server: " + URL);

            Console.WriteLine("Укажите размер матрицы ");
            int size = 0; 
            InputController.parseInt(ref size);
            ArrayList matrix = new ArrayList(size);

            InputController.fillMatrix(size, ref matrix);

            Console.WriteLine("Исходная матрица");

            InputController.printMatrix(size, ref matrix);
            Console.WriteLine("=============");
            
            
            XmlRpcRequest client = new XmlRpcRequest();
            client.MethodName = "sample.MyFunc";
            client.Params.Clear();
            client.Params.Add(matrix);
            client.Params.Add(size);
            Console.WriteLine(client);
            try
            {
                ArrayList response = (ArrayList)client.Invoke(URL);
                InputController.printMatrix(size, ref response);
            }
            catch (XmlRpcException serverException)
            {
                Console.WriteLine("Fault {0}: {1}", serverException.FaultCode, serverException.FaultString);
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception " + e.Message);
            }

            
        }
    }
}