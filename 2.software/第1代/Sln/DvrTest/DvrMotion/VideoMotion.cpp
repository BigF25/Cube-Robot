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
	m_cvmode = CV_RETR_EXTERNAL;//������Ե��ȡʱ�Ĳ���
	cvInitFont(&m_cvfont1, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, 8);
	//����Ƶ�л�������Ȥ��������ô�������س������ߣ�������������
	pt1.x=0;//(��Ƶ�����µ�)
	pt1.y=0;
	pt2.x=width;//(��Ƶ�����ϵ�)
	pt2.y=height;
	m_bndRect=cvRect(0,0,0,0);//��cvBoundingRect������Ӿ���ʱ��Ҫ�ľ���
	m_avgX = 0;//The midpoint X position of the rectangle surrounding the moving objects
	m_avgY = 0;//The midpoint Y position of the rectangle surrounding the moving objects
	m_avgX1= 0;//�����ϲ�����ĳ���
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
		cimg.CopyOf(pImage); // ����ͼƬ
		cimg.DrawToHDC(hDC,&m_ImageRect); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
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
	 CvSeq * contour;//������Ե��ȡʱ�Ĳ���
	 CvMemStorage * storage ;//������Ե��ȡʱ�Ĳ���
	IplConvKernel* m_cvElement;
	if(CheckMotionTarget()== FALSE) return waring_cnt;
	m_cvElement = cvCreateStructuringElementEx(13,13,1,1,CV_SHAPE_RECT,NULL);
	nFrmNum ++;
	//��̬ѧ����ʱ�ں˵Ĵ�С 
 //���ַ���ʱһ��Ҫ��using namespace std;д��ǰ�棬��������,������������ʾ���ַ���
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
   //��˹�˲��ȣ���ƽ��ͼ��
   cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
   //����Ƶ�����ò���������Ȥ������
   //cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
   //ShowMotionSelectArea(pImage);
   //��ǰ֡������ͼ���,cvAbsDiff�������������ľ���ֵ
   cvAbsDiff(pFrameMat, pBkMat, pFrMat);
   //��ֵ��ǰ��ͼ
   cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
   
   //ͨ�����ұ߽��ҳ�ROI���������ڵ��˶�������������ȫĿ�굵��
   //cvCanny(pFrImg, pBkImg, 50, 150, 3);
   cvDilate(pFrImg,pBkImg,m_cvElement,1);
   //���±���///////////////////////////////////////////////////
   cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
  }
   else if(nFrmNum > 3)//�ӵ���֡��ʼ��������ȫĿ�굵����������ɾ���˶�����������
  {
     storage = cvCreateMemStorage(0);//������Ե��ȡʱ�Ĳ���
	cvCvtColor(pImage, pFrImg, CV_BGR2GRAY);
    cvConvert(pFrImg, pFrameMat);
   //��˹�˲��ȣ���ƽ��ͼ��
    cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
   //����Ƶ�����ò���������Ȥ������
   //cvSetImageROI(pFrame,rect1);
   //cvRectangle(pImage,pt1,pt2,CV_RGB(255,0,0),2, 8, 0 );
   //��ǰ֡������ͼ���,cvAbsDiff�������������ľ���ֵ
   cvAbsDiff(pFrameMat, pBkMat, pFrMat);
   //��ֵ��ǰ��ͼ,void cvThreshold( const CvArr* src, CvArr* dst, double threshold,
            //double max_value, int threshold_type );
   cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
   //ͨ�����ұ߽��ҳ�ROI���������ڵ��˶�������������ȫĿ�굵��
   //cvCanny(pFrImg, pBkImg, 50, 150, 3);
   cvDilate(pFrImg,pBkImg,m_cvElement,1);
   cvFindContours( pBkImg, storage, &contour, sizeof(CvContour),
    m_cvmode, CV_CHAIN_APPROX_SIMPLE);
   //process each moving contour in the current frame�ú���cvBoundingRect
   for(;contour!=0;contour=contour->h_next)
   {
    //Get a bounding rectangle around the moving object.
    m_bndRect = cvBoundingRect(contour, 0);
    
    //Get an average X position of the moving contour.
    m_avgX = (m_bndRect.x + m_bndRect.x + m_bndRect.width) / 2; 
    m_avgY = (m_bndRect.y + m_bndRect.y + m_bndRect.height) / 2;
    pt5.x=m_bndRect.x;//д�ֵ����½ǵ�
    pt5.y=m_avgY;
	 pt3.x = m_bndRect.x;
     pt3.y = m_bndRect.y;
     pt4.x = m_bndRect.x + m_bndRect.width;
     pt4.y = m_bndRect.y + m_bndRect.height;

	if(FindMotionTarget(m_bndRect))
    {
      //cvPutText(pFrame,msg[No].c_str(), pt5, &font1, cvScalar(0,255,0));
      //�ڸ���������Ѱ�ҿ��Ƿ���ƥ��ĳ�����û�����ʾ���³���
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

   //���±���///////////////////////////////////////////////////
   cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
   //----------------------------
   cvClearMemStorage(storage);
   cvReleaseMemStorage(&storage);
   //------------------------------
}
cvReleaseStructuringElement(&m_cvElement);//ɾ���ṹԪ��
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
			pt1.x=x0*x_inc;//(��Ƶ�����µ�)
			pt1.y=y0*y_inc;
			pt2.x=x1*x_inc;//(��Ƶ�����ϵ�)
			pt2.y=y1*y_inc;
			break;
		}
		case 1:
		{
			m_min_pt1.x=x0*x_inc;//(��Ƶ�����µ�)
			m_min_pt1.y=y0*y_inc;
			m_min_pt2.x=x1*x_inc;//(��Ƶ�����ϵ�)
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
	
	if((cvrct.height>m_min_height)&&(cvrct.width >m_min_width)) //�ѳ���С��ĳ����ֵ�ĸ��ž���ȥ��
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