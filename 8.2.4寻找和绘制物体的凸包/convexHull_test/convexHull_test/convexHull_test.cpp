#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始窗口1】"
#define WINDOW_NAME2 "【原始窗口2】"

Mat g_srcImage;Mat g_grayImage;
int g_nThresh=50;
int g_maxThresh=255;
RNG g_rng(12345);
Mat srcImage_copy=g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

static void ShowHelpText();
void on_ThreshChange(int,void*);

int main()
{
	g_srcImage=imread("1.jpg",1);
	//imshow("1",g_srcImage);
	cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
	//imshow("2",g_grayImage);
	blur(g_grayImage,g_grayImage,Size(3,3));
	//imshow("3",g_grayImage);

	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1,g_srcImage);

	createTrackbar("阈值：",WINDOW_NAME1,&g_nThresh,g_maxThresh,on_ThreshChange);
	on_ThreshChange(0,0);
	ShowHelpText();
	waitKey(0);
	return(0);
}

void on_ThreshChange(int,void*)
{
	threshold(g_grayImage,g_thresholdImage_output,g_nThresh,255,THRESH_BINARY);
	findContours(g_thresholdImage_output,g_vContours,g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	vector<vector<Point>>hull(g_vContours.size());
	for (unsigned int i=0;i<g_vContours.size();i++)
	{
		convexHull(Mat(g_vContours[i]),hull[i],false,true);
	}
	Mat drawing=Mat::zeros(g_thresholdImage_output.size(),CV_8UC3);
	for (unsigned int i=0;i<g_vContours.size();i++)
	{
		Scalar color=Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));
		//Scalar color=Scalar(255,255,255);
		drawContours(drawing,g_vContours,i,color,1,8,vector<Vec4i>(),0,Point());
		drawContours(drawing,hull,i,color,1,8,vector<Vec4i>(),0,Point());

	}
	imshow(WINDOW_NAME2,drawing);
}

static void ShowHelpText()
{
	printf("\n\n\t按键操作说明：\n\n");
	printf("\t\t任意键→退出程序\n\n");
	printf("\t\t滚动条→改变阈值\n\n");

}











