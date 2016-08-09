using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Owin;
using System.Web.Http;

namespace WebAPI_SelfHosting
{
    class Startup
    {
        public void Configuration(IAppBuilder appBuilder)
        {
            var config = new HttpConfiguration();

            //커스텀 매핑 룰
            config.MapHttpAttributeRoutes();
            //appBuilder.UseWebApi(config);

            // 기본 라우팅 매핑 룰
            //config.Routes.MapHttpRoute(
            //     name: "DefaultApi",
            //     routeTemplate: "api/{controller}/{id}",
            //     defaults: new { id = RouteParameter.Optional });
            appBuilder.UseWebApi(config);
        }
    }
}
