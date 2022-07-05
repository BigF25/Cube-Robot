// OpenCVtest.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
using namespace cv;
using namespace std;
//====================================================================�ṹ��
struct Cube
{
	//UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR F R U B L D
	int CubeData[3][54];
	int Idx[54];
	int GetValueFlag[54];
};
//====================================================================��������
void RectInit(void);
string my_i2s(int i);
Cube KmeanCluster(Cube cube);
Cube CutOverNum(Cube cube);
Cube GetCubeData(Mat src0, Mat src1);
bool CubeCanSolve(Cube cube);
bool CubeIdxIs6_9(Cube cube);
void PrinfCube(Cube cube);
Cube Cluster(Cube cube);
bool IsPictureCaped(void);
#define CENTER_MOVE      true
#define CENTER_NO_MOVE   false
Cube CenterGrab(Cube cube, bool CenterMove);
//====================================================================ȫ�ֱ���
Rect rect[50];
Rect rect0[7];
Rect rect1[18];
Rect rect2[7];
Rect rect3[18];
Scalar scalar[50];
char str[6] = { 'F', 'R', 'U', 'B', 'L', 'D' };
//====================================================================�궨
//�궨��������ǿ�ȡ�
//���ƴ��ǿ����
//double light[50] = {
//	428, 460, 452, 514, 430, 477, 463, 427, 470, 549, 542, 456, 420, 430, 489, 572, 561, 470, 428, 424, 475, 547, 532, 461, 411, 420, 461, 408, 451, 500, 419, 424, 394, 436, 481, 481, 437, 392, 408, 463, 512, 513, 469, 411, 409, 458, 509, 518, 463, 415
//};
//ȫ�״������ ȫ��ɫps����//�����õ�
//double light[50] = {
//643,703,687,705,701,706,697,570,601,661,660,663,427,570,562,701,702,600,466,560,597,707,706,614,538,698,708,659,685,706,704,701,543,471,626,633,364,460,487,599,543,464,404,404,450,430,529,459,311,620, };

//double light[50] = {
//704,705,705,705,706,706,705,595,457,560,550,657,591,569,666,560,593,702,576,577,530,610,632,700,602,642,681,665,684,705,682,708,567,496,689,652,337,467,552,699,667,636,527,469,553,580,652,574,299,589, };

//11.29 3:00
double light[50] = {
690,704,703,705,697,705,697,590,583,672,705,649,538,565,675,695,705,669,524,560,609,688,705,636,553,625,663,652,666,705,667,709,603,602,631,653,638,647,618,651,668,696,675,673,634,657,643,709,703,689, };

double LightScale[54];  //����ǿ�ȱ���
//�궨����ͶӰ����
double B1 = 46;
double B2 = 136;
//=====================================================================�궨��
#define F  0
#define R  1
#define U  2
#define B  3
#define L  4
#define D  5
//=====================================================================������
int _tmain(int argc, _TCHAR* argv[])
{
	////�����ǿ����
	double LightSum = 0;
	for (int i = 0; i < 50; i++)
	{
		LightSum += light[i];
	}
	double LightAverage = LightSum / 50.0;
	for (int i = 0; i < 50; i++)
	{
		LightScale[i] = light[i] / LightAverage;
		//LightScale[i] = 1;
	}
	////������ת����
	double cB1 = cos(B1*3.141592654 / 180.0);
	double cB2 = cos(B2*3.141592654 / 180.0);
	double sB1 = sin(B1*3.141592654 / 180.0);
	double sB2 = sin(B2*3.141592654 / 180.0);
	double Rx[3][3] = {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, cB1, -sB1 },
		{ 0.0, sB1, cB1 }
	};
	double Ry[3][3] = {
		{ cB2, 0.0, sB2 },
		{ 0.0, 1.0, 0.0 },
		{ -sB2, 0.0, cB2 }
	};
	//��ʼ���ɼ�λ��
	RectInit();
	//��ʱ
	while (true)
	{
		cout << "�ȴ�ͼ��...." << endl;
		while (!IsPictureCaped())  //�ȴ����ⱻ����
		{
			Sleep(5);
		}
		double start = (double)cvGetTickCount();
		//��ȡͼ��
		Mat src00 = imread(".\\Bridge\\00.bmp");  //352*288
		Mat src01 = imread(".\\Bridge\\01.bmp");
		Mat src02 = imread(".\\Bridge\\02.bmp");
		Mat src03 = imread(".\\Bridge\\03.bmp");
		Mat src10 = imread(".\\Bridge\\10.bmp");  //352*288
		Mat src11 = imread(".\\Bridge\\11.bmp");
		Mat src12 = imread(".\\Bridge\\12.bmp");
		Mat src13 = imread(".\\Bridge\\13.bmp");

		//Mat src00 = imread("00.bmp");
		//Mat src01 = imread("01.bmp");
		//Mat src02 = imread("02.bmp");
		//Mat src03 = imread("03.bmp");
		//Mat src10 = imread("10.bmp");  //352*288
		//Mat src11 = imread("11.bmp");
		//Mat src12 = imread("12.bmp");
		//Mat src13 = imread("13.bmp");



		//��д���Զ�����
		{
			//////////////////////////////////��ʾͼƬ����
			//{
			//	imshow("a", src03);
			//	waitKey(0);
			//}
			///////////////////////////////��ʾ������Ϣ����
			//{
			//	for (int i = 0; i < src00.rows; i++) {
			//		for (int j = 0; j < src00.cols; j++) {
			//			int b = src00.at<Vec3b>(i, j)[0];
			//			int g = src00.at<Vec3b>(i, j)[1];
			//			int r = src00.at<Vec3b>(i, j)[2];
			//			cout << "(" << i << "," << j << "):" << b << "," << g << "," << r << ";";
			//		}
			//		cout << endl;
			//	}
			//}
			//////////////////////////////////�޸�������ɫ
			{
				//for (int i = 0; i < src00.rows; i++) {
				//	for (int j = 0; j < src00.cols; j++) {
				//		src00.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src01.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src02.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src03.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src10.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src11.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src12.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//		src13.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//	}
				//}
				////00.bmp
				//for (int k = 0; k < 7; k++) {
				//	for (int i = rect0[k].y; i < rect0[k].y + rect0[k].height; i++) {
				//		for (int j = rect0[k].x; j < rect0[k].x + rect0[k].width; j++) {
				//			//src00.at<Vec3b>(i, j) = Vec3b(39, 127, 255);//��ɫ
				//			src00.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////01.bmp
				//for (int k = 0; k < 18; k++) {
				//	for (int i = rect1[k].y; i < rect1[k].y + rect1[k].height; i++) {
				//		for (int j = rect1[k].x; j < rect1[k].x + rect1[k].width; j++) {
				//			if (k % 6 == 0 || k % 6 == 1 || k % 6 == 2)
				//				//src01.at<Vec3b>(i, j) = Vec3b(255, 0, 0);//��ɫ
				//				src01.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//			else
				//				//src01.at<Vec3b>(i, j) = Vec3b(0, 255, 255);//��ɫ
				//				src01.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////02.bmp
				//for (int k = 0; k < 7; k++) {
				//	for (int i = rect2[k].y; i < rect2[k].y + rect2[k].height; i++) {
				//		for (int j = rect2[k].x; j < rect2[k].x + rect2[k].width; j++) {
				//			//src02.at<Vec3b>(i, j) = Vec3b(0, 0, 255);//��ɫ
				//			src02.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////03.bmp
				//for (int k = 0; k < 18; k++) {
				//	for (int i = rect3[k].y; i < rect3[k].y + rect3[k].height; i++) {
				//		for (int j = rect3[k].x; j < rect3[k].x + rect3[k].width; j++) {
				//			if (k % 6 == 0 || k % 6 == 1 || k % 6 == 2)
				//				//src03.at<Vec3b>(i, j) = Vec3b(0, 255, 0);//��ɫ
				//				src03.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//			else
				//				//src03.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//				src03.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////10.bmp
				//for (int k = 0; k < 7; k++) {
				//	for (int i = rect0[k].y; i < rect0[k].y + rect0[k].height; i++) {
				//		for (int j = rect0[k].x; j < rect0[k].x + rect0[k].width; j++) {
				//			//src10.at<Vec3b>(i, j) = Vec3b(255, 0, 0);//��ɫ
				//			src10.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////11.bmp
				//for (int k = 0; k < 18; k++) {
				//	for (int i = rect1[k].y; i < rect1[k].y + rect1[k].height; i++) {
				//		for (int j = rect1[k].x; j < rect1[k].x + rect1[k].width; j++) {
				//			if (k % 6 == 0 || k % 6 == 1 || k % 6 == 2)
				//				//src11.at<Vec3b>(i, j) = Vec3b(0, 0, 255);//��ɫ
				//				src11.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//			else
				//				//src11.at<Vec3b>(i, j) = Vec3b(0, 255, 255);//��ɫ
				//				src11.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////12.bmp
				//for (int k = 0; k < 7; k++) {
				//	for (int i = rect2[k].y; i < rect2[k].y + rect2[k].height; i++) {
				//		for (int j = rect2[k].x; j < rect2[k].x + rect2[k].width; j++) {
				//			//src12.at<Vec3b>(i, j) = Vec3b(0, 255, 0);//��ɫ
				//			src12.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				////13.bmp
				//for (int k = 0; k < 18; k++) {
				//	for (int i = rect3[k].y; i < rect3[k].y + rect3[k].height; i++) {
				//		for (int j = rect3[k].x; j < rect3[k].x + rect3[k].width; j++) {
				//			if (k % 6 == 0 || k % 6 == 1 || k % 6 == 2)
				//				//src13.at<Vec3b>(i, j) = Vec3b(39, 127, 255);//��ɫ
				//				src13.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//			else
				//				//src13.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//��ɫ
				//				src13.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//��ɫ
				//		}
				//	}
				//}
				//imshow("src00", src00);
				//imshow("src01", src01);
				//imshow("src02", src02);
				//imshow("src03", src03);
				//imshow("src00", src00);
				//imshow("src11", src01);
				//imshow("src12", src02);
				//imshow("src13", src03);
				//imwrite("00.bmp", src00);
				//imwrite("01.bmp", src01);
				//imwrite("02.bmp", src02);
				//imwrite("03.bmp", src03);
				//imwrite("10.bmp", src10);
				//imwrite("11.bmp", src11);
				//imwrite("12.bmp", src12);
				//imwrite("13.bmp", src13);
				//waitKey(0);
			}
		}

		Sleep(100);

		Mat src0;
		src0.push_back(src00);
		src0.push_back(src01);
		src0.push_back(src02);
		src0.push_back(src03);
		Mat src1;
		src1.push_back(src10);
		src1.push_back(src11);
		src1.push_back(src12);
		src1.push_back(src13);
		//imwrite("33.bmp", src0);///////////////////////
		//imwrite("44.bmp", src1);///////////////////////
		//////��ȡħ����ɫ��Ϣ
		Cube cube = GetCubeData(src0, src1);
		//////����
		cube = Cluster(cube);
		//////���ħ��״̬��Ϣ
		cout << cube.CubeData << endl;
		PrinfCube(cube);
		ofstream dout("result.txt");
		////д��ǿ
		//dout << "double light[50]={" << endl;
		//for (int i = 0; i < 50; i++)
		//{
		//	dout << (int)(scalar[i].val[0] + scalar[i].val[1] + scalar[i].val[2]) << ",";
		//}
		//dout << "};" << endl;
		//dout.close();
		//д����
		//for (int i = 0; i < 3; i++)
		//{
		//	dout << "d" << i << "=[" << endl;
		//	for (int j = 0; j < 54; j++)
		//	{
		//		dout << cube.CubeData[i][j] << ";";
		//	}
		//	dout << "];" << endl;
		//}
		//д���ĵ�
		/*dout << "s=[" << endl;
		for (int i = 48; i < 54; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				dout << cube.CubeData[j][i] << " ";
			}
			dout << ";" << endl;
		}
		dout << "];" << endl;
		dout.close();
		for (int i = 0; i < 50; i++)
		{
			rectangle(src1, rect[i], Scalar(0, 0, 0), CV_FILLED);
		}
		namedWindow("src", CV_WINDOW_NORMAL);
		imshow("src", src1);
		waitKey(0);*/
		//double end = (double)cvGetTickCount();
		//cout << "����ʱ��:" << (end - start) / cvGetTickFrequency() / 1000 << endl;////////////////////////////////////////
	}
	return 0;
}
//namedWindow("src", CV_WINDOW_NORMAL);
//createTrackbar("x", "src", &x, 380, onTrackBar);
//createTrackbar("y", "src", &y, 380, onTrackBar);
//createTrackbar("dx", "src", &dx, 380, onTrackBar);
//createTrackbar("dy", "src", &dy, 380, onTrackBar);
//void onTrackBar(int, void*)
//{
//	Mat src0;
//	src0 = imread("03.bmp");
//	rectangle(src0, Rect(x,y,dx,dy), Scalar(0,0,0), CV_FILLED);
//	imshow("src", src0);
//}
//��ʼ����Ϣ�ɼ�λ��
void RectInit(void)
{
	//���ƴ��ԭ����
	////00.bmp
	//rect0[0] = Rect(49, 29, 25, 25);
	//rect0[1] = Rect(275, 27, 25, 25);
	//rect0[2] = Rect(41, 142, 25, 25);
	//rect0[3] = Rect(160, 142, 25, 25);
	//rect0[4] = Rect(49, 246, 25, 25);
	//rect0[5] = Rect(160, 246, 25, 25);
	//rect0[6] = Rect(277, 242, 25, 25);
	////01.bmp
	//rect1[0] = Rect(55, 64, 12, 21);
	//rect1[1] = Rect(88, 57, 19, 21);
	//rect1[2] = Rect(148, 25, 25, 25);
	//rect1[3] = Rect(214, 25, 25, 25);
	//rect1[4] = Rect(271, 55, 19, 21);
	//rect1[5] = Rect(308, 64, 12, 21);
	//rect1[6] = Rect(51, 131, 12, 25);
	//rect1[7] = Rect(88, 129, 19, 25);
	//rect1[8] = Rect(144, 120, 21, 25);
	//rect1[9] = Rect(215, 125, 25, 25);
	//rect1[10] = Rect(271, 125, 20, 25);
	//rect1[11] = Rect(310, 131, 12, 25);
	//rect1[12] = Rect(53, 199, 12, 21);
	//rect1[13] = Rect(86, 207, 19, 19);
	//rect1[14] = Rect(140, 230, 25, 35);
	//rect1[15] = Rect(212, 230, 25, 35);
	//rect1[16] = Rect(267, 207, 19, 19);
	//rect1[17] = Rect(308, 199, 12, 19);
	////02.bmp
	//rect2[0] = Rect(43, 19, 25, 25);
	//rect2[1] = Rect(166, 19, 25, 25);
	//rect2[2] = Rect(290, 21, 25, 25);
	//rect2[3] = Rect(29, 138, 25, 25);
	//rect2[4] = Rect(166, 148, 21, 21);
	//rect2[5] = Rect(41, 249, 21, 21);
	//rect2[6] = Rect(294, 249, 21, 21);
	////03.bmp
	//rect3[0] = Rect(68 - 15, 70, 12, 25);
	//rect3[1] = Rect(103 - 15, 53, 16, 25);
	//rect3[2] = Rect(152 - 15, 35, 19, 25);
	//rect3[3] = Rect(212 - 15, 35, 19, 25);
	//rect3[4] = Rect(261 - 15, 51, 16, 25);
	//rect3[5] = Rect(298 - 15, 68, 12, 25);
	//rect3[6] = Rect(66 - 15, 140, 12, 25);
	//rect3[7] = Rect(101 - 15, 134, 16, 25);
	//rect3[8] = Rect(152 - 15, 125, 19, 25);
	//rect3[9] = Rect(214 - 15, 125, 19, 25);
	//rect3[10] = Rect(263 - 15, 131, 16, 25);
	//rect3[11] = Rect(302 - 15, 136, 12, 25);
	//rect3[12] = Rect(68 - 15, 210, 12, 25);
	//rect3[13] = Rect(103 - 15, 216, 16, 25);
	//rect3[14] = Rect(152 - 15, 222, 19, 25);
	//rect3[15] = Rect(214 - 15, 218, 19, 25);
	//rect3[16] = Rect(265 - 15, 212, 16, 25);
	//rect3[17] = Rect(302 - 15, 205, 12, 25);

	////2-----
	////00.bmp
	//rect0[0] = Rect(58, 131, 25, 25);//32
	//rect0[1] = Rect(163, 23, 25, 25);//34
	//rect0[2] = Rect(110, 188, 25, 25);//23
	//rect0[3] = Rect(161, 133, 25, 25);//52
	//rect0[4] = Rect(163, 243, 25, 25);//43
	//rect0[5] = Rect(216, 183, 25, 25);//15
	//rect0[6] = Rect(276, 129, 25, 25);//41
	////01.bmp

	//rect1[0] = Rect(273, 198, 12, 25);//27
	//rect1[1] = Rect(235, 212, 16, 25);//2
	//rect1[2] = Rect(176, 212, 19, 25);//24
	//rect1[3] = Rect(122, 222, 19, 25);//25
	//rect1[4] = Rect(73, 196, 16, 25);//16
	//rect1[5] = Rect(41, 192, 12, 25);//38
	//rect1[6] = Rect(274, 124, 12, 25);//4
	//rect1[7] = Rect(233, 131, 16, 25);//50
	//rect1[8] = Rect(186, 125, 19, 25);//0
	//rect1[9] = Rect(122, 125, 19, 25);//1
	//rect1[10] = Rect(71, 134, 16, 25);//48
	//rect1[11] = Rect(41, 125, 12, 25);//9
	//rect1[12] = Rect(276, 50, 12, 25);//30
	//rect1[13] = Rect(231, 51, 16, 25);//6
	//rect1[14] = Rect(182, 26, 19, 25);//33
	//rect1[15] = Rect(122, 35, 19, 25);//35
	//rect1[16] = Rect(73, 53, 16, 25);//18
	//rect1[17] = Rect(39, 53, 12, 25);//40
	////02.bmp
	//rect2[0] = Rect(162, 39, 25, 25);//47
	//rect2[1] = Rect(215, 88, 25, 25);//11
	//rect2[2] = Rect(264, 138, 21, 21);//37
	//rect2[3] = Rect(116, 90, 25, 25);//21
	//rect2[4] = Rect(170, 140, 21, 21);//49
	//rect2[5] = Rect(69, 145, 25, 25);//28
	//rect2[6] = Rect(167, 247, 21, 21);//26
	////03.bmp
	//rect3[0] = Rect(302, 197, 12, 19);//36
	//rect3[1] = Rect(262, 202, 19, 19);//10
	//rect3[2] = Rect(205, 214, 25, 35);//45
	//rect3[3] = Rect(144, 213, 25, 35);//46
	//rect3[4] = Rect(96, 199, 19, 19);//20
	//rect3[5] = Rect(59, 199, 12, 21);//29
	//rect3[6] = Rect(299, 124, 12, 25);//8
	//rect3[7] = Rect(263, 120, 20, 25);//53
	//rect3[8] = Rect(208, 116, 25, 25);//12
	//rect3[9] = Rect(148, 120, 21, 25);//13
	//rect3[10] = Rect(97, 124, 19, 25);//51
	//rect3[11] = Rect(56, 123, 12, 25);//5
	//rect3[12] = Rect(305, 46, 12, 21);//39
	//rect3[13] = Rect(261, 35, 19, 21);//14
	//rect3[14] = Rect(208, 25, 25, 25);//42
	//rect3[15] = Rect(147, 25, 25, 25);//44
	//rect3[16] = Rect(95, 38, 19, 21);//22
	//rect3[17] = Rect(59, 50, 12, 21);//31

	////3------���Գɹ���
	////00.bmp
	//rect0[0] = Rect(276, 129, 25, 25);//32
	//rect0[1] = Rect(163, 23, 25, 25);//34
	//rect0[2] = Rect(216, 183, 25, 25);//23
	//rect0[3] = Rect(161, 133, 25, 25);//52
	//rect0[4] = Rect(163, 243, 25, 25);//43
	//rect0[5] = Rect(110, 188, 25, 25);//15
	//rect0[6] = Rect(58, 131, 25, 25);//41
	////01.bmp
	//rect1[0] = Rect(41, 192, 12, 25);//27
	//rect1[1] = Rect(73, 196, 16, 25);//2
	//rect1[2] = Rect(122, 222, 19, 25);//24
	//rect1[3] = Rect(176, 212, 19, 25);//25
	//rect1[4] = Rect(235, 212, 16, 25);//16
	//rect1[5] = Rect(273, 198, 12, 25);//38
	//rect1[6] = Rect(41, 125, 12, 25);//4
	//rect1[7] = Rect(71, 134, 16, 25);//50
	//rect1[8] = Rect(122, 125, 19, 25);//0
	//rect1[9] = Rect(186, 125, 19, 25);//1
	//rect1[10] = Rect(233, 131, 16, 25);//48
	//rect1[11] = Rect(274, 124, 12, 25);//9
	//rect1[12] = Rect(39, 53, 12, 25);//30
	//rect1[13] = Rect(73, 53, 16, 25);//6
	//rect1[14] = Rect(122, 35, 19, 25);//33
	//rect1[15] = Rect(182, 26, 19, 25);//35
	//rect1[16] = Rect(231, 51, 16, 25);//18
	//rect1[17] = Rect(276, 50, 12, 25);//40
	////02.bmp
	//rect2[0] = Rect(162, 39, 25, 25);//47
	//rect2[1] = Rect(116, 90, 25, 25);//11
	//rect2[2] = Rect(69, 145, 25, 25);//37
	//rect2[3] = Rect(215, 88, 25, 25);//21
	//rect2[4] = Rect(170, 140, 21, 21);//49
	//rect2[5] = Rect(264, 138, 21, 21);//28
	//rect2[6] = Rect(167, 247, 21, 21);//26
	////03.bmp
	//rect3[0] = Rect(59, 199, 12, 21);//36
	//rect3[1] = Rect(96, 199, 19, 19);//10
	//rect3[2] = Rect(144, 213, 25, 35);//45
	//rect3[3] = Rect(205, 214, 25, 35);//46
	//rect3[4] = Rect(262, 202, 19, 19);//20
	//rect3[5] = Rect(302, 197, 12, 19);//29
	//rect3[6] = Rect(56, 123, 12, 25);//8
	//rect3[7] = Rect(97, 124, 19, 25);//53
	//rect3[8] = Rect(148, 120, 21, 25);//12
	//rect3[9] = Rect(208, 116, 25, 25);//13
	//rect3[10] = Rect(263, 120, 20, 25);//51
	//rect3[11] = Rect(299, 124, 12, 25);//5
	//rect3[12] = Rect(59, 50, 12, 21);//39
	//rect3[13] = Rect(95, 38, 19, 21);//14
	//rect3[14] = Rect(147, 25, 25, 25);//42
	//rect3[15] = Rect(208, 25, 25, 25);//44
	//rect3[16] = Rect(261, 35, 19, 21);//22
	//rect3[17] = Rect(305, 46, 12, 21);//31

	//��һ�β���ȫ�״���
	rect0[6] = Rect(50, 130, 25, 25);//41
	rect0[5] = Rect(100, 180, 25, 25);//15

	rect0[1] = Rect(154, 23, 25, 25);//34
	rect0[3] = Rect(154, 133, 25, 25);//52
	rect0[4] = Rect(154, 235, 25, 25);//43

	rect0[2] = Rect(200, 180, 25, 25);//23
	rect0[0] = Rect(255, 130, 25, 25);//32
	
	//01.bmp
	rect1[12] = Rect(55, 75, 10, 25);//30
	rect1[6]  = Rect(55, 140, 10, 25);//4
	rect1[0]  = Rect(55, 205, 10, 25);//27

	rect1[13] = Rect(95, 53, 15, 20);//6
	rect1[7]  = Rect(95, 140, 15, 25);//50
	rect1[1]  = Rect(95, 223, 15, 20);//2

	rect1[14] = Rect(140, 45, 20, 25);//33
	rect1[8]  = Rect(140, 135, 20, 25);//0
	rect1[2]  = Rect(140, 225, 20, 25);//24
	rect1[15] = Rect(205, 40, 20, 25);//35
	rect1[9]  = Rect(205, 133, 20, 25);//1
	rect1[3]  = Rect(205, 220, 20, 25);//25

	rect1[16] = Rect(255, 55, 15, 20);//18
	rect1[10] = Rect(255, 133, 15, 25);//48
	rect1[4]  = Rect(255, 212, 15, 20);//16

	rect1[17] = Rect(296, 60, 10, 25);//40
	rect1[11] = Rect(296, 135, 10, 25);//9
	rect1[5]  = Rect(296, 210, 10, 25);//38
	//02.bmp
	rect2[2] = Rect(60, 150, 25, 25);//37
	rect2[1] = Rect(110, 95, 25, 25);//11

	rect2[0] = Rect(157, 40, 25, 25);//47
	rect2[4] = Rect(160, 148, 25, 25);//49
	rect2[6] = Rect(163, 255, 25, 25);//26

	rect2[3] = Rect(208, 88, 25, 25);//21
	rect2[5] = Rect(254, 140, 25, 25);//28
	//03.bmp
	rect3[12] = Rect(60, 63, 10, 25);//39
	rect3[6] = Rect(60, 135, 10, 25);//8
	rect3[0] = Rect(60, 210, 10, 25);//36
	rect3[13] = Rect(99, 53, 15, 25);//14
	rect3[7] = Rect(99, 134, 15, 25);//53
	rect3[1] = Rect(99, 218, 15, 25);//10

	rect3[14] = Rect(146, 44, 20, 25);//42
	rect3[8] = Rect(146, 137, 20, 25);//12
	rect3[2] = Rect(146, 230, 20, 25);//45
	rect3[15] = Rect(208, 44, 20, 25);//44
	rect3[9] = Rect(208, 137, 20, 25);//13
	rect3[3] = Rect(208, 230, 20, 25);//46

	rect3[16] = Rect(264, 53, 15, 25);//22
	rect3[10] = Rect(264, 139, 15, 25);//51
	rect3[4] = Rect(264, 223, 15, 25);//20
	rect3[17] = Rect(303, 60, 10, 25);//31
	rect3[11] = Rect(303, 133, 10, 25);//5
	rect3[5] = Rect(303, 207, 10, 25);//29

	for (int i = 0; i < 7; i++)//7��
	{
		rect[i] = rect0[i];
	}
	for (int i = 7; i < 25; i++)//18��
	{
		rect[i] = rect1[i - 7];
		rect[i].y += 288;
	}
	for (int i = 25; i < 32; i++)//7��
	{
		rect[i] = rect2[i - 25];
		rect[i].y += 288 * 2;
	}
	for (int i = 32; i < 50; i++)//18��
	{
		rect[i] = rect3[i - 32];
		rect[i].y += 288 * 3;
	}
}
//intתstring,�޶�λ������
string my_i2s(int i)
{
	string str = "00";
	str[0] = i / 10 + 0x30;
	str[1] = i % 10 + 0x30;
	return str;
}
//��ȡħ��״̬��Ϣ
Cube GetCubeData(Mat src0, Mat src1)
{
	////������ת����
	double cB1 = cos(B1*3.141592654 / 180.0);
	double cB2 = cos(B2*3.141592654 / 180.0);
	double sB1 = sin(B1*3.141592654 / 180.0);
	double sB2 = sin(B2*3.141592654 / 180.0);
	double Rx[3][3] = {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, cB1, -sB1 },
		{ 0.0, sB1, cB1 }
	};
	double Ry[3][3] = {
		{ cB2, 0.0, sB2 },
		{ 0.0, 1.0, 0.0 },
		{ -sB2, 0.0, cB2 }
	};
	//�ɼ�����src0
	int data0[3][50];
	for (int i = 0; i < 50; i++)
	{
		Mat ROI = src0(rect[i]);////����ROI���� ��ROI�����д���ͼƬѡ����������ص���ɫ����
		scalar[i] = mean(ROI);////ͨ��mean������ȡROI��ͨ������ɫ��ɫ��Ϣ

		double X = scalar[i].val[0] / LightScale[i];////��ͨ����Ϣ�ӳɹ�����Ϣ
		double Y = scalar[i].val[1] / LightScale[i];////��ͨ����Ϣ�ӳɹ�����Ϣ
		double Z = scalar[i].val[2] / LightScale[i];////��ͨ����Ϣ�ӳɹ�����Ϣ
		//cout << X << endl;
		//======================================================================����任
		//x����ת
		double temp1 = Rx[0][0] * X + Rx[0][1] * Y + Rx[0][2] * Z;
		double temp2 = Rx[1][0] * X + Rx[1][1] * Y + Rx[1][2] * Z;
		double temp3 = Rx[2][0] * X + Rx[2][1] * Y + Rx[2][2] * Z;
		//y����ת
		data0[0][i] = (int)(Ry[0][0] * temp1 + Ry[0][1] * temp2 + Ry[0][2] * temp3);
		data0[1][i] = (int)(Ry[1][0] * temp1 + Ry[1][1] * temp2 + Ry[1][2] * temp3);
		data0[2][i] = (int)(Ry[2][0] * temp1 + Ry[2][1] * temp2 + Ry[2][2] * temp3);
		//z��ѹ��
		data0[2][i] /= 2;
	}
	//�ɼ�����src1
	int data1[3][50];
	for (int i = 0; i < 50; i++)
	{
		Mat ROI = src1(rect[i]);
		scalar[i] = mean(ROI);

		double X = scalar[i].val[0] / LightScale[i];
		double Y = scalar[i].val[1] / LightScale[i];
		double Z = scalar[i].val[2] / LightScale[i];
		//======================================================================����任
		//x����ת
		double temp1 = Rx[0][0] * X + Rx[0][1] * Y + Rx[0][2] * Z;
		double temp2 = Rx[1][0] * X + Rx[1][1] * Y + Rx[1][2] * Z;
		double temp3 = Rx[2][0] * X + Rx[2][1] * Y + Rx[2][2] * Z;
		//y����ת
		data1[0][i] = (int)(Ry[0][0] * temp1 + Ry[0][1] * temp2 + Ry[0][2] * temp3);
		data1[1][i] = (int)(Ry[1][0] * temp1 + Ry[1][1] * temp2 + Ry[1][2] * temp3);
		data1[2][i] = (int)(Ry[2][0] * temp1 + Ry[2][1] * temp2 + Ry[2][2] * temp3);
		//z��ѹ��
		data1[2][i] /= 2;
	}
	//����ӳ��
	int map0[50] = { 32,34,23,52,43,15,41,27,2,24,25,16,38,4,50,0,1,48,9,30,6,33,35,18,40,47,11,37,21,49,28,26,36,10,45,46,20,29,8,53,12,13,51,5,39,14,42,44,22,31 };
	int map1[50] = { 27,24,4,50,30,6,33,47,11,37,38,9,40,21,49,17,16,48,18,28,3,26,25,1,35,42,14,39,12,53,45,36,41,15,43,44,13,46,19,52,23,22,51,20,34,7,32,31,5,29 };
	//int map0[50] = {
	//	34,41,7,52,32,23,43,
	//	25,16,38,36,10,45,1,48,9,8,53,12,35,18,40,39,14,42,
	//	28,21,47,3,49,26,37,
	//	46,20,29,27,2,24,13,51,5,4,50,0,44,22,31,30,6,33
	//};	
	//int map1[50] = { 
	//	24,33,2,50,27,4,30,
	//	38,9,40,41,15,43,16,48,18,19,52,23,25,1,35,34,7,32,
	//	45,12,42,10,53,36,39,
	//	44,13,40,47,11,37,22,51,20,21,49,17,31,5,29,28,3,26
	//};

	
	//cube ��ʼ��
	Cube cube;
	for (int i = 0; i < 54; i++)
	{
		cube.GetValueFlag[i] = 0;
		cube.Idx[i] = -1;
		cube.CubeData[0][i] = 0;
		cube.CubeData[1][i] = 0;
		cube.CubeData[2][i] = 0;
	}
	//cube��ֵ
	for (int i = 0; i < 50; i++)
	{
		cube.GetValueFlag[map0[i]]++;
		for (int j = 0; j < 3; j++)
		{
			cube.CubeData[j][map0[i]] = (cube.CubeData[j][map0[i]] * (cube.GetValueFlag[map0[i]] - 1) + data0[j][i]) / cube.GetValueFlag[map0[i]];
		}
	}
	for (int i = 0; i < 50; i++)
	{
		cube.GetValueFlag[map1[i]]++;
		for (int j = 0; j < 3; j++)
		{
			cube.CubeData[j][map1[i]] = (cube.CubeData[j][map1[i]] * (cube.GetValueFlag[map1[i]] - 1) + data1[j][i]) / cube.GetValueFlag[map1[i]];
		}
	}
	return cube;
}

//@breaf���ж�һ��ħ���Ƿ�ɽ�
/*
#define F  0
#define R  1
#define U  2
#define B  3
#define L  4
#define D  5
*/
//�����ʽ��UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR F R U B L D
bool CubeCanSolve(Cube cube)
{
	//1,�ж����Ŀ��Ƿ�����ظ�
	if ((cube.Idx[48 + F] != F) || (cube.Idx[48 + R] != R) || (cube.Idx[48 + U] != U) || (cube.Idx[48 + B] != B) || (cube.Idx[48 + L] != L) || (cube.Idx[48 + D] != D))
	{
		return false;
	}
	//2,�ж�ÿ���߿��������ɫ�Ƿ���ͬ
	for (int i = 0; i < 12; i++)
	{
		int start = i * 2;
		if (cube.Idx[start] % 3 == cube.Idx[start + 1] % 3) return false;
	}
	//3,�ж�ÿ���ǿ��������ɫ�Ƿ���ͬ
	for (int i = 0; i < 8; i++)
	{
		int start = 24 + i * 3;
		if ((cube.Idx[start] % 3 == cube.Idx[start + 1] % 3) || (cube.Idx[start] % 3 == cube.Idx[start + 2] % 3) || (cube.Idx[start + 1] % 3 == cube.Idx[start + 2] % 3))return false;
	}
	//4,�жϱ߿�ɫ���Ƿ���ȷ
	int ColorSum = 0;
	for (int i = 0; i < 12; i++)
	{
		int start = i * 2;
		int map[3] = { 1, 0, 2 };

		if (map[cube.Idx[start] % 3] < map[cube.Idx[start + 1] % 3])ColorSum++;
	}
	if (ColorSum % 2 != 0)return false;
	//5,�жϽǿ�ɫ���Ƿ���ȷ
	ColorSum = 0;
	for (int i = 0; i < 8; i++)
	{
		int start = 24 + i * 3;
		if
			(cube.Idx[start] % 3 == 2)ColorSum += 0;
		else if
			(cube.Idx[start + 1] % 3 == 2)ColorSum += 1;
		else if
			(cube.Idx[start + 2] % 3 == 2)ColorSum += 2;
	}
	if (ColorSum % 3 != 0)return false;
	//6���ж�ɫƬλ��
	//��Ǹд������������
	return true;
}
//�ж�ħ����Idx�Ƿ�Ϊ6��9
bool CubeIdxIs6_9(Cube cube)
{
	int count[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 54; i++)
	{
		count[cube.Idx[i]]++;
	}
	for (int i = 0; i < 6; i++)
	{
		if (count[i] != 9)
		{
			return false;
		}
	}
	return true;
}
//���ħ��״̬
void PrinfCube(Cube cube)
{
	ofstream dout(".\\Bridge\\cubeIdxData.txt");/////////////////////////////////////////////
	//ofstream dout(".\\CubeIdxData.txt");
	for (int i = 0; i < 48; i++)
	{
		dout << str[cube.Idx[i]];
	}
	dout.close();

	ofstream eout(".\\Bridge\\CubeIdxDataFlag.txt");///////////////////////////////////////////
	//ofstream eout(".\\CubeIdxDataFlag.txt");
	eout.close();

}
//kmean����
Cube KmeanCluster(Cube cube)
{
	//��ʼ������
	for (int i = 0; i < 54; i++)
	{
		cube.Idx[i] = -1;
	}
	for (int i = 0; i < 6; i++)
	{
		cube.Idx[48 + i] = i;
	}
	//��ʼ����������
	int Center[3][6];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Center[j][i] = cube.CubeData[j][48 + i];
		}
	}
	while (true)
	{
		//������ǰ����
		int preIdx[54];
		for (int i = 0; i < 54; i++)
		{
			preIdx[i] = cube.Idx[i];
		}
		//��48��ɫ�����
		for (int i = 0; i < 48; i++)
		{
			double minDis = 1e8;
			int idx = -1;
			for (int c = 0; c < 6; c++)
			{
				double Dis =
					(cube.CubeData[0][i] - Center[0][c])*(cube.CubeData[0][i] - Center[0][c]) +
					(cube.CubeData[1][i] - Center[1][c])*(cube.CubeData[1][i] - Center[1][c]) +
					(cube.CubeData[2][i] - Center[2][c])*(cube.CubeData[2][i] - Center[2][c]);
				if (Dis < minDis)
				{
					minDis = Dis;
					idx = c;
				}
			}
			cube.Idx[i] = idx;
		}
		//д����
		ofstream dout("result.txt");

		for (int j = 0; j < 54; j++)
		{
			dout << cube.Idx[j] << ";";
		}
		dout << "];" << endl;
		dout.close();
		//����Idx�Ƿ�ı�
		bool IdxIsChanged = false;
		for (int i = 0; i < 54; i++)
		{
			if (preIdx[i] != cube.Idx[i])IdxIsChanged = true;  //һ�����κ�һ��������֮ǰ��ͬ�����������ı�
		}
		if (IdxIsChanged == false)   //�������Ѿ��ȶ�
		{
			return cube;
		}
		//���·����������
		int count[6] = { 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < 54; i++)
		{
			int Class = cube.Idx[i];   //��ȡ���ɫƬΪ��һ��
			if (Class != -1)
			{
				count[Class]++;
				for (int j = 0; j < 3; j++)
				{
					Center[j][Class] = (Center[j][Class] * (count[Class] - 1) + cube.CubeData[j][i]) / count[Class];
				}
			}
		}
	}
	return cube;
}
//����ƽ��
Cube CutOverNum(Cube cube)
{
	//��ʼ����������
	int Center[3][6];
	int count1[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 54; i++)
	{
		int Class = cube.Idx[i];   //��ȡ���ɫƬΪ��һ��
		count1[Class]++;
		for (int j = 0; j < 3; j++)
		{
			Center[j][Class] = (Center[j][Class] * (count1[Class] - 1) + cube.CubeData[j][i]) / count1[Class];
		}
	}
	//����ÿ������������ĵľ���
	int Dis[54];
	for (int i = 0; i < 54; i++)
	{
		Dis[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			Dis[i] += (cube.CubeData[j][i] - Center[j][cube.Idx[i]])*(cube.CubeData[j][i] - Center[j][cube.Idx[i]]);
		}
	}
	//���ÿ���㣬�����������������ĵľ�������
	int Level[54];
	for (int i = 0; i < 54; i++)
	{
		Level[i] = 0;
		for (int j = 0; j < 54; j++)//��������������бȽ�
		{
			if (cube.Idx[i] == cube.Idx[j])//��������Ϊͬһ��
			{
				if (Dis[i] < Dis[j])
				{
					Level[i]++;  //��¼���Լ�������м���,��0������˵���Լ����
				}
			}
		}
	}
	//ȡ���������ڵ���9�ĵ����ķ���
	for (int i = 0; i < 54; i++)
	{
		if (Level[i] >= 9)
		{
			cube.Idx[i] = -1;
		}
	}
	//����ȷ����������
	int count2[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 54; i++)
	{
		int Class = cube.Idx[i];   //��ȡ���ɫƬΪ��һ��
		if (Class != -1)
		{
			count2[Class]++;
			for (int j = 0; j < 3; j++)
			{
				Center[j][Class] = (Center[j][Class] * (count2[Class] - 1) + cube.CubeData[j][i]) / count2[Class];
			}
		}
	}
	//�Ա�ȡ������ĵ�������·���
	for (int i = 0; i < 54; i++)
	{
		if (cube.Idx[i] == -1)  //ȡ���˷���ĵ�
		{
			int minDis = 1000000;
			int c = -1;
			for (int j = 0; j < 6; j++)
			{
				if (count2[j] < 9)
				{
					int dis = 0;
					for (int k = 0; k < 3; k++)
					{
						dis += (cube.CubeData[k][i] - Center[k][j])*(cube.CubeData[k][i] - Center[k][j]);
					}
					if (dis < minDis)
					{
						minDis = dis;
						c = j;
					}
				}
			}
			cube.Idx[i] = c;
			count2[c]++;
		}
	}
	return cube;
}
//���ĵ���ռ
Cube CenterGrab(Cube cube, bool CenterMove)
{
	//���Idx
	for (int i = 0; i < 54; i++)
	{
		cube.Idx[i] = -1;
	}
	//��ʼ����������
	int Center[3][6];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Center[j][i] = cube.CubeData[j][48 + i];
		}
	}
	//�����ռ9����
	for (int i = 0; i < 9; i++)
	{
		//ÿһ����ռһ����
		for (int c = 0; c < 6; c++)
		{
			int minDis = 1000000;
			int p = -1;
			for (int j = 0; j < 54; j++)
			{
				if (cube.Idx[j] == -1)  //������δ����ĵ�
				{
					int dis = 0;
					for (int k = 0; k < 3; k++)
					{
						dis += (cube.CubeData[k][j] - Center[k][c])*(cube.CubeData[k][j] - Center[k][c]);
					}
					if (dis < minDis)
					{
						minDis = dis;
						p = j;
					}
				}
			}
			cube.Idx[p] = c;
		}
		//���µ�����������
		if (CenterMove)
		{
			int count[6] = { 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 54; i++)
			{
				int Class = cube.Idx[i];   //��ȡ���ɫƬΪ��һ��
				if (Class != -1)
				{
					count[Class]++;
					for (int j = 0; j < 3; j++)
					{
						Center[j][Class] = (Center[j][Class] * (count[Class] - 1) + cube.CubeData[j][i]) / count[Class];
					}
				}
			}
		}
	}
	return cube;
}
Cube Cluster(Cube cube)
{
	/*
	����˼·��
	1��������һ��kmean���жϸ���Ԫ����Ŀ�Ƿ�Ϊ6��9���������˳���
	2�������ǣ�Ȼ�����������ƽ�㷨����ƽΪ9����                   //ע�⣬����Ĩȥʱ�����µ����������ġ�
	3���ж��Ƿ�ɽ⣬�ɽ����˳���
	4���������ĵ���ռ�㷨���ж��Ƿ�ɽ⣬�ɽ����˳���              //ע�⣬ÿ����ռ����Ҫ�������ĵ㡣
	5�����ò��������ĵ��������ռ�㷨���ɽ����˳���                //ע�⣬ÿ����ռ���������ĵ㡣
	6�������ɽ⣬���ظ�ԭħ�����ݡ�
	*/
	//��ʼ��Idx
	for (int i = 0; i < 54; i++)
	{
		cube.Idx[i] = -1;
	}
	//ʹ�ö�̬�����������ĵ����ĵ���ռ�㷨
	cout << "ʹ�ö�̬�����������ĵ����ĵ���ռ�㷨" << endl;
	cube = CenterGrab(cube, CENTER_MOVE);
	if (CubeCanSolve(cube))
	{
		cout << "��̬�����������ĵ����ĵ���ռ�㷨�ɽ�" << endl;
		return cube;
	}
	else
	{
		cout << "ʹ�ö�̬�����������ĵ����ĵ���ռ�㷨���ɽ�" << endl;
	}
	//ʹ�����ĵ���ռ�㷨
	cout << "ʹ�����ĵ���ռ�㷨" << endl;
	cube = CenterGrab(cube, CENTER_NO_MOVE);
	if (CubeCanSolve(cube))
	{
		cout << "���ĵ���ռ�㷨�ɽ�" << endl;
		return cube;
	}
	else
	{
		cout << "ʹ�����ĵ���ռ�㷨���ɽ�" << endl;
	}
	//kmean����
	cout << "ʹ��kmean����" << endl;
	cube = KmeanCluster(cube);
	//�жϸ�Ԫ�����Ƿ�Ϊ6��9
	if (CubeIdxIs6_9(cube))
	{
		if (CubeCanSolve(cube))
		{
			cout << "kmean�������ɽ�" << endl;
			return cube;
		}
		else
		{
			cout << "kmean������ɽ�" << endl;
		}
	}
	//ʹ������ƽ���㷨
	else
	{
		cout << "kmeanδ��ȷ���࣬ʹ������ƽ��" << endl;
		cube = CutOverNum(cube);
		if (CubeCanSolve(cube))
		{
			cout << "����ƽ�ƾ������ɽ�" << endl;
			return cube;
		}
		else
		{
			cout << "����ƽ�ƽ�����ɽ�" << endl;
		}
	}
	return cube;
}
bool IsPictureCaped(void)
{
	char FileName[] = ".\\Bridge\\CluserStartFlag.txt";

	std::fstream _file;
	_file.open(FileName, ios::in);
	if (!_file)
	{
		return false;  //������
	}
	else
	{
		_file.close();
		Sleep(20);
		remove(FileName);
		return true;
	}
}