using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Cowboy.Sockets;
using WebAPI.DB;

namespace WebAPI
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        public static TcpSocketServer tcpServer { get; set; }

        public static UnitWork<BaseDBContext> UnitWork { get; set; }

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            tcpServer = new TcpSocketServer(1234, new TcpSocketServerConfiguration
            {
                FrameBuilder = new RawBufferFrameBuilder()
            });

            UnitWork = new UnitWork<BaseDBContext>(new BaseDBContext());

            new MainWindow().Show();
        }
    }
}
