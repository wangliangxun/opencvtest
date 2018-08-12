#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include <remap_test_h.h>
using namespace cv;
using namespace std;


int main(int argc,char **argv)
{
	system("color 2F");
	ShowHelpText();
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("读取图片错误，请确定目录下是否有1.jpg！\n");
		return false;
	}
	imshow("原始图",g_srcImage);
	g_dstImage.create(g_srcImage.size(),g_srcImage.type());
	g_map_x.create(g_srcImage.size(),CV_32FC1);
	g_map_y.create(g_srcImage.size(),CV_32FC1);

	namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME,g_srcImage);

	while(1)
	{
		int key=waitKey(0);
		if ((key&255)==27)
		{
			cout<<"程序退出........\n";
			break;
		}
		update_map(key);
		remap(g_srcImage,g_dstImage,g_map_x,g_map_y,CV_INTER_LINEAR,BORDER_CONSTANT,Scalar(0,0,0));
		imshow(WINDOW_NAME,g_dstImage);

	}
	return 0;
}