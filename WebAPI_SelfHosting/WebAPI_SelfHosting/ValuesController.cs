using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Http;


namespace WebAPI_SelfHosting
{
    public class ValuesController : ApiController
    {
        // GET api/values
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET api/values/5
        public string Get(string id)
        {
            return "Hello, " + id + ".";
        }

        // POST api/values  BODY - name : 
        public string Post([FromBody]string text)
        {
            Console.WriteLine("name : "+ text);
            return "Hey," + text;
        }
    }
}
