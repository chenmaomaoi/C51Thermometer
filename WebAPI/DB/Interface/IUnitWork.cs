using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace WebAPI.DB.Interface
{
    public interface IUnitWork<U> where U : BaseDBContext
    {
        U GetDbContext();

        void ChangeDbContext(string dbcon);

        /// <summary>
        /// EF默认情况下，每调用一次SaveChanges()都会执行一个单独的事务
        /// 本接口实现在一个事务中可以多次执行SaveChanges()方法
        /// </summary>
        void ExecuteWithTransaction(Action action);

        T FindSingle<T>(Expression<Func<T, bool>> exp = null) where T : class;

        bool IsExist<T>(Expression<Func<T, bool>> exp) where T : class;

        IQueryable<T> Find<T>(Expression<Func<T, bool>> exp = null) where T : class;

        IQueryable<T> Finds<T>(Expression<Func<T, bool>> exp = null) where T : class;

        IQueryable<T> Find<T>(int pageindex = 1, int pagesize = 10, string orderby = "", Expression<Func<T, bool>> exp = null) where T : class;

        int GetCount<T>(Expression<Func<T, bool>> exp = null) where T : class;

        void Add<T>(T entity) where T : class;

        void BatchAdd<T>(List<T> entities) where T : class;

        void BatchUpdateClass<T>(List<T> entities) where T : class;

        /// <summary>
        /// 更新一个实体的所有属性
        /// </summary>
        void Update<T>(T entity) where T : class;

        void Delete<T>(T entity) where T : class;

        /// <summary>
        /// 实现按需要只更新部分更新
        /// 如：Update<T>(u =>u.Id==1,u =>new User{Name="ok"}) where T:class;
        /// </summary>
        /// <param name="where">更新条件</param>
        /// <param name="entity">更新后的实体</param>
        void Update<T>(Expression<Func<T, bool>> where, Expression<Func<T, T>> entity) where T : class;

        /// <summary>
        /// 批量删除
        /// </summary>
        void Delete<T>(Expression<Func<T, bool>> exp) where T : class;

        void Save();

        dynamic ExecuteStoredProcedureSql(string sql, SQLiteParameter[] parameters);

        int ExecuteSql(string sql);

        int ExecuteSql(string sql, SQLiteParameter[] parameters);

        /// <summary>
        /// 使用SQL脚本查询
        /// </summary>
        /// <typeparam name="T"> T为数据库实体</typeparam>
        /// <returns></returns>
        IQueryable<T> FromSql<T>(string sql, params object[] parameters) where T : class;

        ///// <summary>
        ///// 使用SQL脚本查询
        ///// </summary>
        ///// <typeparam name="T"> T为非数据库实体，需要在DbContext中增加对应的DbQuery</typeparam>
        ///// <returns></returns>
        //IQueryable<T> Query<T>(string sql, params object[] parameters) where T : class;
    }
}
