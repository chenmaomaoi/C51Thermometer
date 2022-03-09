using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace WebAPI.Controllers
{
    public class ValuesController : ApiController
    {
        /// <summary>
        /// 默认Get方法
        /// </summary>
        /// <returns></returns>
        [HttpGet]
        [Route("api/Get")]
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        /// <summary>
        /// 带有ID的Get方法
        /// </summary>
        /// <param name="id"></param>
        /// <returns>value+id</returns>
        [HttpGet]
        [Route("api/Get")]
        public string Get(int id)
        {
            return "value" + id;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        [HttpPost]
        [Route("api/Post")]
        public void Post([FromBody] string value)
        {
        }

        // PUT api/values/5
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/values/5
        public void Delete(int id)
        {
        }
    }
}
