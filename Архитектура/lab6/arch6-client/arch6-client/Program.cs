using ServiceReference1;
using arch6;

// Instantiate the Service wrapper specifying the binding and optionally the Endpoint URL. The BasicHttpBinding could be used instead.
var client = new ServiceClient(ServiceClient.EndpointConfiguration.WSHttpBinding_IService, "https://localhost:5001/Service/WSHttps");

Controller controller = new Controller(client);
controller.mainLoop();