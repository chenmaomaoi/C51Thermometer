using SQLite.CodeFirst;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebAPI.DB.Domain;

namespace WebAPI.DB
{
    public class BaseDBContext : DbContext
    {
        public BaseDBContext() : base("DataBase") { }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            //如果不存在数据库，则创建
            Database.SetInitializer(new SqliteCreateDatabaseIfNotExists<BaseDBContext>(modelBuilder));
        }

        //在此处添加实体
        public DbSet<Thermometer> ApplicationDB { get; set; }

        public DbSet<User> Users { get; set; }
    }
}
