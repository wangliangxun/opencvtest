#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOWS_NAME1 "程序窗口1"
#define WINDOWS_NAME2 "效果图"

Mat g_maskImage,g_srcImage;
Point prevPt(-1,-1);

static void ShowHelpText();
static void on_Mouse(int event,int x,int y,int flags,void*);

int main(int argc,char** argv)
{
	system("color 6F");
	ShowHelpText();

	g_srcImage=imread("1.jpg",1);
	imshow(WINDOWS_NAME1,g_srcImage);
	Mat srcImage,grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage,g_maskImage,COLOR_BGR2GRAY);
	//imshow("maskImage",g_maskImage);
	cvtColor(g_maskImage,grayImage,COLOR_GRAY2BGR);
	//imshow("grayImage",grayImage);
	//g_maskImage=Scalar::all(0);

	setMouseCallback(WINDOWS_NAME1,on_Mouse,0);

	while(1)
	{
		int c=waitKey(0);
		if((char)c==27)
			break;
		if ((char)c=='2')
		{
			g_maskImage=Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image",g_srcImage);
		}
		if ((char)c=='1'||(char)c==' ')
		{
			int i,j,compCount=0;
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			imshow("g_maskImage1",g_maskImage);
			findContours(g_maskImage,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);

			if (contours.empty())
				continue;

			Mat mastImage(g_maskImage.size(),CV_32S);
			//g_maskImage.copyTo(mastImage);
			mastImage=Scalar::all(0);
			imshow("g_maskImage2",g_maskImage);
			//imshow("mastImage",mastImage);
			for (int index=0;index>=0;index=hierarchy[index][0],compCount++)
				drawContours(mastImage,contours,index,Scalar::all(compCount+1),-1,8,hierarchy,INT_MAX);
			//imshow("mastImage",mastImage);
			if(compCount=0)
				continue;

			vector<Vec3b> colorTab;
			for (i=0;i<compCount;i++)
			{
				int b=theRNG().uniform(0,255);
				int g=theRNG().uniform(0,255);
				int r=theRNG().uniform(0,255);

				colorTab.push_back(Vec3b((uchar)b,(uchar)g,(uchar)r));
			}

			double dTime=(double)getTickCount();
			watershed(srcImage,mastImage);
			dTime=(double)getTickCount()-dTime;
			printf("\t处理时间=%gms\n",dTime*1000./getTickFrequency());

			Mat watershedImage(mastImage.size(),CV_8UC3);
			for (i=0;i<mastImage.rows;i++)
				for (j=0;j<mastImage.cols;j++)
				{
					int index=mastImage.at<int>(i,j);
					if (index=-1)
						watershedImage.at<Vec3b>(i,j)=Vec3b(255,255,255);
					else if (index<=0||index>compCount)
						watershedImage.at<Vec3b>(i,j)=Vec3b(0,0,0);
					else
						watershedImage.at<Vec3b>(i,j)=colorTab[index-1];		
				}
				watershedImage=watershedImage*0.5+grayImage*0.5;
				imshow(WINDOWS_NAME2,watershedImage);
		}
	}
	return 0;
}

static void on_Mouse(int event,int x,int y,int flags,void*)
{
	if (x<0||x>=g_srcImage.cols||y<0||y>=g_srcImage.rows)
		return;
	if(event=CV_EVENT_FLAG_LBUTTON||!(flags &CV_EVENT_FLAG_LBUTTON))
		prevPt=Point(-1,-1);
	else if(event==CV_EVENT_FLAG_LBUTTON)
		prevPt=Point(x,y);
	else if(event==CV_EVENT_MOUSEMOVE &&(flags&CV_EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if(prevPt.x<0)
			prevPt=pt;
		line(g_maskImage,prevPt,pt,Scalar::all(255),5,8,0);
		line(g_srcImage,prevPt,pt,Scalar::all(255),5,8,0);
		prevPt=pt;
		imshow(WINDOWS_NAME1,g_srcImage);
	}
}
static void ShowHelpText()
{
	printf("\t请先用鼠标在图片窗口中标记出大致的区域，\n\n\t然后再按键【1】或者【SPACE】启动算法。"
		"\n\n\t按键操作说明: \n\n"  
		"\t\t键盘按键【1】或者【SPACE】- 运行的分水岭分割算法\n"  
		"\t\t键盘按键【2】- 恢复原始图片\n"  
		"\t\t键盘按键【ESC】- 退出程序\n\n\n");  
}