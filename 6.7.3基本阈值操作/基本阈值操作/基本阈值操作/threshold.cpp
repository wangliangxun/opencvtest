#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "【程序窗口】"

int g_nThresholdValue=100;
int g_nThresholdType=3;
Mat g_srcImage,g_grayImage,g_dstImage;

static void ShowHelpText();
void on_Threshold(int,void*);

int main()
{
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("读取错误");return false;
	}
	cvtColor(g_srcImage,g_grayImage,COLOR_RGB2GRAY);

	namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
	createTrackbar("模式",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
	createTrackbar("参数值",WINDOW_NAME,&g_nThresholdValue,255,on_Threshold);

	on_Threshold(0,0);
	while (1)
	{
		int key;
		key=waitKey(20);
		if ((char)key==27)
		{
			break;
		}
	}
}

void on_Threshold(int,void*)
{
	threshold(g_grayImage,g_dstImage,g_nThresholdValue,255,g_nThresholdType);
	imshow(WINDOW_NAME,g_dstImage);
}




