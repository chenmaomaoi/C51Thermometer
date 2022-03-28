using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Web;
using System.Web.Helpers;
using System.Web.Http;
using System.Web.Http.Controllers;
using System.Web.Security;

namespace WebAPI.App_Start
{
    /// <summary>
    /// token验证
    /// </summary>
    public class TokenCheckFilter : AuthorizeAttribute
    {

        /// <summary>
        /// 重写基类的验证方式，加入自定义的Ticket验证
        /// </summary>
        /// <param name="actionContext"></param>
        public override void OnAuthorization(HttpActionContext actionContext)
        {
            var content = actionContext.Request.Properties["MS_HttpContext"] as HttpContextBase;
            //获取token（请求头里面的值）
            var token = HttpContext.Current.Request.Headers["Token"] ?? "";
            //是否为空
            if (!string.IsNullOrEmpty(token.ToString()))
            {
                //解密用户ticket,并校验用户名密码是否匹配
                if (ValidateTicket(token.ToString()))
                    base.IsAuthorized(actionContext);
                else
                    HandleUnauthorizedRequest(actionContext);
            }
            //如果取不到身份验证信息，并且不允许匿名访问，则返回未验证403
            else
            {
                var attributes = actionContext.ActionDescriptor.GetCustomAttributes<AllowAnonymousAttribute>().OfType<AllowAnonymousAttribute>();
                bool isAnonymous = attributes.Any(a => a is AllowAnonymousAttribute);
                if (isAnonymous) base.OnAuthorization(actionContext);
                else HandleUnauthorizedRequest(actionContext);
            }
        }

        //校验用户名密码（对Session匹配，或数据库数据匹配）
        private bool ValidateTicket(string encryptToken)
        {
            //解密Ticket
            var strTicket = FormsAuthentication.Decrypt(encryptToken).UserData;
            //从Ticket里面获取用户名和密码
            var index = strTicket.IndexOf("&");
            string userName = strTicket.Substring(0, index);
            string password = strTicket.Substring(index + 1);
            //取得session，不通过说明用户退出，或者session已经过期
            var token = HttpContext.Current.Session[userName];
            if (token == null)
                return false;
            //对比session中的令牌
            if (token.ToString() == encryptToken)
                return true;
            return false;
        }

        /// <summary>
        /// 重写HandleUnauthorizedRequest
        /// </summary>
        /// <param name="filterContext"></param>
        protected override void HandleUnauthorizedRequest(HttpActionContext filterContext)
        {
            base.HandleUnauthorizedRequest(filterContext);

            var response = filterContext.Response = filterContext.Response ?? new HttpResponseMessage();
            //状态码401改为其他状态码来避免被重定向。最合理的是改为403，表示服务器拒绝。
            response.StatusCode = HttpStatusCode.Forbidden;
            var content = new
            {
                success = false,
                errs = new[] { "服务端拒绝访问：你没有权限?，或者掉线了?" }
            };
            response.Content = new StringContent(Json.Encode(content), Encoding.UTF8, "application/json");
        }

    }
}