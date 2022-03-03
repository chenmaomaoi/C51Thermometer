using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Cowboy.Sockets;

namespace ThermometerServer
{
    public static class Global
    {
        public static TcpSocketServer tcpServer { get; set; }

    }
}
