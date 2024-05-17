using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using System.Runtime.Serialization;

namespace CoreWCFDemoServer
{
    [DataContract]
    public class Race
    {
        [DataMember]
        public int Id { get; set; }
        [DataMember]
        public string From { get; set; }
        [DataMember]
        public string To { get; set; }
        [DataMember]
        public string Company { get; set; }
        [DataMember]
        public DateTime Date { get; set; }
        [DataMember]
        public int FreeSeats { get; set; }
    }
}
