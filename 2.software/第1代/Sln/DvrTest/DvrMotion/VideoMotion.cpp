#include "StdAfx.h"
#include "VideoMotion.h"
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
CVideoMotion::CVideoMotion(void)
{
	 m_pMainImage = NULL;
	 m_pRgbBuf = NULL;
	 m_currwidth = 0;
	 m_currheight =0;
	 pFrImg = NULL;
     pBkImg = NULL;
	 pFrImg1 = NULL;
     pFrameMat = NULL;
     pFrMat = NULL;
     pBkMat = NULL;
     pFrMat1 = NULL;
	 nFrmNum =0;
	 m_bisShowSelectLine =FALSE;
	 SetcvMinTarget(20,20);
	 SetcvMaxTarget(40,40);
	 m_ndImageHandle = NULL;
}


CVideoMotion::~CVideoMotion(void)
{
	ReleasecvImage();
}


void CVideoMotion::CreatecvImage(int width,int height)
{
	
	m_VideoMotionCritical.Lock();
	m_pMainImage = cvCreateImage( cvSize(width,height), 8, 3 );
	pBkImg = cvCreateImage(cvSize(m_pMainImage->width, m_pMainImage->height),  IPL_DEPTH_8U,1);
	pFrImg = cvCreateImage(cvSize(m_pMainImage->width, m_pMainImage->height),  IPL_DEPTH_8U,1);
	pBkMat = cvCreateMat(m_pMainImage->height, m_pMainImage->width, CV_32FC1);
	pFrMat = cvCreateMat(m_pMainImage->height, m_pMainImage->width, CV_32FC1);
	pFrameMat = cvCreateMat(m_pMainImage->height, m_pMainImage->width, CV_32FC1);
	cvCvtColor(m_pMainImage, pBkImg, CV_BGR2GRAY);
	cvCvtColor(m_pMainImage, pFrImg, CV_BGR2GRAY);
	cvConvert(pFrImg, pFrameMat);
	cvConvert(pFrImg, pFrMat);
	cvConvert(pFrImg, pBkMat);
		
	
	//-------------------------------------------	
	m_linetype=CV_AA;
	m_cvmode = CV_RETR_EXTERNAL;//轮廓边缘提取时的参数
	cvInitFont(&m_cvfont1, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, 8);
	//在视频中画出感兴趣的区域，怎么样才能沿车道画线？？？？？？？
	pt1.x=0;//(视频中左下点)
	pt1.y=0;
	pt2.x=width;//(视频中右上点)
	pt2.y=height;
	m_bndRect=cvRect(0,0,0,0);//用cvBoundingRect画出外接矩形时需要的矩形
	m_avgX = 0;//The midpoint X position of the rectangle surrounding the moving objects
	m_avgY = 0;//The midpoint Y position of the rectangle surrounding the moving objects
	m_avgX1= 0;//用来合并相近的车辆
	m_avgY1= 0;   
	m_No =0;
	m_findCnt = 0;
	//--------------------------------------------------
	m_pRgbBuf = new BYTE[width*height*3];
	m_currwidth  = width;
	m_currheight = height;
	for(int i=0;i<MAX_SERACH_POINT;i++)
	{
		TrackBlock[i]=NULL;
		TrackBlock[i]=(AvTrackBlock *) malloc(sizeof(AvTrackBlock));
	}
	m_VideoMotionCritical.Unlock();
   

}
void  CVideoMotion::ReleasecvImage()
{
	m_VideoMotionCritical.Lock();
	if(m_pMainImage)
	{
		cvReleaseImage(&m_pMainImage);
		m_pMainImage = NULL;
	}
	if(pFrImg)
	{
		cvReleaseImage(&pFrImg);
		pFrImg = NULL;
	}
	if(pBkImg)
	{
		cvReleaseImage(&pBkImg);
		pBkImg = NULL;
	}
	if(pFrameMat)
	{
		cvReleaseMat(&pFrameMat);
		pFrameMat = NULL;
	}
	if(pFrMat)
	{
		cvReleaseMat(&pFrMat);
		pFrMat = NULL;
	}
	if(pBkMat)
	{
		cvReleaseMat(&pBkMat);
		pBkMat = NULL;
	}

	if(m_pRgbBuf)
	{
		delete [] m_pRgbBuf;
		m_pRgbBuf = NULL;
	}
	for(int i=0;i<MAX_SERACH_POINT;i++)
	{
		
		free(TrackBlock[i]);
		TrackBlock[i]=NULL;
	}
	m_VideoMotionCritical.Unlock();
}
 int CVideoMotion::DrawPicToHDC(IplImage *pImage)
{
	if(m_ndImageHandle)
	{
		HDC hDC= ::GetDC(m_ndImageHandle);
		CvvImage cimg;
		cimg.CopyOf(pImage); // 复制图片
		cimg.DrawToHDC(hDC,&m_ImageRect); // 将图片绘制到显示控件的指定区域内
		::ReleaseDC(m_ndImageHandle,hDC);
	}
	return 0;
}
int CVideoMotion::SetVideoMotion(BYTE *YUVBuffer,int width,int height)
{
	int cnt;
	if((m_pMainImage==NULL)||(m_currwidth!=width)||(m_currheight != height))
	{
		ReleasecvImage();
		CreatecvImage(width,height);
	}
	m_VideoMotionCritical.Lock();
	if(m_pMainImage == NULL) return 0;
	ChangeYUVToRGB(YUVBuffer,m_pRgbBuf,width,height);
	BYTE *data = (BYTE *)m_pMainImage->imageData;
	memcpy(data,m_pRgbBuf,width*height*3);
	//----------------------------DO  Motion Analyzer
	cnt = VideoMotionAnalyzer(m_pMainImage);
	ShowMotionSelectArea(m_pMainImage);
	//----------------------------
	DrawPicToHDC(m_pMainImage);
	m_VideoMotionCritical.Unlock();
	return cnt;
}
int CVideoMotion::VideoMotionAnalyzer(IplImage *pImage)
{
	int waring_cnt =0;
	 CvSeq * contour;//轮廓边缘提取时的参数
	 CvMemStorage * storage ;//轮廓边缘提取时的参数
	IplConvKernel* m_cvElement;
	if(CheckMotionTarget()== FALSE) return waring_cnt;
	m_cvElement = cvCreateStructuringElementEx(13,13,1,1,CV_SHAPE_RECT,NULL);
	nFrmNum ++;
	//形态学处理时内核的大小 
 //用字符串时一定要把using namespace std;写在前面，否则不能用,下面是用于显示的字符串
	if(nFrmNum  == 1)
	{
		cvCvtColor(m_pMainImage, pBkImg, CV_BGR2GRAY);
		cvCvtColor(m_pMainImage, pFrImg, CV_BGR2GRAY);
		cvConvert(pFrImg, pFrameMat);
		cvConvert(pFrImg, pFrMat);
		cvConvert(pFrImg, pBkMat);
	}
	else if(nFrmNum == 3)
	{
   cvCvtColor(pImage, pFrImg, CV_BGR2GRAY);
   cvConvert(pFrImg, pFrameMat);
   //高斯滤波先，以平滑图像
   cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
   //在视频中设置并画出感兴趣的区域
   //cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
   //ShowMotionSelectArea(pImage);
   //当前帧跟背景图相减,cvAbsDiff计算两个数组差的绝对值
   cvAbsDiff(pFrameMat, pBkMat, pFrMat);
   //二值化前景图
   cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
   
   //通过查找边界找出ROI矩形区域内的运动车辆，建立完全目标档案
   //cvCanny(pFrImg, pBkImg, 50, 150, 3);
   cvDilate(pFrImg,pBkImg,m_cvElement,1);
   //更新背景///////////////////////////////////////////////////
   cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
  }
   else if(nFrmNum > 3)//从第三帧开始，根据完全目标档案来新增或删除运动车辆档案。
  {
     storage = cvCreateMemStorage(0);//轮廓边缘提取时的参数
	cvCvtColor(pImage, pFrImg, CV_BGR2GRAY);
    cvConvert(pFrImg, pFrameMat);
   //高斯滤波先，以平滑图像
    cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
   //在视频中设置并画出感兴趣的区域
   //cvSetImageROI(pFrame,rect1);
   //cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
   //当前帧跟背景图相减,cvAbsDiff计算两个数组差的绝对值
   cvAbsDiff(pFrameMat, pBkMat, pFrMat);
   //二值化前景图,void cvThreshold( const CvArr* src, CvArr* dst, double threshold,
            //double max_value, int threshold_type );
   cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
   //通过查找边界找出ROI矩形区域内的运动车辆，建立完全目标档案
   //cvCanny(pFrImg, pBkImg, 50, 150, 3);
   cvDilate(pFrImg,pBkImg,m_cvElement,1);
   cvFindContours( pBkImg, storage, &contour, sizeof(CvContour),
    m_cvmode, CV_CHAIN_APPROX_SIMPLE);
   //process each moving contour in the current frame用函数cvBoundingRect
   for(;contour!=0;contour=contour->h_next)
   {
    //Get a bounding rectangle around the moving object.
    m_bndRect = cvBoundingRect(contour, 0);
    
    //Get an average X position of the moving contour.
    m_avgX = (m_bndRect.x + m_bndRect.x + m_bndRect.width) / 2; 
    m_avgY = (m_bndRect.y + m_bndRect.y + m_bndRect.height) / 2;
    pt5.x=m_bndRect.x;//写字的左下角点
    pt5.y=m_avgY;
	 pt3.x = m_bndRect.x;
     pt3.y = m_bndRect.y;
     pt4.x = m_bndRect.x + m_bndRect.width;
     pt4.y = m_bndRect.y + m_bndRect.height;

	if(FindMotionTarget(m_bndRect))
    {
      //cvPutText(pFrame,msg[No].c_str(), pt5, &font1, cvScalar(0,255,0));
      //在跟踪数组中寻找看是否有匹配的车辆，没有则表示是新车辆
		char msg[32];
		sprintf(msg,"M");
		m_findCnt++;
		if(m_ndImageHandle)
		{
			cvRectangle(pImage,pt3,pt4,CV_RGB(0,0,255),1, 8, 0 );
			cvPutText(pImage,msg, pt5, &m_cvfont1, cvScalar(0,255,0));
		}
        TrackBlock[m_No]->FramesTracked=nFrmNum;
        TrackBlock[m_No]->avgX=m_avgX;
        TrackBlock[m_No]->avgY=m_avgY;
        if(m_No==MAX_SERACH_POINT-1)
		{
			m_No=0;
		}
		else
	    {
			m_No++;
	    }
        m_FindCar=true;
		waring_cnt ++;
		if(m_findCnt >3) break;
	}
	//if(m_FindCar) break;
   }

   //更新背景///////////////////////////////////////////////////
   cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
   //----------------------------
   cvClearMemStorage(storage);
   cvReleaseMemStorage(&storage);
   //------------------------------
}
cvReleaseStructuringElement(&m_cvElement);//删除结构元素
return waring_cnt;
}
void CVideoMotion::SetcvSearchArea(int x0,int x1,int y0,int y1)
{
	pt1.x=x0;
	pt1.y=y0;
	pt2.x=x1;
	pt2.y=y1;


}
void CVideoMotion::GetcvSearchArea(int* x0,int* x1,int* y0,int* y1)
{
	*x0 =pt1.x ;
	*y0 =pt1.y;
	*x1 =pt2.x;
	*y1 =pt2.y;
}
void CVideoMotion::GetcvMinTargetArea(int* x0,int* x1,int* y0,int* y1)
{
	*x0 =m_min_pt1.x;
	*y0 =m_min_pt1.y;
	*x1 =m_min_pt2.x;
	*y1 =m_min_pt2.y;
}
void CVideoMotion::SetcvMinTargetArea(int x0,int x1,int y0,int y1)
{
	m_min_pt1.x=x0;
	m_min_pt1.y=y0;
	m_min_pt2.x=x1;
	m_min_pt2.y=y1;

	m_min_width = abs(m_min_pt2.x-m_min_pt1.x);
	m_min_height =  abs(m_min_pt2.y - m_min_pt1.y);

}

void CVideoMotion::SetcvSearchRect(CRect rc,int x0,int x1,int y0,int y1)
{
	double w = rc.right - rc.left;
	double h = rc.bottom - rc.top;
	double x_inc = (double)m_currwidth/w;
	double y_inc =(double)m_currheight/h;
	switch(m_SelectMenuIndex)
	{
		case 0:
		default:
		{
			pt1.x=x0*x_inc;//(视频中左下点)
			pt1.y=y0*y_inc;
			pt2.x=x1*x_inc;//(视频中右上点)
			pt2.y=y1*y_inc;
			break;
		}
		case 1:
		{
			m_min_pt1.x=x0*x_inc;//(视频中左下点)
			m_min_pt1.y=y0*y_inc;
			m_min_pt2.x=x1*x_inc;//(视频中右上点)
			m_min_pt2.y=y1*y_inc;
			m_min_width = abs(m_min_pt2.x-m_min_pt1.x);
	        m_min_height =  abs(m_min_pt2.y - m_min_pt1.y);
			break;
		}
	}

}

void CVideoMotion::SetcvMaxTarget(int w,int h)
{
	 m_max_width =w;
	 m_max_height =h;
}
void CVideoMotion::SetcvMinTarget(int w,int h)
{
	m_min_pt1.x =0;
	m_min_pt1.y=0;
	m_min_pt2.x = w;
	m_min_pt2.y = h;
	m_min_width  = w;
	 m_min_height = h;
}

BOOL CVideoMotion::FindMotionTarget(CvRect cvrct)
{
	BOOL bFind =FALSE;
	BOOL bXFind= FALSE;
	BOOL bYFind = FALSE;
	//TRACE("x =%d y =%d w= %d,h=%d  [%d-%d]\n",m_bndRect.x,m_bndRect.y,m_bndRect.width,m_bndRect.height,m_min_width,m_min_height);
	//TRACE("pt1[%d-%d] pt2[%d-%d]\n",pt1.x,pt1.y,pt2.x,pt2.y);
	
	if((cvrct.height>m_min_height)&&(cvrct.width >m_min_width)) //把长度小于某个阀值的干扰矩形去掉
	{
		if(cvrct.x<pt2.x)
		{
			if(cvrct.x>=pt1.x)
			{
				bXFind = TRUE;	
			}else
			{
				if(cvrct.x+cvrct.width>= pt1.x)
				{
					bXFind = TRUE;
				}
			}
		}

		if(cvrct.y<pt2.y)
		{
			if(cvrct.y>=pt1.y)
			{
				bYFind = TRUE;	
			}else
			{
				if(cvrct.y+cvrct.height>= pt1.y)
				{
					bYFind = TRUE;
				}
			}
		}

	}
	if(bXFind&bYFind)
	{
		//TRACE("x =%d y =%d w= %d,h=%d  [%d-%d]\n",m_bndRect.x,m_bndRect.y,m_bndRect.width,m_bndRect.height,m_min_width,m_min_height);
		//TRACE("pt1[%d-%d] pt2[%d-%d]\n",pt1.x,pt1.y,pt2.x,pt2.y);
		bFind = TRUE;
	}

	return bFind;
	
}

void CVideoMotion::SetMotionSelectMenuIndex(int menuIndex)
{
	m_SelectMenuIndex = menuIndex;
}
void CVideoMotion::ShowMotionSelectArea(IplImage *pImage)
{
	if(m_SelectMenuIndex ==1)
	{
		cvRectangle(pImage,m_min_pt1,m_min_pt2,CV_RGB(255,255,0),2, 8, 0 );
	}
	cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
#if 0	
	
	switch(m_SelectMenuIndex)
	{
	case 1:

	{
		cvRectangle(pImage,m_min_pt1,m_min_pt2,CV_RGB(255,255,0),2, 8, 0 );
		break;
	}
	case 0:
	default:
	{
		cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
		break;
	}
	
	}
#endif 
}
BOOL CVideoMotion::CheckMotionTarget()
{
	int w = abs(pt2.x-pt1.x);
	int h =  abs(pt2.y-pt1.y);
	if((w<m_min_width)&&(h<m_min_height))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}