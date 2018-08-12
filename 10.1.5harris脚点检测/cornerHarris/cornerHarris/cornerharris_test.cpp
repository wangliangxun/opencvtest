#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "【程序窗口1】"
#define WINDOW_NAME2 "【程序窗口2】"
Mat g_srcImage,g_srcImage1,g_grayImage;
int thresh=30;
int max_thresh=175;
void on_CornerHarris(int,void*);
int main()
{
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data){printf(">>>error read!");}
	imshow("原始图",g_srcImage);
	g_srcImage1=g_srcImage.clone();
	cvtColor(g_srcImage1,g_grayImage,COLOR_BGR2GRAY);
	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	createTrackbar("阈值",WINDOW_NAME1,&thresh,max_thresh,on_CornerHarris);
	on_CornerHarris(0,0);
	waitKey();
	return 0;
}
void on_CornerHarris(int,void*)
{
	Mat dstImage,normImage,scaleImage;
	dstImage=Mat::zeros(g_srcImage.size(),CV_32FC1);
	g_srcImage1=g_srcImage.clone();
	cornerHarris(g_grayImage,dstImage,2,3,0.04,BORDER_DEFAULT);
	//imshow("dstImage",dstImage);
	//cout<<dstImage<<endl;
	normalize(dstImage,normImage,0,255,NORM_MINMAX,CV_32FC1,Mat());
	//imshow("normImage",normImage);
	convertScaleAbs(normImage,scaleImage);
	//imshow("scaleImage",scaleImage);
	for (int j=0;j<normImage.rows;j++)
	{
		for (int i=0;i<normImage.cols;i++)
		{
			if ((int)normImage.at<float>(j,i)>thresh+80)
			{
				circle(g_srcImage1,Point(i,j),5,Scalar(10,10,255),2,8,0);
				circle(scaleImage,Point(i,j),5,Scalar(0,10,255),2,8,0);
			}
			
		}
	}
	imshow(WINDOW_NAME1,g_srcImage1);
	imshow(WINDOW_NAME2,scaleImage);


}
