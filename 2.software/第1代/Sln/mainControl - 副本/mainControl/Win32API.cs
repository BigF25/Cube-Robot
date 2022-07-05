using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;
namespace mainControl
{
    class Win32API
    {
        //SetWindowPos参数
        public const Int32 SWP_NOMOVE = 0x0002;
        public const Int32 SWP_NOSIZE = 0x0001;
        //SendMessage参数
        public const Int32 WM_KEYDOWN = 0x100;
        public const Int32 WM_KEYUP = 0x101;
        public const Int32 WM_SYSCHAR = 0x106;
        public const Int32 WM_SYSKEYUP = 0x105;
        public const Int32 WM_SYSKEYDOWN = 0x104;
        public const Int32 WM_CHAR = 0x102;
        //mouse_event参数
        public const Int32 MOUSEEVENTF_LEFTDOWN = 0x2;//定义鼠标左键按下消息 
        public const Int32 MOUSEEVENTF_LEFTUP = 0x4;//定义鼠标左键弹起消息 
        public const Int32 MOUSEEVENTF_RIGHTDOWN = 0x008;//定义鼠标右键按下消息 
        public const Int32 MOUSEEVENTF_RIGHTUP = 0x0010; //定义鼠标右键弹起消息 
        //keybd_event参数
        public const Int32 KEYEVENTF_KEYDOWN = 0x00;  //按下
        public const Int32 KEYEVENTF_KEYUP = 0x02;  //松开

        public const Int32 vbKeyLButton = 1;// 鼠标左键 
        public const Int32 vbKeyRButton = 2;//鼠标右键 
        public const Int32 vbKeyCancel = 3;//CANCEL 键 
        public const Int32 vbKeyMButton = 4;//鼠标中键 
        public const Int32 vbKeyBack = 8;// BACKSPACE 键 
        public const Int32 vbKeyTab = 9;//TAB 键 
        public const Int32 vbKeyClear = 12;// CLEAR 键 
        public const Int32 vbKeyReturn = 13;// ENTER 键 
        public const Int32 vbKeyShift = 16;// SHIFT 键 
        public const Int32 vbKeyControl = 17;// CTRL 键 
        public const Int32 vbKeyMenu = 18;//菜单键 
        public const Int32 vbKeyPause = 19;// PAUSE 键 
        public const Int32 vbKeyCapital = 20;//CAPS LOCK 键 
        public const Int32 vbKeyEscape = 27;//ESC 键 
        public const Int32 vbKeySpace = 32;// SPACEBAR 键 
        public const Int32 vbKeyPageUp = 33;// PAGEUP 键 
        public const Int32 vbKeyPageDown = 34;// PAGEDOWN 键 
        public const Int32 vbKeyEnd = 35;// END 键 
        public const Int32 vbKeyHome = 36;// HOME 键 
        public const Int32 vbKeyLeft = 37;// LEFT ARROW 键 
        public const Int32 vbKeyUp = 38;//UP ARROW 键 
        public const Int32 vbKeyRight = 39;//RIGHT ARROW 键 
        public const Int32 vbKeyDown = 40;//DOWN ARROW 键 
        public const Int32 vbKeySelect = 41;// SELECT 键 
        public const Int32 vbKeyPrint = 42;//PRINT SCREEN 键 
        public const Int32 vbKeyExecute = 43;// EXECUTE 键 
        public const Int32 vbKeySnapshot = 44;// SNAP SHOT 键 
        public const Int32 vbKeyInser = 45;//INS 键 
        public const Int32 vbKeyDelete = 46;//DEL 键 
        public const Int32 vbKeyHelp = 47;// HELP 键 
        public const Int32 vbKeyNumlock = 144;// NUM LOCK 键 

        public const Int32 vbKeyA = 65;// A 键 
        public const Int32 vbKeyB = 66;// B 键 
        public const Int32 vbKeyC = 67;// C 键 
        public const Int32 vbKeyD = 68;// D 键 
        public const Int32 vbKeyE = 69;// E 键 
        public const Int32 vbKeyF = 70;// F 键 
        public const Int32 vbKeyG = 71;// G 键 
        public const Int32 vbKeyH = 72;// H 键 
        public const Int32 vbKeyI = 73;// I 键 
        public const Int32 vbKeyJ = 74;// J 键 
        public const Int32 vbKeyK = 75;// K 键 
        public const Int32 vbKeyL = 76;// L 键 
        public const Int32 vbKeyM = 77;//M 键 
        public const Int32 vbKeyN = 78;// N 键 
        public const Int32 vbKeyO = 79;// O 键 
        public const Int32 vbKeyP = 80;// P 键 
        public const Int32 vbKeyQ = 81;// Q 键 
        public const Int32 vbKeyR = 82;// R 键 
        public const Int32 vbKeyS = 83;//S 键 
        public const Int32 vbKeyT = 84;// T 键 
        public const Int32 vbKeyU = 85;// U 键 
        public const Int32 vbKeyV = 86;// V 键 
        public const Int32 vbKeyW = 87;// W 键 
        public const Int32 vbKeyX = 88;// X 键 
        public const Int32 vbKeyY = 89;//Y 键 
        public const Int32 vbKeyZ = 90;// Z 键 
        public const Int32 vbKey0 = 48;// 0 键 
        public const Int32 vbKey1 = 49;//1 键 
        public const Int32 vbKey2 = 50;// 2 键 
        public const Int32 vbKey3 = 51;// 3 键 
        public const Int32 vbKey4 = 52;// 4 键 
        public const Int32 vbKey5 = 53;// 5 键 
        public const Int32 vbKey6 = 54;// 6 键 
        public const Int32 vbKey7 = 55;// 7 键 
        public const Int32 vbKey8 = 56;// 8 键 
        public const Int32 vbKey9 = 57;// 9 键 
        public const Int32 vbKeyF1 = 112;// F1 键 
        public const Int32 vbKeyF2 = 113;// F2 键 
        public const Int32 vbKeyF3 = 114;// F3 键 
        public const Int32 vbKeyF4 = 115;// F4 键 
        public const Int32 vbKeyF5 = 116;//F5 键 
        public const Int32 vbKeyF6 = 117;// F6 键 
        public const Int32 vbKeyF7 = 118;//F7 键 
        public const Int32 vbKeyF8 = 119;// F8 键 
        public const Int32 vbKeyF9 = 120;// F9 键 
        public const Int32 vbKeyF10 = 121;// F10 键 
        public const Int32 vbKeyF11 = 122;// F11 键 
        public const Int32 vbKeyF12 = 123;// F12 键 
        public const Int32 vbKeyF13 = 124;// F13 键 
        public const Int32 vbKeyF14 = 125;// F14 键 
        public const Int32 vbKeyF15 = 126;//F15 键 
        public const Int32 vbKeyF16 = 127;// F16 键
        //设置窗口的父窗体
        [DllImport("user32.dll", SetLastError = true)]
        public static extern long SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        //设置窗口位置
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int MoveWindow(IntPtr hWnd, int x, int y, int nWidth, int nHeight, bool BRePaint);
        //查找窗口
        [DllImport("user32.dll", EntryPoint = "FindWindow")]
        public extern static IntPtr FindWindow(string lpClassName, string lpWindowName);
        //查找子窗口
        [DllImport("user32.dll", EntryPoint = "FindWindowEx")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);
        //设置最顶层
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int SetWindowPos(IntPtr hWnd, int hWndInsertAfter, int x, int y, int Width, int Height, int flags);
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImport("user32.dll")]
        //设置鼠标位置
        public static extern bool SetCursorPos(int X, int Y);

        [DllImport("user32.dll")]
        //获取鼠标位置
        public static extern bool GetCursorPos(ref Point lpPoint);
        [DllImport("user32.dll")]
        //鼠标事件
        public static extern void mouse_event(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
        [DllImport("user32.dll")]
        public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, uint dwExtraInfo);
        //检查大写锁
        [DllImport("user32.dll", EntryPoint = "GetKeyboardState")]
        public static extern int GetKeyboardState(byte[] pbKeyState);
        public static bool CapsLockStatus
        {
            get
            {
                byte[] bs = new byte[256];
                GetKeyboardState(bs);
                return (bs[0x14] == 1);
            }
        }
    }
}
