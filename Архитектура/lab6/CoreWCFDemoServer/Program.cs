using CoreWCF;
using CoreWCF.Configuration;
using CoreWCF.Description;
using CoreWCFDemoServer;
using Microsoft.EntityFrameworkCore.Metadata.Internal;

var builder = WebApplication.CreateBuilder(args);

// Add WSDL support
builder.Services.AddServiceModelServices().AddServiceModelMetadata();
builder.Services.AddSingleton<IServiceBehavior, UseRequestHeadersForMetadataAddressBehavior>();

var app = builder.Build();

// Configure an explicit none credential type for WSHttpBinding as it defaults to Windows which requires extra configuration in ASP.NET
var myWSHttpBinding = new WSHttpBinding(SecurityMode.Transport);
myWSHttpBinding.Security.Transport.ClientCredentialType = HttpClientCredentialType.None;

app.UseServiceModel(builder =>
{
    builder.AddService<Service>((serviceOptions) => { })
    // Add a BasicHttpBinding at a specific endpoint
    .AddServiceEndpoint<Service, IService>(new BasicHttpBinding(), "/Service/basichttp")
    // Add a WSHttpBinding with Transport Security for TLS
    .AddServiceEndpoint<Service, IService>(myWSHttpBinding, "/Service/WSHttps");
});

var serviceMetadataBehavior = app.Services.GetRequiredService<CoreWCF.Description.ServiceMetadataBehavior>();
serviceMetadataBehavior.HttpGetEnabled = true;
app.Run();
/*
int raceId = Convert.ToInt32(Console.ReadLine());

string? name = Console.ReadLine();

int passport = Convert.ToInt32(Console.ReadLine());

Ticket ticket = new Ticket();
ticket.race = new Race() { Id = raceId };
ticket.Name = name;
ticket.PassportNumber = passport;

Service ser = new Service();
Console.WriteLine(ser.OrderTicket(ticket));*/
