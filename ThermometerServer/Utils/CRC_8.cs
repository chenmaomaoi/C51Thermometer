using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThermometerServer.Utils
{
    public static class CRC_8
    {
        /// <summary>
        /// CRC-8 计算
        /// </summary>
        /// <param name="check_data"></param>
        /// <param name="num_of_data"></param>
        /// <returns></returns>
        private static byte CRC_8_Compute(byte[] check_data, uint num_of_data)
        {
            byte bit_mask;        // bit mask
            byte crc = 0xFF; // calculated checksum
            byte byteCtr;    // byte counter

            // calculates 8-Bit checksum with given polynomial
            for (byteCtr = 0; byteCtr < num_of_data; byteCtr++)
            {
                crc ^= (check_data[byteCtr]);
                //crc校验，最高位是1就^0x31
                for (bit_mask = 8; bit_mask > 0; --bit_mask)
                {
                    if ((crc & 0x80) != 0)
                    {
                        crc = (byte)((crc << 1) ^ 0x31);
                    }
                    else
                    {
                        crc = ((byte)(crc << 1));
                    }
                }
            }
            return crc;
        }

        /// <summary>
        /// CRC-8校验
        /// </summary>
        /// <param name="p"></param>
        /// <param name="num_of_data"></param>
        /// <param name="crc_data"></param>
        /// <returns></returns>
        public static bool CRC_8_Check(byte[] p, uint num_of_data, byte crc_data)
        {
            return CRC_8_Compute(p, num_of_data) == crc_data;
        }

    }
}
