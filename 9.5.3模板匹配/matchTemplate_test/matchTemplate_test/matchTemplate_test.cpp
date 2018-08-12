#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

#define WINDOW_NAME1 "【原始图片】"
#define WINDOW_NAME2 "【效果窗口】"

Mat g_srcImage,g_templateImage,g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum=5;

void on_Matching(int,void*);

int main()
{
	g_srcImage=imread("1.jpg",1);
	//imshow("g_srcImage",g_srcImage);
	g_templateImage=imread("2.jpg",1);
	//imshow("g_templateImage",g_templateImage);
	namedWindow(WINDOW_NAME1,CV_WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2,CV_WINDOW_AUTOSIZE);
	createTrackbar("方法",WINDOW_NAME1,&g_nMatchMethod,g_nMaxTrackbarNum,on_Matching);
	on_Matching(0,0);
	waitKey();
	return 0;

}

void on_Matching(int,void*)
{
	Mat srcImage;
	g_srcImage.copyTo(srcImage);
	int resultImage_rows=g_srcImage.rows-g_templateImage.rows+1;
	int resultImage_cols=g_srcImage.cols-g_templateImage.cols+1;
	g_resultImage.create(resultImage_rows,resultImage_cols,CV_32FC1);
	matchTemplate(g_srcImage,g_templateImage,g_resultImage,g_nMatchMethod);
	normalize(g_resultImage,g_resultImage,0,1,NORM_MINMAX,-1,Mat());
	double minValue,maxValue;
	Point minLocation,maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage,&minValue,&maxValue,&minLocation,&maxLocation,Mat());
	if (g_nMatchMethod==CV_TM_SQDIFF||g_nMatchMethod==CV_TM_SQDIFF_NORMED)
	{
		matchLocation=minLocation;
	} 
	else
	{
		matchLocation=maxLocation;
	}
	rectangle(srcImage,matchLocation,Point(matchLocation.x+g_templateImage.cols,matchLocation.y+g_templateImage.rows),
		Scalar(0,0,255),2,8,0);
	rectangle(g_resultImage,matchLocation,Point(matchLocation.x+g_templateImage.cols,matchLocation.y+g_templateImage.rows),
		Scalar(0,0,255),2,8,0);
	imshow(WINDOW_NAME1,srcImage);
	imshow(WINDOW_NAME2,g_resultImage);

}









