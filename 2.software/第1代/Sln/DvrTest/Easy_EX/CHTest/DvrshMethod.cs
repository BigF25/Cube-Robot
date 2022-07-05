using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CHTest
{
    struct RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }
    class DvrshMethod
    {
        [DllImport("dvrssw.dll")]
        public static extern int InitDVRS();
        [DllImport("dvrssw.dll")]
         public static extern int OpenVideoPreview (int hChannel, IntPtr WndHandle, ref RECT rect);
        [DllImport("dvrssw.dll")]
        public static extern int  ExitDVRS ();
        [DllImport("dvrssw.dll")]
        public static extern  int SaveCaptureImage (int hChannel, System.String path) ;
        [DllImport("dvrssw.dll")]
        public static extern  int SaveOneCaptureVideo (int  hChannel , System.String dirstr);
        [DllImport("dvrssw.dll")]
        public static extern int StopOneCaptureVideo (int hChannel );
        [DllImport("dvrssw.dll")]
        public static extern int SetChangeVideoSize (int hChannel, int  sizeindex);
        [DllImport("dvrssw.dll")]
        public static extern int SetVideoCHName(int hChannel, System.String namestr);
        [DllImport("dvrssw.dll")]
        public static extern int GetSysTotalChannels ();
        [DllImport("dvrssw.dll")]
        public static extern int SetColorParameter (int  hChannel, int br , int  co , int sa, int hu);



    }
}
