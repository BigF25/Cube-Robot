using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
namespace CHTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
        }
        /// <summary>
        /// 打开采集卡
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenDevice_Click(object sender, EventArgs e)
        {
            int ret = DvrshMethod.InitDVRS();
            if (ret == 0)
            {
                OpenDevice.Enabled = false;
            }
            RECT r;
            r.left = V_CH1.Left;
            r.right = V_CH1.Right;
            r.top = V_CH1.Top;
            r.bottom = V_CH1.Bottom;
            DvrshMethod.OpenVideoPreview(0, V_CH1.Handle, ref r);

            r.left = V_CH2.Left;
            r.right = V_CH2.Right;
            r.top = V_CH2.Top;
            r.bottom = V_CH2.Bottom;
            DvrshMethod.OpenVideoPreview(1, V_CH2.Handle, ref r);

            r.left = V_CH3.Left;
            r.right = V_CH3.Right;
            r.top = V_CH3.Top;
            r.bottom = V_CH3.Bottom;
            DvrshMethod.OpenVideoPreview(2, V_CH3.Handle, ref r);

            r.left = V_CH4.Left;
            r.right = V_CH4.Right;
            r.top = V_CH4.Top;
            r.bottom = V_CH4.Bottom;
            DvrshMethod.OpenVideoPreview(3, V_CH4.Handle, ref r);
            System.Threading.Thread.Sleep(3000);
            OpenDevice.BackColor = Color.Red;
            this.CheckFlagTimer.Enabled = true;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            DvrshMethod.ExitDVRS();
           
        }
        private void CAP_Click(object sender, EventArgs e)
        {
            CapPictureFirstTime();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            CapPictureSecondTime();
        }
        /// <summary>
        /// 第一次采集图像
        /// </summary>
        void CapPictureFirstTime()
        {
            try
            {
                DvrshMethod.SaveCaptureImage(0, @"./Bridge/00.bmp");
                DvrshMethod.SaveCaptureImage(1, @"./Bridge/01.bmp");
                DvrshMethod.SaveCaptureImage(2, @"./Bridge/02.bmp");
                DvrshMethod.SaveCaptureImage(3, @"./Bridge/03.bmp");
            }
            catch { }
        }
        void CapPictureSecondTime()
        {
            try
            {
                DvrshMethod.SaveCaptureImage(0, @"./Bridge/10.bmp");
                DvrshMethod.SaveCaptureImage(1, @"./Bridge/11.bmp");
                DvrshMethod.SaveCaptureImage(2, @"./Bridge/12.bmp");
                DvrshMethod.SaveCaptureImage(3, @"./Bridge/13.bmp");
            }
            catch { }
        }
        private void CheckFlagTimer_Tick(object sender, EventArgs e)
        {

            if (!FlagExist("StopPictureFirstTimeFlag"))
            {
                this.CheckFlagTimer.Enabled = false;
                CapPictureFirstTime();
                //CreatFlag("FirstPictureOkFlag");
                //DeleteFlag("GetPictureFirstTimeFlag");
                this.CheckFlagTimer.Enabled = true;
            }
            if (FlagExist("GetPictureSecondTimeFlag"))
            {
                this.CheckFlagTimer.Enabled = false;
                CapPictureSecondTime();
                CreatFlag("SecondPictureOkFlag");
                DeleteFlag("GetPictureSecondTimeFlag");
                this.CheckFlagTimer.Enabled = true;
            }
        }
        /// <summary>
        /// 用于在Brige中创建，删除，判断是否存在flag
        /// </summary>
        /// <param name="str"></param>
        void CreatFlag(string str)
        {
            FileStream fs = new FileStream(@"./Bridge/" + str + ".txt", FileMode.Create);
            fs.Close();
        }
        void DeleteFlag(string str)
        {
            if (FlagExist(str))
            {
                System.Threading.Thread.Sleep(5);
                System.IO.File.Delete(@"./Bridge/" + str + ".txt");
            }
        }
        bool FlagExist(string str)
        {
            return System.IO.File.Exists(@"./Bridge/" + str + ".txt");
        }
    }
}
