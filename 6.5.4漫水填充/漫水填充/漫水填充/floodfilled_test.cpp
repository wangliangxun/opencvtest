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
	imshow("效果图",dst);
	cout<<area<<" 个像素被重绘\n";
}

int main(int argc,char**argv)
{
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("读取jpg图片错误!\n");return false;
	}
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage,g_dstImage,COLOR_BGR2GRAY);//转换三通道图到灰度图
	g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);//初始化掩膜mask
	namedWindow("效果图",CV_WINDOW_AUTOSIZE);

	createTrackbar("负差最大值","效果图",&g_nLowDifference,255,0);
	createTrackbar("正差最大值","效果图",&g_nLowDifference,255,0);

	setMouseCallback("效果图",onMouse,0);
	
	while (1)
	{
		imshow("效果图",g_bIsColar?g_dstImage:g_grayImage);
		int c=waitKey(0);
		if ((c&255)==27)
		{
			cout<<"程序退出…………\n";
			break;
		}
		switch((char)c)
		{
			case '1':
				if (g_bIsColar)
				{
					cout<<"按键‘1’被按下，切换彩色/灰度模式，当前操作将[彩色模式]切换为【灰度模式】\n";
					cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
					g_maskImage=Scalar::all(0);
					g_bIsColar=false;
				} 
				else
				{
					cout<<"按键‘1’被按下，切换彩色/灰度模式，当前操作将[灰度模式]切换为【彩色模式】\n";
					g_srcImage.copyTo(g_dstImage);
					g_maskImage=Scalar::all(0);
					g_bIsColar=true;
				}
				break;
			case '2':
				if (g_bUseMask)
				{
					cout<<"按键‘2’被按下，destroy掩膜\n";
					destroyWindow("mask");
					g_bUseMask=false;
				} 
				else
				{
					cout<<"按键‘2’被按下，newcreate掩膜\n";
					namedWindow("mask",0);
					g_maskImage=Scalar::all(0);
					imshow("mask",g_maskImage);
					g_bUseMask=true;
				}
			case '3':
				cout<<"按键‘3’被按下，恢复原始图像\n";
				g_srcImage.copyTo(g_dstImage);
				cvtColor(g_dstImage,g_grayImage,COLOR_BGR2GRAY);
				g_maskImage=Scalar::all(0);
				break;
			case '4':
				cout<<"按键‘4’被按下，使用孔范围的漫水填充\n";
				g_nFillMode=0;
				break;
			case '5':
				cout<<"按键‘5’被按下，使用渐变、固定范围的漫水填充";
				g_nFillMode=1;
				break;
			case '6':
				cout<<"按键‘6’被按下，使用渐变、浮动范围的漫水填充";
				g_nFillMode=2;
				break;
			case '7':
				cout<<"按键‘7’被按下，操作标志符的低8位使用4位的连续模式\n";
				g_nFillMode=4;
				break;
			case '8':
				cout<<"按键‘8’被按下，操作标志符的低8位使用8位的连续模式\n";
				g_nFillMode=8;
				break;
		}
	}
}



