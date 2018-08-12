#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOWS_NAME1 "¡¾Ô­Ê¼Í¼¡¿"
#define WINDOWS_NAME2 "¡¾wrap¡¿"
#define WINDOWS_NAME3 "¡¾wrap and rotate¡¿"

static void ShowHelpText();

int main()
{
	system("color 1A");
	ShowHelpText();
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	Mat rotMat(2,3,CV_32FC1);
	Mat warMat(2,3,CV_32FC1);
	Mat srcImage,dstImage_wrap,dstImage_wrap_rotate;

	srcImage=imread("1.jpg",1);

	if (!srcImage.data)
	{
		printf("error in reading image!")
	}
	dstImage_wrap=Mat::zeros(srcImage.rows,srcImage.cols,srcImage.type());



}















