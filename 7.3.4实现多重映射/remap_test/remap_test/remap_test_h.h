#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
#define WINDOW_NAME "【程序窗口】"

Mat g_srcImage,g_dstImage;
Mat g_map_x,g_map_y;

int update_map(int key);
static void ShowHelpText();

int update_map(int key)
{
	for (int j=0;j<g_srcImage.rows;j++)
	{
		for (int i=0;i<g_srcImage.cols;i++)
		{
			switch(key)
			{
			case '1':
				if (i>g_srcImage.cols*0.25&&i<g_srcImage.cols*0.75&&j>g_srcImage.rows*0.25&&j<g_srcImage.rows*0.75)
				{
					g_map_x.at<float>(j,i)=static_cast<float>(2*(i-g_srcImage.cols*0.25)+0.5);
					g_map_y.at<float>(j,i)=static_cast<float>(2*(j-g_srcImage.rows*0.25)+0.5);
				} 
				else
				{
					g_map_x.at<float>(j,i)=0;
					g_map_y.at<float>(j,i)=0;
				}
				break;
			case '2':
				g_map_x.at<float>(j,i)=static_cast<float>(i);
				g_map_y.at<float>(j,i)=static_cast<float>(g_srcImage.rows-j);
				break;
			case '3':
				g_map_x.at<float>(j,i)=static_cast<float>(g_srcImage.cols-i);
				g_map_y.at<float>(j,i)=static_cast<float>(j);
				break;
			case '4':
				g_map_x.at<float>(j,i)=static_cast<float>(g_srcImage.cols-i);
				g_map_y.at<float>(j,i)=static_cast<float>(g_srcImage.rows-j);
				break;
			}
		}
	}
	return 1;
}

static void ShowHelpText()
{
	printf("\n\n\n欢迎来到重映射~\n\n");
	printf("\n\n\tps:\n"
		"\t\t【ESC】\t\n"
		"\t\t【1】\t\t\n"
		"\t\t【2】\t\t\n"
		"\t\t【3】\t\t\n"
		"\t\t【4】\t\t\n");
}