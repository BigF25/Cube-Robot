using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AngleTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int[] IDX1 = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 5, 5, 5, 6, 6, 6, 5, 5, 5, 6, 6, 6 };
        double[] D0 = { 52, 19, 19, 50, 20, 25, 46, 30, 34, 188, 86, 45, 25, 39, 65, 163, 88, 55, 39, 67, 83, 88, 61, 43, 27, 33, 57, 177, 155, 180, 150, 126, 142, 179, 130, 146, 134, 127, 114, 234, 255, 285, 131, 119, 116, 220, 237, 271, 136, 122, 115, 220, 241, 275 };
        double[] D1 = { 212, 173, 162, 187, 149, 171, 175, 164, 168, 187, 122, 92, 133, 149, 191, 166, 118, 93, 130, 156, 194, 143, 107, 89, 136, 151, 187, 167, 149, 175, 144, 122, 134, 171, 123, 142, 67, 59, 52, 188, 207, 229, 65, 58, 51, 178, 197, 220, 66, 59, 51, 176, 197, 224 };
        double[] D2 = { 211, 180, 165, 192, 155, 178, 178, 174, 171, 259, 211, 176, 54, 59, 82, 245, 203, 170, 56, 69, 86, 254, 209, 175, 58, 59, 77, 168, 151, 176, 145, 124, 136, 172, 128, 145, 280, 250, 225, 110, 117, 131, 273, 237, 214, 105, 113, 129, 277, 242, 217, 101, 112, 130 };

        private void button1_Click(object sender, EventArgs e)
        {
            double maxDis = -1;
            double _B1=0;
            double _B2=0;
            for(double B1=30;B1<60;B1+=1)
            {
                for(double B2=125;B2<155;B2+=1)
                {
                    double b1 = B1 * 3.141592654 / 180.0;
                    double b2 = B2 * 3.141592654 / 180.0;
                    double Dis = TrackMove(b1, b2);
                    if(Dis>maxDis)
                    {
                        maxDis = Dis;
                        _B1 = B1;
                        _B2 = B2;
                    }
                }
            }

            this.label1.Text = _B1.ToString();
            this.label2.Text = _B2.ToString();

           // this.trackBar1.Value = (int)_B1;
            //this.trackBar2.Value = (int)_B2;

            TrackMove(_B1 * 3.141592654 / 180.0, _B2 * 3.141592654 / 180.0);

        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            this.label1.Text = this.trackBar1.Value.ToString();
            this.label2.Text = this.trackBar2.Value.ToString();

            double B1 = (double)(this.trackBar1.Value) * 3.141592654 / 180.0;
            double B2 = (double)(this.trackBar2.Value) * 3.141592654 / 180.0;
            TrackMove(B1, B2);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            this.label1.Text = this.trackBar1.Value.ToString();
            this.label2.Text = this.trackBar2.Value.ToString();

            double B1 = (double)(this.trackBar1.Value) * 3.141592654 / 180.0;
            double B2 = (double)(this.trackBar2.Value) * 3.141592654 / 180.0;
            TrackMove(B1,B2);
        }
        double TrackMove(double B1,double B2)
        {
            Graphics g = this.pictureBox1.CreateGraphics();
            g.Clear(Color.White);

            double cB1 = Math.Cos(B1);
            double cB2 = Math.Cos(B2);
            double sB1 = Math.Sin(B1);
            double sB2 = Math.Sin(B2);
            double[,] Rx ={
                             {1,   0,   0},
                             {0, cB1,-sB1},
                             {0, sB1, cB1} 
                         };
            double[,] Ry ={
                             {cB2, 0, sB2},
                             {0,   1,   0},
                             {-sB2,0, cB2} 
                         };

            double[,] Point = new double[3, 54];

            for (int i = 0; i < 54; i++)
            {
                //x轴旋转
                double temp1 = Rx[0, 0] * D0[i] + Rx[0, 1] * D1[i] + Rx[0, 2] * D2[i];
                double temp2 = Rx[1, 0] * D0[i] + Rx[1, 1] * D1[i] + Rx[1, 2] * D2[i];
                double temp3 = Rx[2, 0] * D0[i] + Rx[2, 1] * D1[i] + Rx[2, 2] * D2[i];
                //y轴旋转
                Point[0, i] = Ry[0, 0] * temp1 + Ry[0, 1] * temp2 + Ry[0, 2] * temp3;
                Point[1, i] = Ry[1, 0] * temp1 + Ry[1, 1] * temp2 + Ry[1, 2] * temp3;
                Point[2, i] = Ry[2, 0] * temp1 + Ry[2, 1] * temp2 + Ry[2, 2] * temp3;

                Brush p = Brushes.Red; ;
                switch(IDX1[i])
                {
                    case 1: p = Brushes.Red; break;
                    case 2: p = Brushes.Blue; break;
                    case 3: p = Brushes.RosyBrown; break;
                    case 4: p = Brushes.SeaGreen; break;
                    case 5: p = Brushes.Tomato; break;
                    case 6: p = Brushes.Wheat; break;
                    default: p = Brushes.Red; break;
                }
                g.FillEllipse(p, (int)(Point[0, i] * 1.2 + 100), (int)(Point[1, i] * 1.2 + 250), 10, 10);
            }
            g.Dispose();

            double minDis = 1e8;
            for (int i = 0; i < 54;i++ )
            {
                for(int j=i+1;j<54;j++)
                {
                    if(IDX1[i]!=IDX1[j])  //若两个不同类，求距离。找出距离的最小值
                    {
                        double Dis = (Point[0, i] - Point[0, j]) * (Point[0, i] - Point[0, j]) + (Point[1, i] - Point[1, j]) * (Point[1, i] - Point[1, j]);
                        if (Dis < minDis) minDis = Dis;
                    }
                }
            }
            return minDis;
        }
    }
}
