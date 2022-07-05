#include "StdAfx.h"
#include "VideoStitcher.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching/stitcher.hpp>
using namespace std;
using namespace cv;


CVideoStitcher::CVideoStitcher(void)
{
	m_pRgbBuf1 = new BYTE[1920*1080*3];
	m_pRgbBuf2 = new BYTE[1920*1080*3];
	m_pRgbBuf3 = new BYTE[1920*1080*3];
	m_pImage2 = NULL;
	m_pImage1 = NULL;
	m_pImage3 = NULL;
	m_currwidth1 = 0;
	m_currheight1 = 0;

	m_currwidth2 = 0;
	m_currheight2 = 0;
	m_currwidth3 = 0;
	m_currheight3 = 0;
	bool try_use_gpu = false;
}


CVideoStitcher::~CVideoStitcher(void)
{
	delete [] m_pRgbBuf1;
	delete [] m_pRgbBuf2;
	delete [] m_pRgbBuf3;
}
 int CVideoStitcher::DrawPicToHDC(IplImage *pImage)
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
 void CVideoStitcher::CreatecvImage1(int width,int height)
{
	m_pImage1 = cvCreateImage( cvSize(width,height), 8, 3 );
	m_currwidth1 = width;
	m_currheight1 = height;

}
 void  CVideoStitcher::ReleasecvImage1()
{
	if(m_pImage1)
	{
		cvReleaseImage(&m_pImage1);
		m_pImage1 = NULL;
	}
 }
 void CVideoStitcher::CreatecvImage2(int width,int height)
{
	m_pImage2 = cvCreateImage( cvSize(width,height), 8, 3 );
	m_currwidth2 = width;
	m_currheight2 = height;
}
  void  CVideoStitcher::ReleasecvImage2()
{
	if(m_pImage2)
	{
		cvReleaseImage(&m_pImage2);
		m_pImage2 = NULL;
	}
 }

  void CVideoStitcher::CreatecvImage3(int width,int height)
{
	m_pImage3 = cvCreateImage( cvSize(width,height), 8, 3 );
	m_currwidth3 = width;
	m_currheight3 = height;
}
  void  CVideoStitcher::ReleasecvImage3()
{
	if(m_pImage3)
	{
		cvReleaseImage(&m_pImage3);
		m_pImage2 = NULL;
	}
 }
 void  CVideoStitcher::cvVideoStitcher(BYTE * buf1,BYTE *buf2,BYTE*buf3,int w,int h)
 {
	 //TRACE("cvVideoStitcher\n"); 
	 m_VideoStitcherCritical.Lock();
#if 1
	 if((m_pImage1==NULL)||(m_currwidth1!=w)||(m_currheight1 != h))
	{
		ReleasecvImage1();
		CreatecvImage1(w,h);
	}
	 //TRACE("cvVideoStitcher01\n"); 
	if((m_pImage2==NULL)||(m_currwidth2!=w)||(m_currheight2 != h))
	{
		ReleasecvImage2();
		CreatecvImage2(w,h);
	}
	//TRACE("cvVideoStitcher03\n"); 
	if((m_pImage3==NULL)||(m_currwidth3!=w)||(m_currheight3 != h))
	{
		ReleasecvImage3();
		CreatecvImage3(w,h);
	}
  //TRACE("cvVideoStitcher11\n"); 
 ChangeYUVToRGB(buf1,m_pRgbBuf1,w,h);
 ChangeYUVToRGB(buf2,m_pRgbBuf2,w,h);
 ChangeYUVToRGB(buf3,m_pRgbBuf3,w,h);
 BYTE *data = (BYTE *)m_pImage1->imageData;
 memcpy(data,m_pRgbBuf1,w*h*3);
 data = (BYTE *)m_pImage2->imageData;
 memcpy(data,m_pRgbBuf2,w*h*3);

 data = (BYTE *)m_pImage3->imageData;
 memcpy(data,m_pRgbBuf3,w*h*3);

 int lineByte = (w + 3)/4*4;


 Mat img1;
 Mat img2;
 Mat img3;
 img1 = m_pImage1;
 img2 = m_pImage2;
 img3 = m_pImage3;
 imgs.push_back(img1);
 imgs.push_back(img2);
 imgs.push_back(img3);
 Mat pano;    
 //Stitcher stitcher = Stitcher::createDefault(false);
 //Stitcher::Status status = stitcher.stitch(imgs, pano);  
//imshow("全景图像", img1);   
 //TRACE("cvVideoStitcher2\n"); 

  IplImage *src;
 src=&IplImage(img2);
 //TRACE("cvVideoStitcher3\n"); 
 DrawPicToHDC(src);
 imgs.pop_back();
 imgs.pop_back();
 imgs.pop_back();
#endif 
 m_VideoStitcherCritical.Unlock();
 }