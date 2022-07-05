#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
using namespace std;
using namespace cv;
class CVideoStitcher
{
public:
	 HWND m_ndImageHandle;
	  RECT m_ImageRect;
	 int m_currwidth1;
	 int m_currheight1;
	 int m_currwidth2;
	 int m_currheight2;
	 int m_currwidth3;
	 int m_currheight3;
	 BYTE *m_pRgbBuf1;
	 BYTE *m_pRgbBuf2;
	 BYTE *m_pRgbBuf3;
	 IplImage *m_pImage1;
	 IplImage *m_pImage2;
	 IplImage *m_pImage3;
	 vector<Mat> imgs;
	 //Stitcher m_stitcher;
	 CCriticalSection m_VideoStitcherCritical;
	  void  cvVideoStitcher(BYTE * buf1,BYTE *buf2,BYTE*buf3,int w,int h);
	  int DrawPicToHDC(IplImage *pImage);
	  void CreatecvImage1(int width,int height);
	  void CreatecvImage2(int width,int height);
	  void CreatecvImage3(int width,int height);
	   void  ReleasecvImage1();
	    void  ReleasecvImage2();
			    void  ReleasecvImage3();
public:
	CVideoStitcher(void);
	~CVideoStitcher(void);
};

