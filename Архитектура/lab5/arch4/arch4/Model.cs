using System;
using System.Xml;
using System.Xml.Linq;
using ServiceReference1;

namespace arch4
{
    class Model : IModel
    {
        public XDocument GetCurseOnDate(DateTime dateTime)
        {
            DailyInfoSoapClient service = new DailyInfoSoapClient(DailyInfoSoapClient.EndpointConfiguration.DailyInfoSoap12);
            GetCursOnDateXMLRequest req = new GetCursOnDateXMLRequest(dateTime);
            GetCursOnDateXMLResponse resp = service.GetCursOnDateXML(req);
            XmlNode result = resp.GetCursOnDateXMLResult;
            XDocument doc = XDocument.Parse(result.OuterXml);
            return doc;
        }

        public XDocument EnumReutersValutesXML()
        {

            DailyInfoSoapClient service = new DailyInfoSoapClient(DailyInfoSoapClient.EndpointConfiguration.DailyInfoSoap12);
            EnumReutersValutesXMLRequest req = new EnumReutersValutesXMLRequest();
            EnumReutersValutesXMLResponse resp = service.EnumReutersValutesXML(req);
            XmlNode result = resp.EnumReutersValutesXMLResult;
            XDocument doc = XDocument.Parse(result.OuterXml);
            return doc;
        }

        public XDocument MainInfoXML()
        {
            DailyInfoSoapClient service = new DailyInfoSoapClient(DailyInfoSoapClient.EndpointConfiguration.DailyInfoSoap12);
            MainInfoXMLRequest req = new MainInfoXMLRequest();
            MainInfoXMLResponse resp = service.MainInfoXML(req);
            XDocument doc = XDocument.Parse(resp.MainInfoXMLResult.OuterXml);
            return doc;
        }

        public XDocument mrrf7DXML(DateTime fromDate, DateTime toDate)
        {
            DailyInfoSoapClient service = new DailyInfoSoapClient(DailyInfoSoapClient.EndpointConfiguration.DailyInfoSoap12);
            mrrf7DXMLRequest req = new mrrf7DXMLRequest(fromDate, toDate);
            mrrf7DXMLResponse resp = service.mrrf7DXML(req);
            XDocument doc = XDocument.Parse(resp.mrrf7DXMLResult.OuterXml);
            return doc;
        }
    }
}
