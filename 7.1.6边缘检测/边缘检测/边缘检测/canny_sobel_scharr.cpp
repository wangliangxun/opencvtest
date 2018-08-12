#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define WINDOW_N_S "【原始图】"
#define WINDOW_N_R_CA "【效果图-canny】"
#define WINDOW_N_R_SO "【效果图-sobel】"
#define WINDOW_N_R_SC "【效果图-scharr】"
#define WINDOW_PARA "参数值："

Mat g_srcImage,g_srcGrayImage,g_dstImage;

Mat g_cannyDetecctedEdges;
int g_cannyLowThreshold=1;

Mat g_sobelGradient_X,g_sobelGradient_Y;
Mat g_sobelAbsGradient_X,g_sobelAbsGradient_Y;
int g_sobelKernelSize=1;

Mat g_scharrGradient_X,g_scharrGradient_Y;
Mat g_scharrAbsGradient_X,g_scharrAbsGradient_Y;

static void on_Canny(int,void*);
static void on_Sobel(int,void*);
static void on_Scharr();

int main()
{
	system("color 2F");
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("Error OF Reading Jpg\n");return false;
	}
	namedWindow(WINDOW_N_S);
	imshow(WINDOW_N_S,g_srcImage);
	g_dstImage.create(g_srcImage.size(),g_srcImage.type());

	cvtColor(g_srcImage,g_srcGrayImage,COLOR_RGB2GRAY);

	namedWindow(WINDOW_N_R_CA,WINDOW_AUTOSIZE);
	namedWindow(WINDOW_N_R_SO,WINDOW_AUTOSIZE);

	createTrackbar(WINDOW_PARA,WINDOW_N_R_CA,&g_cannyLowThreshold,120,on_Canny);
	createTrackbar(WINDOW_PARA,WINDOW_N_R_SO,&g_sobelKernelSize,3,on_Sobel);

	on_Canny(0,0);
	on_Sobel(0,0);
	on_Scharr();

	//while ((char(waitKey(1))!='q'))
	//{
	//}
	waitKey(0);
	return 0;

}

void on_Canny(int,void*)
{
	blur(g_srcGrayImage,g_cannyDetecctedEdges,Size(3,3));
	Canny(g_cannyDetecctedEdges,g_cannyDetecctedEdges,g_cannyLowThreshold,g_cannyLowThreshold*3,3);
	g_dstImage=Scalar::all(0);
	g_srcImage.copyTo(g_dstImage,g_cannyDetecctedEdges);
	//cout<<g_dstImage<<endl;
	imshow(WINDOW_N_R_CA,g_dstImage);
}

void on_Sobel(int,void*)
{
	Sobel(g_srcImage,g_sobelGradient_X,CV_16S,1,0,(2*g_sobelKernelSize+1),1,1,BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_X,g_sobelAbsGradient_X);
	Sobel(g_srcImage,g_sobelGradient_Y,CV_16S,0,1,(2*g_sobelKernelSize+1),1,1,BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_Y,g_sobelAbsGradient_Y);
	addWeighted(g_sobelAbsGradient_X,0.5,g_sobelAbsGradient_Y,0.5,0,g_dstImage);
	imshow(WINDOW_N_R_SO,g_dstImage);
}

void on_Scharr()
{
	Scharr(g_srcImage,g_scharrGradient_X,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_X,g_scharrAbsGradient_X);

	Scharr(g_srcImage,g_scharrGradient_Y,CV_16S,0,1,1,0,BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_Y,g_scharrAbsGradient_Y);

	addWeighted(g_scharrAbsGradient_X,0.5,g_scharrAbsGradient_Y,0.5,0,g_dstImage);
	imshow(WINDOW_N_R_SC,g_dstImage);

}