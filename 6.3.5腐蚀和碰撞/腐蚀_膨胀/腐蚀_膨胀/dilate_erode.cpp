#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage;
int g_nTrackbarNumber=0;
int g_nStructElementSize=3;

void Process();
void on_TrackbarNumChange(int,void*);
void on_ElementSizeChange(int,void*);

int main()
{
	system("color 5E");
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("读取srcImage错误");return 0;
	}
	namedWindow("【原始图】");
	imshow("【原始图】",g_srcImage);

	Mat element=getStructuringElement(MORPH_RECT,
		Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
		Point(g_nStructElementSize,g_nStructElementSize));
	erode(g_srcImage,g_dstImage,element);
	imshow("【效果图】",g_dstImage);

	createTrackbar("腐蚀/膨胀","【效果图】",&g_nTrackbarNumber,1,on_TrackbarNumChange);
	createTrackbar("内核尺寸","【效果图】",&g_nStructElementSize,21,on_ElementSizeChange);

	while (char(waitKey(1))!='q')
	{
	}
	return 0;

}
void Process()
{
	Mat element=getStructuringElement(MORPH_RECT,
		Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
		Point(g_nStructElementSize,g_nStructElementSize));
	if (g_nTrackbarNumber==0)
	{
		erode(g_srcImage,g_dstImage,element);
	} 
	else
	{
		dilate(g_srcImage,g_dstImage,element);
	}
	imshow("【效果图】",g_dstImage);
}

void on_TrackbarNumChange(int,void*)
{
	Process();
}

void on_ElementSizeChange(int,void*)
{
	Process();
}





