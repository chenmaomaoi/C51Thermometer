using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Linq.Dynamic;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using WebAPI.DB.Interface;
using System.Data.SQLite;
using Z.EntityFramework.Plus;

namespace WebAPI.DB
{
    public class UnitWork<U> : IUnitWork<U> where U : BaseDBContext
    {
        private U _context;

        public UnitWork(U context)
        {
            _context = context;
        }

        public U GetDbContext()
        {
            return _context;
        }

        /// <summary>
        /// 变更数据库连接
        /// </summary>
        /// <param name="dbcon"></param>
        public void ChangeDbContext(string dbcon)
        {
            if (string.IsNullOrEmpty(dbcon)) return;
            _context.Database.Connection.ConnectionString = dbcon;
        }

        /// <summary>
        /// EF默认情况下，每调用一次SaveChanges()都会执行一个单独的事务
        /// 本接口实现在一个事务中可以多次执行SaveChanges()方法
        /// </summary>
        public void ExecuteWithTransaction(Action action)
        {
            using (var transaction = _context.Database.BeginTransaction())
            {
                try
                {
                    action();
                    _context.SaveChanges();
                    transaction.Commit();
                }
                catch (Exception ex)
                {
                    transaction.Rollback();
                    throw ex;
                }
            }
        }

        /// <summary>
        /// 根据过滤条件，获取记录
        /// </summary>
        /// <param name="exp">The exp.</param>
        public IQueryable<T> Find<T>(Expression<Func<T, bool>> exp = null) where T : class
        {
            return Filter(exp);
        }

        /// <summary>
        /// 根据过滤条件，获取记录
        /// </summary>
        /// <param name="exp">The exp.</param>
        public IQueryable<T> Finds<T>(Expression<Func<T, bool>> exp = null) where T : class
        {
            return Filters(exp);
        }

        public bool IsExist<T>(Expression<Func<T, bool>> exp) where T : class
        {
            return _context.Set<T>().Any(exp);
        }

        /// <summary>
        /// 查找单个
        /// </summary>
        public T FindSingle<T>(Expression<Func<T, bool>> exp) where T : class
        {
            return _context.Set<T>().AsNoTracking().FirstOrDefault(exp);
        }

        /// <summary>
        /// 得到分页记录
        /// </summary>
        /// <param name="pageindex">The pageindex.</param>
        /// <param name="pagesize">The pagesize.</param>
        /// <param name="orderby">排序，格式如："Id"/"Id descending"</param>
        public IQueryable<T> Find<T>(int pageindex, int pagesize, string orderby, Expression<Func<T, bool>> exp = null) where T : class
        {
            if (pageindex < 1) pageindex = 1;
            if (pagesize < 0) pagesize = 10;
            //if (string.IsNullOrEmpty(orderby))
            //    orderby = "Id descending";

            return Filter(exp).OrderBy(orderby).Skip(pagesize * (pageindex - 1)).Take(pagesize);
        }

        /// <summary>
        /// 根据过滤条件获取记录数
        /// </summary>
        public int GetCount<T>(Expression<Func<T, bool>> exp = null) where T : class
        {
            return Filter(exp).Count();
        }

        public void Add<T>(T entity) where T : class
        {
            _context.Set<T>().Add(entity);
        }

        /// <summary>
        /// 批量添加
        /// </summary>
        /// <param name="entities">The entities.</param>
        public void BatchAdd<T>(List<T> entities) where T : class
        {
            _context.Set<T>().AddRange(entities);
        }

        public void Update<T>(T entity) where T : class
        {
            var entry = this._context.Entry(entity);
            entry.State = EntityState.Modified;

            //如果数据没有发生变化
            if (!this._context.ChangeTracker.HasChanges())
            {
                entry.State = EntityState.Unchanged;
            }
        }

        public void BatchUpdateClass<T>(List<T> entities) where T : class
        {
            _context.Set<T>().BulkUpdate(entities);
        }

        public void Delete<T>(T entity) where T : class
        {
            _context.Set<T>().Remove(entity);
        }

        /// <summary>
        /// 实现按需要只更新部分更新
        /// <para>如：Update(u =>u.Id==1,u =>new User{Name="ok"});</para>
        /// </summary>
        /// <param name="where">The where.</param>
        /// <param name="entity">The entity.</param>
        public void Update<T>(Expression<Func<T, bool>> where, Expression<Func<T, T>> entity) where T : class
        {
            _context.Set<T>().Where(where).Update(entity);
        }

        public virtual void Delete<T>(Expression<Func<T, bool>> exp) where T : class
        {
            _context.Set<T>().RemoveRange(Filter(exp));
        }

        public void Save()
        {
            //try
            //{
            var transaction = _context.Database.BeginTransaction();
            _context.SaveChanges();
            transaction.Commit();
            //}
            //catch (DbEntityValidationException e)
            //{
            //    throw new Exception(e.EntityValidationErrors.First().ValidationErrors.First().ErrorMessage);
            //}
        }

        private IQueryable<T> Filter<T>(Expression<Func<T, bool>> exp) where T : class
        {
            var dbSet = _context.Set<T>().AsNoTracking().AsQueryable();
            if (exp != null)
                dbSet = dbSet.Where(exp);
            return dbSet;
        }

        private IQueryable<T> Filters<T>(Expression<Func<T, bool>> exp) where T : class
        {
            var dbSet = _context.Set<T>().AsQueryable();
            if (exp != null)
                dbSet = dbSet.Where(exp);
            return dbSet;
        }

        /// <summary>
        /// 调用存储过程
        /// </summary>
        /// <param name="sql"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        public dynamic ExecuteStoredProcedureSql(string sql, SQLiteParameter[] sqlParams)
        {
            dynamic value;
            using (var connection = new SQLiteConnection(_context.Database.Connection.ConnectionString))
            // using (var connection = new SqlConnection(_context.Database.GetDbConnection().ConnectionString))
            {
                connection.Open();

                using (var cmd = connection.CreateCommand())
                {

                    cmd.CommandText = sql;
                    cmd.CommandType = System.Data.CommandType.StoredProcedure;
                    if (sqlParams != null) cmd.Parameters.AddRange(sqlParams);
                    value = cmd.ExecuteNonQuery();
                }
            }
            return value;
        }

        public int ExecuteSql(string sql)
        {
            return _context.Database.ExecuteSqlCommand(sql);
        }

        public int ExecuteSql(string sql, SQLiteParameter[] parameters)
        {
            return _context.Database.ExecuteSqlCommand(sql, parameters);
        }

        public IQueryable<T> FromSql<T>(string sql, params object[] parameters) where T : class
        {
            return (IQueryable<T>)_context.Set<T>().SqlQuery(sql, parameters);
        }

        //public IQueryable<T> Query<T>(string sql, params object[] parameters) where T : class
        //{
        //    return _context.Query<T>().FromSqlRaw(sql, parameters);
        //}
    }
}
