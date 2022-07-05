using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace mainControl
{
    class FindHandles
    {
        //句柄
        public static IntPtr cube500Handle = IntPtr.Zero;
        public static IntPtr hAnswerArea = IntPtr.Zero;
        public static IntPtr hInput = IntPtr.Zero;
        public static IntPtr hApply = IntPtr.Zero;
        public static IntPtr hSearch = IntPtr.Zero;
        public static IntPtr hRecover = IntPtr.Zero;
        public static void FindCube500Handle()
        {
            //寻找句柄
            //*1级
            cube500Handle = Win32API.FindWindow("TForm1", "untitled.txt - Cube Explorer 5.00s");
            ////*2级
            //hAnswerArea = Win32API.FindWindowEx(cube500Handle, IntPtr.Zero, "TPanel", null);
            //IntPtr htemp = Win32API.FindWindowEx(cube500Handle, IntPtr.Zero, "TPageControl", null);
            ////*3级
            //htemp = Win32API.FindWindowEx(htemp, IntPtr.Zero, "TTabSheet", "外观编辑器");
            ////*4级
            //IntPtr htemp1 = Win32API.FindWindowEx(htemp, IntPtr.Zero, "TGroupBox", "输入公式");
            //IntPtr htemp2 = Win32API.FindWindowEx(htemp, IntPtr.Zero, "TGroupBox", "对当前魔方");
            //IntPtr htemp3 = Win32API.FindWindowEx(htemp, IntPtr.Zero, "TGroupBox", "重置为");
            ////*5级
            //IntPtr hInput = Win32API.FindWindowEx(htemp1, IntPtr.Zero, "TEdit", null);
            //IntPtr hApply = Win32API.FindWindowEx(htemp1, IntPtr.Zero, "TButton", "应用");
            //IntPtr hSearch = Win32API.FindWindowEx(htemp2, IntPtr.Zero, "TButton", "搜索还原解法");
            //IntPtr hRecover = Win32API.FindWindowEx(htemp3, IntPtr.Zero, "TButton", "复原");
        }
        //句柄
        public static IntPtr CHTestHandle = IntPtr.Zero;
        public static void FindCHTestHandle()
        {
            //寻找句柄
            //*1级
            CHTestHandle = Win32API.FindWindow(null, " C# SDK Demo");
        }
    }
}
