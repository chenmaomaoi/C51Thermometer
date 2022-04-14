using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebAPI.DB.Domain
{
    [Table(nameof(MainTable))]
    public class MainTable
    {
        public MainTable()
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

        [Required]
        public int RH { get; set; }

        public bool Effective { get; set; }
    }
}
