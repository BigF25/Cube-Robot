namespace CHTest
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
            this.OpenDevice = new System.Windows.Forms.Button();
            this.V_CH1 = new System.Windows.Forms.Label();
            this.V_CH2 = new System.Windows.Forms.Label();
            this.V_CH3 = new System.Windows.Forms.Label();
            this.V_CH4 = new System.Windows.Forms.Label();
            this.CheckFlagTimer = new System.Windows.Forms.Timer(this.components);
            this.button2 = new System.Windows.Forms.Button();
            this.CAP = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // OpenDevice
            // 
            this.OpenDevice.Location = new System.Drawing.Point(533, 2);
            this.OpenDevice.Name = "OpenDevice";
            this.OpenDevice.Size = new System.Drawing.Size(114, 309);
            this.OpenDevice.TabIndex = 0;
            this.OpenDevice.Text = "打开采集卡";
            this.OpenDevice.UseVisualStyleBackColor = true;
            this.OpenDevice.Click += new System.EventHandler(this.OpenDevice_Click);
            // 
            // V_CH1
            // 
            this.V_CH1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.V_CH1.Location = new System.Drawing.Point(1, -2);
            this.V_CH1.Name = "V_CH1";
            this.V_CH1.Size = new System.Drawing.Size(263, 192);
            this.V_CH1.TabIndex = 1;
            this.V_CH1.Text = "CH1";
            // 
            // V_CH2
            // 
            this.V_CH2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.V_CH2.Location = new System.Drawing.Point(264, 2);
            this.V_CH2.Name = "V_CH2";
            this.V_CH2.Size = new System.Drawing.Size(263, 188);
            this.V_CH2.TabIndex = 2;
            this.V_CH2.Text = "CH2";
            // 
            // V_CH3
            // 
            this.V_CH3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.V_CH3.Location = new System.Drawing.Point(1, 190);
            this.V_CH3.Name = "V_CH3";
            this.V_CH3.Size = new System.Drawing.Size(263, 192);
            this.V_CH3.TabIndex = 6;
            this.V_CH3.Text = "CH3";
            // 
            // V_CH4
            // 
            this.V_CH4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.V_CH4.Location = new System.Drawing.Point(264, 190);
            this.V_CH4.Name = "V_CH4";
            this.V_CH4.Size = new System.Drawing.Size(263, 192);
            this.V_CH4.TabIndex = 7;
            this.V_CH4.Text = "CH4";
            // 
            // CheckFlagTimer
            // 
            this.CheckFlagTimer.Interval = 5;
            this.CheckFlagTimer.Tick += new System.EventHandler(this.CheckFlagTimer_Tick);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button2.Location = new System.Drawing.Point(593, 317);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(54, 65);
            this.button2.TabIndex = 21;
            this.button2.Text = "第2次抓图";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // CAP
            // 
            this.CAP.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CAP.Location = new System.Drawing.Point(533, 317);
            this.CAP.Name = "CAP";
            this.CAP.Size = new System.Drawing.Size(54, 65);
            this.CAP.TabIndex = 0;
            this.CAP.Text = "第1次抓图";
            this.CAP.UseVisualStyleBackColor = true;
            this.CAP.Click += new System.EventHandler(this.CAP_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(671, 405);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.V_CH4);
            this.Controls.Add(this.V_CH3);
            this.Controls.Add(this.V_CH2);
            this.Controls.Add(this.V_CH1);
            this.Controls.Add(this.CAP);
            this.Controls.Add(this.OpenDevice);
            this.Name = "Form1";
            this.Text = " C# SDK Demo";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button OpenDevice;
        private System.Windows.Forms.Label V_CH1;
        private System.Windows.Forms.Label V_CH2;
        private System.Windows.Forms.Label V_CH3;
        private System.Windows.Forms.Label V_CH4;
        private System.Windows.Forms.Timer CheckFlagTimer;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button CAP;
    }
}

