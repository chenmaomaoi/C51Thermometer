using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebAPI.DB.Domain
{
    /// <summary>
    /// 存储温湿度信息
    /// </summary>
    [Table(nameof(Thermometer))]
    public class Thermometer
    {
        /// <summary>
        /// 默认生产GUID，最后一次更新时间，数据有效
        /// </summary>
        public Thermometer()
        {
            GUID = Guid.NewGuid().ToString();
            LastUpdateTime = DateTime.Now;
            Effective = true;
        }

        /// <summary>
        /// GUID
        /// </summary>
        [Key]
        [Required]
        public string GUID { get; set; }

        /// <summary>
        /// 最后一次更新时间
        /// </summary>
        [Required]
        public DateTime LastUpdateTime { get; set; }

        /// <summary>
        /// 温度(传感器原始数据)
        /// </summary>
        [Required]
        public int T { get; set; }

        /// <summary>
        /// 湿度(传感器原始数据)
        /// </summary>
        [Required]
        public int RH { get; set; }

        /// <summary>
        /// 数据有效性
        /// </summary>
        public bool Effective { get; set; }
    }
}
