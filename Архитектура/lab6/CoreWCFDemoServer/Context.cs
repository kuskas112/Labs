using Microsoft.EntityFrameworkCore;

namespace CoreWCFDemoServer
{
    public class Context : DbContext
    {
        public DbSet<Race> Races { get; set; }
        public DbSet<Ticket> Tickets { get; set; }

        public Context()
        {
            Database.EnsureCreated();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer("Server=(localdb)\\mssqllocaldb;Database=helloappdb;Trusted_Connection=True;");
        }
    }
}
