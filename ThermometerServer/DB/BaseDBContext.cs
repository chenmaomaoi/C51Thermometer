using SQLite.CodeFirst;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        public DbSet<RAWData> RawData { get; set; }
    }

    [Table("T_RAWData")]
    public class RAWData
    {
        [Key]
        [Required]
        public string GUID { get; set; }

        [Required]
        public DateTime LastUpdateTime { get; set; }

        [Required]
        public Int16 T { get; set; }

        [Required]
        public Int16 RH { get; set; }

        [Required]
        public bool Effective { get; set; }
    }
}
