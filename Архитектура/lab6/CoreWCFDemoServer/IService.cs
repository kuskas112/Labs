using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Linq;
using CoreWCF;
using System.Data;

namespace CoreWCFDemoServer
{
    [ServiceContract]
    public interface IService
    {
        [OperationContract]
        Race[] GetRacesByPlaces(string from, string to);
        [OperationContract]
        string OrderTicket(Ticket ticket);
        [OperationContract]
        Race GetRaceById(int id);
        //сделать валидацию тикета и проверку на наличие мест
    }

}
