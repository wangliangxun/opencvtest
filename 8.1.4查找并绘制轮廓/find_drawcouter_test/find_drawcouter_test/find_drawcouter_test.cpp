#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始窗口】"
#define WINDOW_NAME2 "【轮廓图】"

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh=80;
int g_nThresh_max=255;
RNG g_rng(12345);
Mat g_cannyMat_output;
//Mat g_vContours;
//vector<vector<Point>> g_vHierarchy;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

static void ShowHelpText();
void on_ThreshChange(int,void*);

int main(int argc,char **argv)
{
	system("color 1F");
	ShowHelpText();
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("read error!");
		return false;

	}
	cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
	//imshow("blur_before",g_grayImage);
	blur(g_grayImage,g_grayImage,Size(3,3));
	//imshow("blur_after",g_grayImage);
	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1,g_srcImage);

	createTrackbar("canny_Thre_val",WINDOW_NAME1,&g_nThresh,g_nThresh_max,on_ThreshChange);
	on_ThreshChange(0,0);
	waitKey(0);
	return(0);

}

void on_ThreshChange(int,void*)
{
	Canny(g_grayImage,g_cannyMat_output,g_nThresh,g_nThresh*3,3);
	//imshow("canny edge",g_cannyMat_output);
	findContours(g_cannyMat_output,g_vContours,g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
	Mat drawing =Mat::zeros(g_cannyMat_output.size(),CV_8UC3);

	for (int i=0; i < g_vContours.size();i++)
	{
		Scalar color =Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));
		drawContours(drawing,g_vContours,i,color,1,8,g_vHierarchy,0,Point());
		imshow(WINDOW_NAME2,drawing);
	}
}

static void ShowHelpText()
{
	printf("\n\n\t按键操作说明：\n\n");
	printf("\t\t任意键→退出程序\n\n");
	printf("\t\t滚动条→改变阈值\n\n");
}



































