using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ThermometerServer.DB.Domain
{
    [Table(nameof(ApplicationDB))]
    public class ApplicationDB
    {
        public ApplicationDB()
        {
            GUID = Guid.NewGuid().ToString();
            LastUpdateTime = DateTime.Now;
            Effective = true;
        }

        [Key]
        [Required]
        public string GUID { get; set; }

        [Required]
        public DateTime LastUpdateTime { get; set; }

        [Required]
        public int T { get; set; }

        public float Tf { get; set; }

        [Required]
        public int RH { get; set; }

        public float RHf { get; set; }

        public bool Effective { get; set; }
    }
}
