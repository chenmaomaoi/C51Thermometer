using SQLite.CodeFirst;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ThermometerServer.DB.Domain;

namespace ThermometerServer.DB
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
        public DbSet<MainTable> ApplicationDB { get; set; }
    }
}
