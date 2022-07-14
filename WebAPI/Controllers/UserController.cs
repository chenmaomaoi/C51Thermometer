using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Web;
using System.Web.Http;
using System.Web.Security;
using System.Web.UI.WebControls;
using WebAPI.App_Start;
using WebAPI.DB.Domain;

namespace WebAPI.Controllers
{
    /// <summary>
    /// 用户管理
    /// </summary>
    public class UserController : BaseApiController
    {
        /// <summary>
        /// 登录
        /// </summary>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        [AllowAnonymous]
        [HttpPost]
        public object Login(string username, string password)
        {
            User user = UnitWork.GetDbContext().Users.Where(x => x.UserName == username).FirstOrDefault();
            //验证密码
            if (user == null || ((password + user.RegistTime).GetHashCode() != user.PasswordHashCode))
            {
                return Json(new { ret = 0, data = "", msg = "用户名密码错误" });
            }

            FormsAuthenticationTicket token = new FormsAuthenticationTicket(0, username, DateTime.Now, DateTime.Now.AddHours(12), true, $"{username}&{password}", FormsAuthentication.FormsCookiePath);
            //返回登录结果、用户信息、用户验证票据信息
            var _token = FormsAuthentication.Encrypt(token);
            //将身份信息保存在session中，验证当前请求是否是有效请求
            LoginID = username;
            Token = _token;
            HttpContext.Current.Session[LoginID] = _token;

            return Json(new { ret = 1, data = _token, msg = "登录成功！" });
        }

        /// <summary>
        /// 注册账户
        /// </summary>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        [AllowAnonymous]
        [HttpPost]
        public object Regist(string username,string password)
        {
            if (UnitWork.Find<User>(p => p.UserName == username).FirstOrDefault() != null)
            {
                return Json(new { ret = 0, data = "", msg = "该用户已注册" });
            }
            var u = new User()
            {
                GUID = Guid.NewGuid().ToString(),
                UserName = username,
                RegistTime = DateTime.Now
            };

            u.PasswordHashCode = (password + u.RegistTime).GetHashCode();

            UnitWork.Add(u);
            UnitWork.Save();

            return true;
        }

        /// <summary>
        /// 测试
        /// </summary>
        /// <returns></returns>
        [TokenCheckFilter]
        [HttpGet]
        public string Test()
        {
            return "测试成功";
        }
    }
}
