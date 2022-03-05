using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Cowboy.Sockets;
using System.Timers;
using ThermometerServer.DB;
using ThermometerServer.DB.Domain;

namespace ThermometerServer
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Timer timer;
        BaseDBContext dbContext;

        public MainWindow()
        {
            InitializeComponent();
            App.tcpServer.ClientConnected += TcpServer_ClientConnected;
            App.tcpServer.ClientDisconnected += TcpServer_ClientDisconnected;
            App.tcpServer.ClientDataReceived += TcpServer_ClientDataReceived;

            timer = new Timer();
            timer.Interval = 1000;
            timer.AutoReset = true;
            timer.Elapsed += Timer_Elapsed;

            dbContext = new BaseDBContext();
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            if (App.tcpServer.IsListening && App.tcpServer.SessionCount > 0)
            {
                App.tcpServer.Broadcast(Encoding.Default.GetBytes("C:"));
            }
        }

        private void TcpServer_ClientConnected(object sender, TcpClientConnectedEventArgs e)
        {
            timer.Start();
            this.Dispatcher.Invoke(new Action(() => {
                logText.Text += "TCP Connect:" + e.Session + "\n";
                bbb.IsEnabled = true;}));
        }

        private void TcpServer_ClientDisconnected(object sender, TcpClientDisconnectedEventArgs e)
        {
            if (App.tcpServer.SessionCount < 1)
            {
                timer.Stop();
            }
            this.Dispatcher.Invoke(new Action(() => {
                logText.Text += "TCP Disconnect:" + e.Session + "\n";
                bbb.IsEnabled = false;
            }));
        }

        private void TcpServer_ClientDataReceived(object sender, TcpClientDataReceivedEventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                //处理数据

                if (Utils.CRC_8.CRC_8_Check(new byte[] { e.Data[e.DataOffset], e.Data[e.DataOffset + 1] }, 2, e.Data[e.DataOffset + 2])
                 && Utils.CRC_8.CRC_8_Check(new byte[] { e.Data[e.DataOffset + 3], e.Data[e.DataOffset + 4] }, 2, e.Data[e.DataOffset + 5]))
                {
                    UInt16[] buffer = new UInt16[2];
                    buffer[0] = e.Data[e.DataOffset];
                    buffer[0] <<= 8;
                    buffer[0] |= e.Data[e.DataOffset + 1];

                    buffer[1] = e.Data[e.DataOffset + 3];
                    buffer[1] <<= 8;
                    buffer[1] |= e.Data[e.DataOffset + 4];

                    float SHT_30_T = (175.0f * buffer[0] / 65535.0f) - 45.0f;
                    float SHT_30_RH = 100.0f * buffer[1] / 65535.0f;

                    var v = new DB.Domain.ApplicationDB
                    {
                        GUID = Guid.NewGuid().ToString(),
                        LastUpdateTime = DateTime.Now,
                        T = buffer[0],
                        Tf = SHT_30_T,
                        RH = buffer[1],
                        RHf = SHT_30_RH
                    };

                    App.UnitWork.Add(v);
                    App.UnitWork.Save();

                    //dbContext.ApplicationDB.Add(new DB.Domain.ApplicationDB
                    //{
                    //    GUID = Guid.NewGuid().ToString(),
                    //    LastUpdateTime = DateTime.Now,
                    //    T = buffer[0],
                    //    Tf = SHT_30_T,
                    //    RH = buffer[1],
                    //    RHf = SHT_30_RH
                    //});


                    //dbContext.SaveChanges();

                    //string text = Encoding.ASCII.GetString(e.Data, e.DataOffset, e.DataLength);

                    logText.Text = $"T:{SHT_30_T} RH:{SHT_30_RH} \n";
                }
                else
                {
                    logText.Text += $"{Encoding.ASCII.GetString(e.Data, e.DataOffset, e.DataLength)}\n";
                }
            }));
        }


        private void btnControl_Click(object sender, RoutedEventArgs e)
        {
            if (App.tcpServer.IsListening)
            {
                App.tcpServer.Shutdown();
                btnControl.Content = "开始服务";
            }
            else
            {
                App.tcpServer.Listen();
                btnControl.Content = "停止服务";
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            App.tcpServer.Broadcast(Encoding.Default.GetBytes("C:"));
        }
    }
}
