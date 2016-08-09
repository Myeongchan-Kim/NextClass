using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Owin.Hosting;
using System.Net.Http;

namespace WebAPI_SelfHosting
{
    class Program
    {
        static void Main(string[] args)
        {
            string baseAddress = "http://localhost:19000/";
            //string baseAddress = "http://*:19000/";

            using (WebApp.Start<Startup>(url: baseAddress))
            {
                Console.WriteLine("Web API 실행 중 " + baseAddress);   
                Console.ReadLine();
            }

        }
    }
}
