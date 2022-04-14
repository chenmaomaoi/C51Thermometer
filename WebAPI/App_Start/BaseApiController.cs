using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Http;
using WebAPI.DB.Domain;
using WebAPI.DB.Interface;
using WebAPI.DB;

namespace WebAPI.App_Start
{
    /// <summary>
    /// 基础Api控制器  所有的都继承他
    /// </summary>
    public class BaseApiController : ApiController
    {
        /// <summary>
        /// 构造函数赋值
        /// </summary>
        public BaseApiController()
        {
            Token = HttpContext.Current.Session[LoginID] ?? "";
            //HttpContext.Current.Request.Headers.Add(nameof(Token), Token.ToString());
        }

        /// <summary>
        /// 数据库上下文
        /// </summary>
        //public WYDBContext db = WYDBContextFactory.GetDbContext();

        public IUnitWork<BaseDBContext> UnitWork = new DB.UnitWork<BaseDBContext>(new DB.BaseDBContext());

        /// <summary>
        /// token值 登录后赋值请求api的时候添加到header中
        /// </summary>
        public static object Token { get; set; } = "";

        /// <summary>
        /// 登录者账号
        /// </summary>
        public static string LoginID { get; set; } = "";
    }
}