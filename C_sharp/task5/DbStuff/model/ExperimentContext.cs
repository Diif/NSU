namespace DbStuff.Model;

using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

public class ExperimentContext : DbContext
{
  public DbSet<ExperimentEntity> Experiments {get; set;}
  public ExperimentContext(DbContextOptions<ExperimentContext> options) : base(options){}

}