using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sfunction
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        double GetXi(double k,double A,double i)
        {
            double preXi = 0;
            double Xi = k / 2;
            while(Math.Abs(Xi-preXi)>1e-6)
            {
                double a = 2 * k * Math.Cos(Math.PI / 2 * (Xi - k) / k);
                preXi = Xi;
                Xi = a / Math.PI + (i + 1) / A;
            }
            return Xi;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.richTextBox1.Text = "";
            Graphics g = this.pictureBox1.CreateGraphics();
            g.Clear(Color.White);

            int totalTime = 0;
            int totalPluse = System.Convert.ToInt32(this.totalPluse.Text);

            double S = System.Convert.ToDouble(this.S.Text);
            double v = System.Convert.ToDouble(this.v.Text);
            double A = 1 / v;
            double k = S / ((Math.PI / 2 - 1) * A);

            this.richTextBox1.Text += "#define " + this.PathName.Text + "AcNum  " + this.S.Text + "\r\n";
            this.richTextBox1.Text +=  "int "+this.PathName.Text + "[" + this.S.Text+"]={" + "\r\n";
            double Xi_1 = 0;
            double Xi = 0;
            for(int i=0;i<S;i++)
            {
                Point p = new Point();

                Xi_1 = Xi;
                Xi = GetXi(k, A, i);

                p.X = i;
                p.Y = (int)(Xi - Xi_1);

                g.DrawEllipse(Pens.Red, p.X, 400 - p.Y, 2, 2);

                if ((i % 25 == 0)&&(i>0)) this.richTextBox1.Text += "\r\n";
                this.richTextBox1.Text += ((int)(Xi - Xi_1 + 0.5)).ToString();
                if (i != S - 1) this.richTextBox1.Text += ",";

                totalTime += (int)(Xi - Xi_1 + 0.5) * 2;
            }
            this.richTextBox1.Text += "\r\n};";

            totalTime += (int)(Xi - Xi_1 + 0.5) * (totalPluse - 2 * (int)S);
            this.totalTime.Text = ((double)totalTime/100).ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }
    }
}
