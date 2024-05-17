using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace CoreWCFDemoServer.Migrations
{
    /// <inheritdoc />
    public partial class passNum : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "PassportNumber",
                table: "Tickets",
                type: "int",
                nullable: false,
                defaultValue: 0);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "PassportNumber",
                table: "Tickets");
        }
    }
}
