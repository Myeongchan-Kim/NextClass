using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Http;


namespace WebAPI_SelfHosting.Request
{

    class LoginController : ApiController
    {
        [Route("Request/Login")]
        [HttpPost]
        public string Login()
        {
            //if (name == "111")
            //    return "LoginSuccess.";
            //else
            //    return "Login Fail.";
            return "hi.";
        }
    }
}
