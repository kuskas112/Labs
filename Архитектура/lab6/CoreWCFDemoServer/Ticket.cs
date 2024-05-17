using System.Diagnostics.CodeAnalysis;
using Microsoft.EntityFrameworkCore;
using System.Runtime.Serialization;

namespace CoreWCFDemoServer
{
    [DataContract]
    public class Ticket
    {
        [DataMember]
        public int Id { get; set; }
        [DataMember]
        [AllowNull]
        public string Name { get; set; }
        [DataMember]
        public int PassportNumber { get; set; }
        [DataMember]
        public Race race { get; set; }
        
    }
}
