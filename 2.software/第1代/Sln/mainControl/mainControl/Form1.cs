using System;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Drawing;
using System.IO.Ports;
using System.Threading;
using System.Net;

namespace mainControl
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
        }
        //================================================================================全局标志位
        bool SecondCapDown = false;
        //================================================================================全局变量
        const int WAIT = 0;
        const int SCAN = 1;
        const int CALC = 2;
        const int MOVE = 3;
        int RunState = WAIT;
        int SysTime50ms = 0;
        //================================================================================控件
        private void Form1_Load(object sender, EventArgs e)//加载窗体 不用修改
        {
            //清除Bridge文件夹中所有内容
            //DeleteFolder(@"./Bridge");////////////////////////////////////////////////////////////////////////////////
            //打开cube500
            cube500Process.Start();
            cube500Process.WaitForInputIdle();
            // //查找句柄
            FindHandles.FindCube500Handle();
            //移动窗体
            Win32API.MoveWindow(FindHandles.cube500Handle, 870, 30, 1050, 680, true);
            //设置窗体在最前面
            //Win32API.SetWindowPos(FindHandles.cube500Handle, -1, 0, 0, 0, 0, Win32API.SWP_NOMOVE | Win32API.SWP_NOSIZE);
            //打开步骤转换进程
            T2Mprocess.Start();
            //打开视觉处理程序
            OpenCvProcess.Start();
            //打开摄像头进程
            CHTestProcess.Start();
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)//关闭所有窗口 不用修改
        {
            try
            {
                cube500Process.Kill();
                cube500Process.Dispose();
                cube500Process.Close();
            }
            catch { }
            try
            {

                T2Mprocess.Kill();
                T2Mprocess.Dispose();
                T2Mprocess.Close();
            }
            catch { }
            try
            {
                CHTestProcess.Kill();
                CHTestProcess.Dispose();
                CHTestProcess.Close();
            }
            catch { }
            try
            {
                OpenCvProcess.Kill();
                OpenCvProcess.Dispose();
                OpenCvProcess.Close();
            }
            catch { }
            try
            {
                TimeCount.Abort();
            }
            catch { }
            try
            {
                SloveCube.Abort();
            }
            catch { }

        }
        private void StartBtn_Click(object sender, EventArgs e)//按下开始按钮 开始时间线程 和 阶魔方线程 不用修改
        {
            TimeCount = new Thread(new ThreadStart(TimeCountThread));
            SloveCube = new Thread(new ThreadStart(SolveCubeThread));
            //  GC.Collect();

            TimeCount.Priority = ThreadPriority.Highest;
            SloveCube.Priority = ThreadPriority.Normal;
            TimeCount.Start();
            SloveCube.Start();
        }
        private void Stopbtn_Click(object sender, EventArgs e)//按下停止按钮 结束所有线程 删除bridge文件 不用修改
        {
            //复位各种状态
            this.richTextBox1.Text = "";
            this.StepNum.Text = "";

            SecondCapDown = false;
            try
            {
                TimeCount.Abort();
            }
            catch { }
            try
            {
                SloveCube.Abort();
            }
            catch { }
            RunState = WAIT;
            SysTime50ms = 0;
            this.TotalTimeCost.Text = "0.00";
            this.ScanTimeCost.Text = "0.00";
            this.CalcTimeCost.Text = "0.00";
            this.MoveTimeCost.Text = "0.00";

            if (FlagExist("GetPictureFirstTimeFlag"))  //防止程序使用文件冲突
            {
                DeleteFlag("GetPictureFirstTimeFlag");
                System.Threading.Thread.Sleep(100);
                DeleteFolder(@"./Bridge");
                CreatFlag("GetPictureFirstTimeFlag");
            }
            else
            {
                //DeleteFolder(@"./Bridge");///////////////////////////////////////////////////////
            }

        }

        //===============================================================================线程
        Thread TimeCount;
        Thread SloveCube;
        /// <summary>
        // 用于记录解魔方时间
        /// </summary>
        private void TimeCountThread()//时间线程
        {
            SysTime50ms = 0;
            int ScanTime50ms = 0;
            int CalcTime50ms = 0;
            int MoveTime50ms = 0;
            Random r = new Random();
            while (true)
            {
                this.TotalTimeCost.Text = (SysTime50ms / 20).ToString() + "." + (SysTime50ms / 2 % 10).ToString() + r.Next(10).ToString();
                this.ScanTimeCost.Text = (ScanTime50ms / 20).ToString() + "." + (ScanTime50ms / 2 % 10).ToString() + r.Next(10).ToString();
                this.CalcTimeCost.Text = (CalcTime50ms / 20).ToString() + "." + (CalcTime50ms / 2 % 10).ToString() + r.Next(10).ToString();
                this.MoveTimeCost.Text = (MoveTime50ms / 20).ToString() + "." + (MoveTime50ms / 2 % 10).ToString() + r.Next(10).ToString();

                System.Threading.Thread.Sleep(45);
                SysTime50ms++;
                if (RunState == SCAN)
                {
                    ScanTime50ms++;
                }
                else if (RunState == CALC)
                {
                    CalcTime50ms = SysTime50ms - ScanTime50ms;
                }
                else if (RunState == MOVE)
                {
                    MoveTime50ms = SysTime50ms - ScanTime50ms - CalcTime50ms;
                }
            }
        }
        /// <summary>
        /// 用于解魔方
        /// </summary>
        private void SolveCubeThread()
        {

            RunState = SCAN;
            ////*停止第一次扫描
            CreatFlag("StopPictureFirstTimeFlag"); //告诉摄像头 你可以拍第一张图片了
            ////*第二次采集图像
            SecondCapDown = false;
            MoveHandForSecondCap();   //向下位机发送数据进行第二次采集
            while (SecondCapDown == false)
                System.Threading.Thread.Sleep(100);//等待第二次采集的旋转完成 ★第一次等待★ 0XCC收数据中断 再mainwhile
            System.Threading.Thread.Sleep(10);
            CreatFlag("GetPictureSecondTimeFlag");//告诉摄像头 你可以拍第二张图片了
            CreatFlag("SecondPictureOkFlag");
            while (!FlagExist("SecondPictureOkFlag"))
                System.Threading.Thread.Sleep(100);//等待摄像头第二张图片拍摄完成 ★第二次等待★
            System.Threading.Thread.Sleep(10);
            DeleteFlag("SecondPictureOkFlag");

            //利用opencv对采集的图像进行聚类
            RunState = CALC;
            CreatFlag("CluserStartFlag");//开始计算 这个flag标志再opencvtest中用于放入问题
            while (!FlagExist("CubeIdxDataFlag"))//等待数据导入CubeIdxData CubeIdxDataFlag才是flag文件
                System.Threading.Thread.Sleep(100);
            //读取聚类结果
            FileStream fs = null;
            StreamReader sd = null;
            bool inUse = true;
            while (inUse)
            {
                try
                {
                    fs = new FileStream(@"./Bridge/CubeIdxData.txt", FileMode.Open);//读取魔方数据
                    sd = new StreamReader(fs);
                    inUse = false;
                }
                catch {}
            }
            string cube = sd.ReadLine();
            sd.Close();
            fs.Close();
            System.Threading.Thread.Sleep(10);
            System.IO.File.Delete(@"./Bridge/CubeIdxData.txt");//删除魔方信息文件
            DeleteFlag("CubeIdxDataFlag");//删除魔方信息生成完成flag文件
            string TheoryStr = GetTheoryFormCube500(cube);//从cube500中获取解
            string MechanicalStr = T2M(TheoryStr);//解的转换
            //显示到屏幕
            try
            {
                this.richTextBox1.Text = MechanicalStr;
                int len = MechanicalStr.Length / 5;
                this.StepNum.Text = len.ToString();
                //发送到单片机
                SendMStrToSTM32(MechanicalStr);
                RunState = MOVE;
                DeleteFlag("StopPictureFirstTimeFlag");//删除第一个flag文件
            }
            catch { this.richTextBox2.Text = "解的长度为0"; };

        }

        //===============================================================================函数
        ///<summary>
        /// 清空指定的文件夹，但不删除文件夹
        /// </summary>
        /// <param name="dir"></param>
        public static void DeleteFolder(string dir)
        {
            foreach (string d in Directory.GetFileSystemEntries(dir))
            {
                try
                {
                    if (File.Exists(d))
                    {
                        FileInfo fi = new FileInfo(d);
                        if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)
                            fi.Attributes = FileAttributes.Normal;
                        File.Delete(d);//直接删除其中的文件  
                    }
                    else
                    {
                        DirectoryInfo d1 = new DirectoryInfo(d);
                        if (d1.GetFiles().Length != 0)
                        {
                            DeleteFolder(d1.FullName);////递归删除子文件夹
                        }
                        Directory.Delete(d);
                    }
                }
                catch { }
            }
        }
        /// <summary>
        /// 从cube500获取魔方理论解
        /// </summary>
        /// <param name="cube"></param>
        /// <returns></returns>
        private string GetTheoryFormCube500(string cube)//cube-->workCube-->url-->Str1-->Str2--Theory-->return
        {
            string url = "http://127.0.0.1:8081/?";
            //UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
            //TO
            //U1-U9,R1-R9,F1-F9,D1-D9,L1-L9,B1-B9
            string workCube = cube + "FRUBLD";
            int[] map = {
                            30,4,27,6,50,2,33,0,24,
                            26,3,28,17,49,21,37,11,47,
                            35,1,25,18,48,16,40,9,38,
                            39,8,36,14,53,10,42,12,45,
                            32,7,34,23,52,19,43,15,41,
                            29,5,31,20,51,22,46,13,44
                        };
            for (int i = 0; i < 54; i++)
            {
                url += workCube[map[i]];
            }
            string Str1 = URLRequest(url);
            string Str2 = Str1.Substring(14, Str1.Length - 32);

            string Theory = "";
            for (int i = 0; i < Str2.Length;)
            {
                if ((Str2[i] == 'F') || (Str2[i] == 'R') || (Str2[i] == 'U') || (Str2[i] == 'B') || (Str2[i] == 'L') || (Str2[i] == 'D'))
                {
                    Theory += Str2[i];

                    if (i == (Str2.Length - 1))  //搜索到了最后一个字符
                    {
                        Theory += "1 ";   //注意加空格
                        i = Str2.Length;
                    }
                    else
                    {
                        if (Str2[i + 1] == ' ')
                        {
                            Theory += "1 ";
                            i = i + 2;
                        }
                        else if (Str2[i + 1] == '2')
                        {
                            Theory += "2 ";
                            i = i + 3;
                        }
                        else if (Str2[i + 1] == '\'')
                        {
                            Theory += "3 ";
                            i = i + 3;
                        }
                        else
                        {
                            MessageBox.Show("格式转换失败！！");
                            break;
                        }
                    }

                }
                else
                {
                    MessageBox.Show("格式转换失败！！");
                    break;
                }
            }
            return Theory;
        }
        /// 访问URL地址
        /// <summary>     
        /// Get方式获取url地址输出内容     
        /// </summary> /// <param name="url">url</param>     
        /// <param name="encoding">返回内容编码方式，例如：Encoding.UTF8</param>     
        private static String URLRequest(String url)
        {
            HttpWebRequest webRequest = (HttpWebRequest)WebRequest.Create(url);
            webRequest.Method = "GET";
            Encoding encoding = Encoding.Default;
            HttpWebResponse webResponse = (HttpWebResponse)webRequest.GetResponse();
            StreamReader sr = new StreamReader(webResponse.GetResponseStream(), encoding);
            return sr.ReadToEnd();
        }
        /// <summary>
        /// 利用外部程序，进行T2M转换
        /// </summary>
        /// <param name="Theory"></param>
        /// <returns></returns>
        private string T2M(string Theory)
        {
            //建立Theory.txt
            FileStream TheoryFile = new FileStream(@"./Bridge/Theory.txt", FileMode.Create);//将Cube500获得的解放进Theory.txt中
            StreamWriter sw = new StreamWriter(TheoryFile);
            sw.WriteLine(Theory);
            sw.Close();
            TheoryFile.Close();
            System.Threading.Thread.Sleep(20);
            //建立TheoryFileFlag.txt
            FileStream TheoryFileFlagFile = new FileStream(@"./Bridge/TheoryFlag.txt", FileMode.Create);//这个flag标志在Theory2Mechanical中用于放入问题
            TheoryFileFlagFile.Close();
            //等待T2M解算完成
            while (!FlagExist("MechanicalFlag"))//等待Theory2Mechanical跑完
            {
                System.Threading.Thread.Sleep(20);
            }
            //*读取答案
            FileStream MechanicalFile = new FileStream(@"./Bridge/Mechanical.txt", FileMode.Open); //结果存在Mechanical.txt中
             StreamReader sr = new StreamReader(MechanicalFile);
            string MechanicalAnswer = sr.ReadLine();
            sr.Close();
            MechanicalFile.Close();
            //删除文件
            System.Threading.Thread.Sleep(20);
            System.IO.File.Delete(@"./Bridge/MechanicalFlag.txt");//temp文件删除
            System.IO.File.Delete(@"./Bridge/Mechanical.txt");
            return MechanicalAnswer;//返回
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
                System.Threading.Thread.Sleep(50);
                System.IO.File.Delete(@"./Bridge/" + str + ".txt");
            }
        }
        bool FlagExist(string str)
        {
            return System.IO.File.Exists(@"./Bridge/" + str + ".txt");
        }

        //==============================================================================串口相关控件
        /*
        给下位机发送数据，连发三遍，共计450个Byte
        包头0XAA
        数据 148个
        包尾0XBB

        信号类型：
        1，扫描移动指令，数据格式为AA FF FF ... FF FF BB
        2，移动步骤，数据格式为AA step0 step1 step2 step3 ... stepn BB BB ... BB
        
         下位机回复指令，连发三遍，共计3个字符
         
         * 信号类型：
         * 1，扫描通讯完成：0XCC
         * 2，解魔方完成：0XDD
        */
        /// <summary>
        /// 搜索串口按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        int SearchPort_Click_count = 0;
        private void SearchPort_Click(object sender, EventArgs e)
        {
            //点击搜索后关闭串口
            this.SerialPort1.Close();
            this.StartButton.Checked = false;
            string[] PortStr = SerialPort.GetPortNames();
            if (PortStr.Length == 0)
            {
                this.PortName.Text = "null";
            }
            else
            {
                this.PortName.Text = PortStr[SearchPort_Click_count].ToString();
                SearchPort_Click_count++;
                if (SearchPort_Click_count == PortStr.Length) SearchPort_Click_count = 0;
            }
        }
        /// <summary>
        /// 启动串口按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void StartButton_Click(object sender, EventArgs e)
        {
            this.StartButton.Checked = false;
            this.SerialPort1.Close();

            if (this.PortName.Text != "null")
            {
                try
                {
                    //打开串口
                    this.SerialPort1.BaudRate = 115200;
                    this.SerialPort1.PortName = this.PortName.Text;
                    this.SerialPort1.Open();
                    this.StartButton.Checked = true;
                    this.SerialPort1.DiscardInBuffer();
                }
                catch
                {
                    this.PortName.Text = "null";
                }
            }
            
        }
        public static string ToHexString(byte[] bytes) // 0xae00cf => "AE00CF "
        {
            string hexString = string.Empty;
            if (bytes != null)
            {
                StringBuilder strB = new StringBuilder();
                for (int i = 0; i < bytes.Length; i++)
                {
                    strB.Append(bytes[i].ToString("X2"));
                }
                hexString = strB.ToString();
            }
            return hexString;
        }
        //收数据中断
        private void SerialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            Byte[] ReceiveByte = new Byte[this.SerialPort1.BytesToRead];
            this.SerialPort1.Read(ReceiveByte, 0, ReceiveByte.Length);
            this.SerialPort1.DiscardInBuffer();

            for (int i = 0; i < ReceiveByte.Length; i++)
            {
                //ReceiveByte[i]=0xcc;
                //string str = System.Text.Encoding.UTF8.GetString(ReceiveByte);
                //string str = ToHexString(ReceiveByte);
                //this.MoveTimeCost.Text = str;

                //若收到数据OXCC，则SecondCapDown为true
                if (ReceiveByte[i] == 0xCC)
                {
                    SecondCapDown = true;
                    break;
                }
                //若收到数据为0XDD，则解算完成
                else if (ReceiveByte[i] == 0xDD)
                {
                    RunState = WAIT;
                    try
                    {
                        TimeCount.Abort();
                    }
                    catch { }
                    try
                    {
                        SloveCube.Abort();
                    }
                    catch { }
                    break;
                }
            }
        }

        /// <summary>
        /// 向下位机发送数据，移动手抓进行第二次采集
        /// </summary>
        void MoveHandForSecondCap()
        {
            if (this.SerialPort1.IsOpen)
            {
                try
                {
                    Byte[] tempByte = new Byte[150];
                    for (int i = 0; i < 150; i++)
                    {
                        tempByte[i] = 0XFF;
                    }
                    tempByte[0] = 0XAA;
                    tempByte[149] = 0XBB;
                    this.SerialPort1.Write(tempByte, 0, 150);
                    //this.SerialPort1.Write(tempByte, 0, 150);
                    //this.SerialPort1.Write(tempByte, 0, 150);
                }
                catch { MessageBox.Show("MoveHandForSecondCap err"); }
            }
            else
            {
                MessageBox.Show("串口未打开");
            }
        }
        //发送解法到下位机
        void SendMStrToSTM32(string MechanicalStr)
        {
            if (this.SerialPort1.IsOpen)
            {
                try
                {
                    Byte[] tempByte = new Byte[150];

                    int Len = MechanicalStr.Length / 5;

                    for (int i = 0; i < Len; i++)
                    {
                        string tempStr = MechanicalStr.Substring(i * 5 + 2, 2);
                        tempByte[i + 1] = MStr2int(tempStr);
                    }
                    tempByte[0] = 0XAA;
                    for (int i = Len + 1; i < 150; i++)
                    {
                        tempByte[i] = 0XBB;
                    }

                    this.SerialPort1.Write(tempByte, 0, 150);
                    //this.SerialPort1.Write(tempByte, 0, 150);
                    //this.SerialPort1.Write(tempByte, 0, 150);
                }
                catch { }
            }
        }
        Byte MStr2int(string MechStep)
        {
            /*
                L_C: 0		R_C: 5
                L_O: 1		R_O: 6
                L_1: 2		R_1: 7
                L_2: 3		R_2: 8
                L_3: 4		R_3: 9
            */
            switch (MechStep)
            {
                case "LC": return 0x00;
                case "LO": return 0x01;
                case "L1": return 0x02;
                case "L2": return 0x03;
                case "L3": return 0x04;

                case "RC": return 0x05;
                case "RO": return 0x06;
                case "R1": return 0x07;
                case "R2": return 0x08;
                case "R3": return 0x09;

            }
            return 0xff;
        }
    }
}
