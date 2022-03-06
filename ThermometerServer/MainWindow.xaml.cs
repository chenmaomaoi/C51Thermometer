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
using System.IO;

namespace ThermometerServer
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Timer timer;

        public MainWindow()
        {
            InitializeComponent();
            App.tcpServer.ClientConnected += TcpServer_ClientConnected;
            App.tcpServer.ClientDisconnected += TcpServer_ClientDisconnected;
            App.tcpServer.ClientDataReceived += TcpServer_ClientDataReceived;

            timer = new Timer
            {
                Interval = 1000,
                AutoReset = true
            };
            timer.Elapsed += Timer_Elapsed;
            ChartWebBrowser.Navigate(new Uri(Directory.GetCurrentDirectory() + "/Chart.html"));
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            btnGet8052Data_Click(sender, new RoutedEventArgs());
        }

        private void TcpServer_ClientConnected(object sender, TcpClientConnectedEventArgs e)
        {
            timer.Start();
            this.Dispatcher.Invoke(new Action(() =>
            {
                logText.Text += "TCP Connect:" + e.Session;
                btnGet8052Data.IsEnabled = true;
            }));
        }

        private void TcpServer_ClientDisconnected(object sender, TcpClientDisconnectedEventArgs e)
        {
            if (App.tcpServer.SessionCount < 1)
            {
                timer.Stop();
            }
            this.Dispatcher.Invoke(new Action(() =>
            {
                logText.Text = "TCP Disconnect:" + e.Session;
                btnGet8052Data.IsEnabled = false;
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

                    var v = new DB.Domain.MainTable
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

                    logText.Text = $"T:{SHT_30_T} RH:{SHT_30_RH}";
                    icoDataErr.Visibility = Visibility.Hidden;
                }
                else
                {
                    logText.Text = $"{Encoding.ASCII.GetString(e.Data, e.DataOffset, e.DataLength)}";
                    icoDataErr.Visibility = Visibility.Visible;
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

        private void btnGet8052Data_Click(object sender, RoutedEventArgs e)
        {
            if (App.tcpServer.IsListening && App.tcpServer.SessionCount > 0)
            {
                App.tcpServer.Broadcast(Encoding.Default.GetBytes("C:"));
            }
        }
    }
}
