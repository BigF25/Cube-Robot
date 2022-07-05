namespace mainControl
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.cube500Process = new System.Diagnostics.Process();
            this.T2Mprocess = new System.Diagnostics.Process();
            this.CHTestProcess = new System.Diagnostics.Process();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.StartBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.TotalTimeCost = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.StepNum = new System.Windows.Forms.Label();
            this.OpenCvProcess = new System.Diagnostics.Process();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.StartButton = new System.Windows.Forms.RadioButton();
            this.label2 = new System.Windows.Forms.Label();
            this.PortName = new System.Windows.Forms.TextBox();
            this.SearchPort = new System.Windows.Forms.Button();
            this.SerialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.richTextBox2 = new System.Windows.Forms.RichTextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.Stopbtn = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.ScanTimeCost = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.CalcTimeCost = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.MoveTimeCost = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cube500Process
            // 
            this.cube500Process.StartInfo.Domain = "";
            this.cube500Process.StartInfo.FileName = ".\\cube500\\cube500sCN.exe";
            this.cube500Process.StartInfo.LoadUserProfile = false;
            this.cube500Process.StartInfo.Password = null;
            this.cube500Process.StartInfo.StandardErrorEncoding = null;
            this.cube500Process.StartInfo.StandardOutputEncoding = null;
            this.cube500Process.StartInfo.UserName = "";
            this.cube500Process.StartInfo.UseShellExecute = false;
            this.cube500Process.SynchronizingObject = this;
            // 
            // T2Mprocess
            // 
            this.T2Mprocess.StartInfo.Domain = "";
            this.T2Mprocess.StartInfo.FileName = ".\\Theory2Mechancial";
            this.T2Mprocess.StartInfo.LoadUserProfile = false;
            this.T2Mprocess.StartInfo.Password = null;
            this.T2Mprocess.StartInfo.StandardErrorEncoding = null;
            this.T2Mprocess.StartInfo.StandardOutputEncoding = null;
            this.T2Mprocess.StartInfo.UserName = "";
            this.T2Mprocess.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Minimized;
            this.T2Mprocess.SynchronizingObject = this;
            // 
            // CHTestProcess
            // 
            this.CHTestProcess.StartInfo.Domain = "";
            this.CHTestProcess.StartInfo.FileName = ".\\CHTest\\CHTest.exe";
            this.CHTestProcess.StartInfo.LoadUserProfile = false;
            this.CHTestProcess.StartInfo.Password = null;
            this.CHTestProcess.StartInfo.StandardErrorEncoding = null;
            this.CHTestProcess.StartInfo.StandardOutputEncoding = null;
            this.CHTestProcess.StartInfo.UserName = "";
            this.CHTestProcess.StartInfo.UseShellExecute = false;
            this.CHTestProcess.SynchronizingObject = this;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(16, 308);
            this.richTextBox1.Margin = new System.Windows.Forms.Padding(4);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(279, 122);
            this.richTextBox1.TabIndex = 2;
            this.richTextBox1.Text = "";
            // 
            // StartBtn
            // 
            this.StartBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartBtn.Location = new System.Drawing.Point(280, 177);
            this.StartBtn.Margin = new System.Windows.Forms.Padding(4);
            this.StartBtn.Name = "StartBtn";
            this.StartBtn.Size = new System.Drawing.Size(100, 50);
            this.StartBtn.TabIndex = 4;
            this.StartBtn.Text = "开始";
            this.StartBtn.UseVisualStyleBackColor = true;
            this.StartBtn.Click += new System.EventHandler(this.StartBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(579, 279);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 44);
            this.label1.TabIndex = 5;
            this.label1.Text = "总长：";
            // 
            // TotalTimeCost
            // 
            this.TotalTimeCost.AutoSize = true;
            this.TotalTimeCost.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TotalTimeCost.Location = new System.Drawing.Point(825, 280);
            this.TotalTimeCost.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.TotalTimeCost.Name = "TotalTimeCost";
            this.TotalTimeCost.Size = new System.Drawing.Size(98, 44);
            this.TotalTimeCost.TabIndex = 6;
            this.TotalTimeCost.Text = "0.00";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(917, 280);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 44);
            this.label3.TabIndex = 7;
            this.label3.Text = "S";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(21, 260);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(137, 44);
            this.label4.TabIndex = 8;
            this.label4.Text = "步骤：";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(353, 260);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(137, 44);
            this.label5.TabIndex = 9;
            this.label5.Text = "总数：";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // StepNum
            // 
            this.StepNum.AutoSize = true;
            this.StepNum.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.StepNum.Location = new System.Drawing.Point(397, 331);
            this.StepNum.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.StepNum.Name = "StepNum";
            this.StepNum.Size = new System.Drawing.Size(63, 69);
            this.StepNum.TabIndex = 10;
            this.StepNum.Text = "0";
            // 
            // OpenCvProcess
            // 
            this.OpenCvProcess.StartInfo.Domain = "";
            this.OpenCvProcess.StartInfo.FileName = ".\\OpenCVtest.exe";
            this.OpenCvProcess.StartInfo.LoadUserProfile = false;
            this.OpenCvProcess.StartInfo.Password = null;
            this.OpenCvProcess.StartInfo.StandardErrorEncoding = null;
            this.OpenCvProcess.StartInfo.StandardOutputEncoding = null;
            this.OpenCvProcess.StartInfo.UserName = "";
            this.OpenCvProcess.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Minimized;
            this.OpenCvProcess.SynchronizingObject = this;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Controls.Add(this.label19);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.PortName);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(233, 34);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(735, 135);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口设置";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(524, 60);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(181, 50);
            this.textBox1.TabIndex = 18;
            this.textBox1.Text = "115200";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(333, 63);
            this.label19.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(173, 38);
            this.label19.TabIndex = 17;
            this.label19.Text = "波特率：";
            // 
            // StartButton
            // 
            this.StartButton.Appearance = System.Windows.Forms.Appearance.Button;
            this.StartButton.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.StartButton.Location = new System.Drawing.Point(155, 179);
            this.StartButton.Margin = new System.Windows.Forms.Padding(4);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(100, 50);
            this.StartButton.TabIndex = 16;
            this.StartButton.TabStop = true;
            this.StartButton.Text = "启动串口";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(8, 63);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(173, 38);
            this.label2.TabIndex = 1;
            this.label2.Text = "端口号：";
            // 
            // PortName
            // 
            this.PortName.Location = new System.Drawing.Point(193, 54);
            this.PortName.Margin = new System.Windows.Forms.Padding(4);
            this.PortName.Name = "PortName";
            this.PortName.ReadOnly = true;
            this.PortName.Size = new System.Drawing.Size(119, 50);
            this.PortName.TabIndex = 2;
            this.PortName.Text = "null";
            this.PortName.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SearchPort
            // 
            this.SearchPort.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SearchPort.Location = new System.Drawing.Point(33, 178);
            this.SearchPort.Margin = new System.Windows.Forms.Padding(4);
            this.SearchPort.Name = "SearchPort";
            this.SearchPort.Size = new System.Drawing.Size(100, 50);
            this.SearchPort.TabIndex = 1;
            this.SearchPort.Text = "搜索串口";
            this.SearchPort.UseVisualStyleBackColor = true;
            this.SearchPort.Click += new System.EventHandler(this.SearchPort_Click);
            // 
            // SerialPort1
            // 
            this.SerialPort1.BaudRate = 38400;
            this.SerialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort1_DataReceived);
            // 
            // richTextBox2
            // 
            this.richTextBox2.Font = new System.Drawing.Font("宋体", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.richTextBox2.Location = new System.Drawing.Point(20, 56);
            this.richTextBox2.Margin = new System.Windows.Forms.Padding(4);
            this.richTextBox2.Name = "richTextBox2";
            this.richTextBox2.ReadOnly = true;
            this.richTextBox2.Size = new System.Drawing.Size(177, 61);
            this.richTextBox2.TabIndex = 12;
            this.richTextBox2.Text = "";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("宋体", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(13, 11);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(212, 38);
            this.label6.TabIndex = 13;
            this.label6.Text = "错误提示：";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // Stopbtn
            // 
            this.Stopbtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Stopbtn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Stopbtn.Location = new System.Drawing.Point(409, 178);
            this.Stopbtn.Margin = new System.Windows.Forms.Padding(4);
            this.Stopbtn.Name = "Stopbtn";
            this.Stopbtn.Size = new System.Drawing.Size(100, 50);
            this.Stopbtn.TabIndex = 14;
            this.Stopbtn.Text = "停止";
            this.Stopbtn.UseVisualStyleBackColor = true;
            this.Stopbtn.Click += new System.EventHandler(this.Stopbtn_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(917, 323);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(46, 44);
            this.label7.TabIndex = 17;
            this.label7.Text = "S";
            // 
            // ScanTimeCost
            // 
            this.ScanTimeCost.AutoSize = true;
            this.ScanTimeCost.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ScanTimeCost.Location = new System.Drawing.Point(825, 323);
            this.ScanTimeCost.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ScanTimeCost.Name = "ScanTimeCost";
            this.ScanTimeCost.Size = new System.Drawing.Size(98, 44);
            this.ScanTimeCost.TabIndex = 16;
            this.ScanTimeCost.Text = "0.00";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(579, 323);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(254, 44);
            this.label9.TabIndex = 15;
            this.label9.Text = "摄像头读取：";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(917, 367);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 44);
            this.label8.TabIndex = 20;
            this.label8.Text = "S";
            // 
            // CalcTimeCost
            // 
            this.CalcTimeCost.AutoSize = true;
            this.CalcTimeCost.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CalcTimeCost.Location = new System.Drawing.Point(825, 367);
            this.CalcTimeCost.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.CalcTimeCost.Name = "CalcTimeCost";
            this.CalcTimeCost.Size = new System.Drawing.Size(98, 44);
            this.CalcTimeCost.TabIndex = 19;
            this.CalcTimeCost.Text = "0.00";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(579, 367);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(215, 44);
            this.label11.TabIndex = 18;
            this.label11.Text = "步骤计算：";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(917, 404);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(46, 44);
            this.label12.TabIndex = 23;
            this.label12.Text = "S";
            // 
            // MoveTimeCost
            // 
            this.MoveTimeCost.AutoSize = true;
            this.MoveTimeCost.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MoveTimeCost.Location = new System.Drawing.Point(825, 404);
            this.MoveTimeCost.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.MoveTimeCost.Name = "MoveTimeCost";
            this.MoveTimeCost.Size = new System.Drawing.Size(98, 44);
            this.MoveTimeCost.TabIndex = 22;
            this.MoveTimeCost.Text = "0.00";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(579, 404);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(137, 44);
            this.label14.TabIndex = 21;
            this.label14.Text = "拧动：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(579, 235);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(137, 44);
            this.label10.TabIndex = 24;
            this.label10.Text = "时间：";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(736, 8);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(215, 44);
            this.label13.TabIndex = 25;
            this.label13.Text = "魔方机器人";
            this.label13.Click += new System.EventHandler(this.label13_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.Info;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ClientSize = new System.Drawing.Size(989, 479);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.MoveTimeCost);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.CalcTimeCost);
            this.Controls.Add(this.SearchPort);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.ScanTimeCost);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.Stopbtn);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.richTextBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.StepNum);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.TotalTimeCost);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.StartBtn);
            this.Controls.Add(this.richTextBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Diagnostics.Process cube500Process;
        public System.Diagnostics.Process T2Mprocess;
        public System.Diagnostics.Process CHTestProcess;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button StartBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label TotalTimeCost;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label StepNum;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        public System.Diagnostics.Process OpenCvProcess;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.RadioButton StartButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox PortName;
        private System.Windows.Forms.Button SearchPort;
        private System.IO.Ports.SerialPort SerialPort1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.RichTextBox richTextBox2;
        private System.Windows.Forms.Button Stopbtn;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label ScanTimeCost;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label MoveTimeCost;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label CalcTimeCost;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label10;
    }
}

