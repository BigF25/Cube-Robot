#pragma once
using namespace std;
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

#define MAX_SERACH_POINT 2
class CVideoMotion
{
public:
	 CVideoMotion(void);
	~CVideoMotion(void);
public:
	 IplImage *m_pMainImage;
	 int m_currwidth;
	 int m_currheight;
	 int m_max_width;
	 int m_max_height;
	 int m_min_width;
	 int m_min_height;
	 CvPoint m_min_pt1;
	 CvPoint m_min_pt2;
	 int m_findCnt;
	 HWND m_ndImageHandle;
	 RECT m_ImageRect;
	 BYTE *m_pRgbBuf;
	 int m_SelectMenuIndex;
	 BOOL m_bisShowSelectLine;
	 CCriticalSection m_VideoMotionCritical;
	 //-----------
	 IplImage* pFrImg;
     IplImage* pBkImg;
	 IplImage* pFrImg1;
     CvMat* pFrameMat;
     CvMat* pFrMat;
     CvMat* pBkMat;
	 CvMat* pFrMat1;
     //CvSeq * contour;//轮廓边缘提取时的参数
	 int nFrmNum;
	 CvFont m_cvfont1;//初始化字体格式
	 CvPoint pt1;
	 CvPoint pt2;
	 CvPoint pt3;
	 CvPoint pt4;
	 CvPoint pt5;

	 int m_No;//用于记录显示车辆
     bool m_FindCar;
	 int m_linetype;
	 int m_cvmode;
	CvRect m_bndRect;//用cvBoundingRect画出外接矩形时需要的矩形
	int m_avgX ;//The midpoint X position of the rectangle surrounding the moving objects
	int m_avgY ;//The midpoint Y position of the rectangle surrounding the moving objects
	int m_avgX1;//用来合并相近的车辆
	int m_avgY1;  
	
	 //------------
	 AvTrackBlock *TrackBlock[MAX_SERACH_POINT];
	 //----------------------------
	 int   DrawPicToHDC(IplImage *pImage);
	 void  ReleasecvImage();
	 void  CreatecvImage(int width,int height);
	 int SetVideoMotion(BYTE *YUVBuffer,int width,int height);
	 int VideoMotionAnalyzer(IplImage *pImage);
	 void SetcvSearchRect(CRect rc,int x0,int x1,int y0,int y1);
	 void SetcvSearchArea(int x0,int x1,int y0,int y1);
	 void SetcvMinTargetArea(int x0,int x1,int y0,int y1);
	 void SetcvMaxTarget(int w,int h);
	 void SetcvMinTarget(int w,int h);
	 BOOL FindMotionTarget(CvRect cvrct);
	 void SetMotionSelectMenuIndex(int menuIndex);
	 void ShowMotionSelectArea(IplImage *pImage);
	 BOOL CheckMotionTarget();
	 void GetcvSearchArea(int* x0,int* x1,int* y0,int* y1);
	 void GetcvMinTargetArea(int* x0,int* x1,int* y0,int* y1);
};

