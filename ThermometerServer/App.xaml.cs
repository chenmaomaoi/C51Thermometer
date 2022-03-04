using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Cowboy.Sockets;
using ThermometerServer.DB;

namespace ThermometerServer
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            Global.tcpServer = new TcpSocketServer(1234, new TcpSocketServerConfiguration
            {
                FrameBuilder = new RawBufferFrameBuilder()
            });
            //todo:连接SQLite数据库，EF
            var context = new BaseDBContext();

            var s = new RAWData
            {
                GUID = Guid.NewGuid().ToString(),
                T = 12,
                RH = 55,
                LastUpdateTime = DateTime.Now
            };

            context.RawData.Add(s);
            context.SaveChanges();


            new MainWindow().Show();
        }
    }
}
