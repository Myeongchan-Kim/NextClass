using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Http;


namespace WebAPI_SelfHosting.Request
{

    public class LoginController : ApiController
    {
        public class LoginRequest
        {
            public int UserSeq { get; set; }
            public string UserID { get; set; }
            public string UserPW { get; set; }
        }

        public class LoginResponse
        {
            public string Result { get; set; }
            public string Sequence { get; set; }
            public int UserSeq { get; set; }
        }

        // /Request/Login
        [Route("Request/Login")]
        [HttpPost]
        public LoginResponse RequestLogin(LoginRequest request)
        {
            if (request.UserID == "123" && request.UserPW == "111")
            {

                return new LoginResponse
                {
                    Result = "Success",
                    Sequence = System.DateTime.Now.Ticks.ToString(),
                    UserSeq = request.UserSeq
                }; 
            }

            return new LoginResponse { Result = "LoginFail" };
        }
        
    }
}
