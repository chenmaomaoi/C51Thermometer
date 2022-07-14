using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace WebAPI.DB.Domain
{
    /// <summary>
    /// 用户
    /// </summary>
    [Table(nameof(User))]
    public class User
    {
        /// <summary>
        /// 默认生成GUID，注册时间
        /// </summary>
        public User()
        {
            GUID = Guid.NewGuid().ToString();
            RegistTime = DateTime.Now;
        }

        /// <summary>
        /// GUID
        /// </summary>
        [Key]
        [Required]
        public string GUID { get; set; }

        /// <summary>
        /// 用户名
        /// </summary>
        [Required]
        public string UserName { get; set; }

        /// <summary>
        /// 密码Hash，生成方法：Hash(密码+注册时间)
        /// </summary>
        [Required]
        public int PasswordHashCode { get; set; }

        /// <summary>
        /// 注册时间
        /// </summary>
        [Required]
        public DateTime RegistTime { get; set; }
    }
}