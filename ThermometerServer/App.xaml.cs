using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Cowboy.Sockets;

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

            new MainWindow().Show();
        }
    }
}
