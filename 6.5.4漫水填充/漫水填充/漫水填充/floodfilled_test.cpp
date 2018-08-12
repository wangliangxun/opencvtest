#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage,g_dstImage,g_grayImage,g_maskImage;
int g_nFillMode=1; 
int g_nLowDifference=20,g_nUpDifference=20;
int g_nConnectivity=4;
int g_bIsColar=true;
bool g_bUseMask=false;
int g_nNewMaskVal=255;

static void onMouse(int event,int x,int y,int,void*)
{
	if(event!=CV_EVENT_LBUTTONDBLCLK)return;
	Point seed=Point(x,y);
	int LowDifference=g_nFillMode==0?0:g_nLowDifference;
	int UpDifference=g_nFillMode==0?0:g_nUpDifference;

	int flags=g_nConnectivity+(g_nNewMaskVal<<8)+(g_nFillMode==1?CV_FLOODFILL_FIXED_RANGE:0);
	
	int b=(unsigned)theRNG()&255;
	int g=(unsigned)theRNG()&255;
	int r=(unsigned)theRNG()&255;
	Rect ccomp;

	Scalar newVal=g_bIsColar?Scalar(b,g,r):Scalar(r*0.299+g*0.587+b*0.114);
	Mat dst=g_bIsColar?g_dstImage:g_grayImage;
	int area;
	if (g_bUseMask)
	{
		threshold(g_maskImage,g_maskImage,1,128,CV_THRESH_BINARY);
		area=floodFill(dst,
			g_maskImage,
			seed,
			newVal,
			&ccomp,
			Scalar(LowDifference,LowDifference,LowDifference),
			Scalar(UpDifference,UpDifference,UpDifference),
			flags);
		imshow("mask",g_maskImage);
	} 
	else
	{
		area=floodFill(dst,
			seed,
			newVal,
			&ccomp,
			Scalar(LowDifference,LowDifference,LowDifference),
			Scalar(UpDifference,UpDifference,UpDifference),
			flags);
	}
	imshow("Ч��ͼ",dst);
	cout<<area<<" �����ر��ػ�\n";
}

int main(int argc,char**argv)
{
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("��ȡjpgͼƬ����!\n");return false;
	}
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage,g_dstImage,COLOR_BGR2GRAY);//ת����ͨ��ͼ���Ҷ�ͼ
	g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);//��ʼ����Ĥmask
	namedWindow("Ч��ͼ",CV_WINDOW_AUTOSIZE);

	createTrackbar("�������ֵ","Ч��ͼ",&g_nLowDifference,255,0);
	createTrackbar("�������ֵ","Ч��ͼ",&g_nLowDifference,255,0);

	setMouseCallback("Ч��ͼ",onMouse,0);
	
	while (1)
	{
		imshow("Ч��ͼ",g_bIsColar?g_dstImage:g_grayImage);
		int c=waitKey(0);
		if ((c&255)==27)
		{
			cout<<"�����˳���������\n";
			break;
		}
		switch((char)c)
		{
			case '1':
				if (g_bIsColar)
				{
					cout<<"������1�������£��л���ɫ/�Ҷ�ģʽ����ǰ������[��ɫģʽ]�л�Ϊ���Ҷ�ģʽ��\n";
					cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
					g_maskImage=Scalar::all(0);
					g_bIsColar=false;
				} 
				else
				{
					cout<<"������1�������£��л���ɫ/�Ҷ�ģʽ����ǰ������[�Ҷ�ģʽ]�л�Ϊ����ɫģʽ��\n";
					g_srcImage.copyTo(g_dstImage);
					g_maskImage=Scalar::all(0);
					g_bIsColar=true;
				}
				break;
			case '2':
				if (g_bUseMask)
				{
					cout<<"������2�������£�destroy��Ĥ\n";
					destroyWindow("mask");
					g_bUseMask=false;
				} 
				else
				{
					cout<<"������2�������£�newcreate��Ĥ\n";
					namedWindow("mask",0);
					g_maskImage=Scalar::all(0);
					imshow("mask",g_maskImage);
					g_bUseMask=true;
				}
			case '3':
				cout<<"������3�������£��ָ�ԭʼͼ��\n";
				g_srcImage.copyTo(g_dstImage);
				cvtColor(g_dstImage,g_grayImage,COLOR_BGR2GRAY);
				g_maskImage=Scalar::all(0);
				break;
			case '4':
				cout<<"������4�������£�ʹ�ÿ׷�Χ����ˮ���\n";
				g_nFillMode=0;
				break;
			case '5':
				cout<<"������5�������£�ʹ�ý��䡢�̶���Χ����ˮ���";
				g_nFillMode=1;
				break;
			case '6':
				cout<<"������6�������£�ʹ�ý��䡢������Χ����ˮ���";
				g_nFillMode=2;
				break;
			case '7':
				cout<<"������7�������£�������־���ĵ�8λʹ��4λ������ģʽ\n";
				g_nFillMode=4;
				break;
			case '8':
				cout<<"������8�������£�������־���ĵ�8λʹ��8λ������ģʽ\n";
				g_nFillMode=8;
				break;
		}
	}
}



