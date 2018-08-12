#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【修补后的效果图】"

Mat srcImage1,inpaintMask;
Point previousPoint(-1,-1);

static void On_Mouse(int event,int x,int y,int flags,void*)
{
	if (event==EVENT_LBUTTONUP||!(flags&EVENT_FLAG_LBUTTON))
		previousPoint=Point(-1,-1);
	else if(event==EVENT_LBUTTONDOWN)
		previousPoint=Point(x,y);
	else if(event==EVENT_MOUSEMOVE &&(flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x,y);
		if(previousPoint.x<0)
			previousPoint=pt;
		line(inpaintMask,previousPoint,pt,Scalar::all(255),5,8,0);
		line(srcImage1,previousPoint,pt,Scalar::all(255),5,8,0);
		previousPoint=pt;
		imshow(WINDOW_NAME1,srcImage1);
	}
}

int	main(int argc,char** argv)
{
	Mat srcImage=imread("1.jpg",-1);
	//imshow(WINDOW_NAME1,srcImage1);
	if (!srcImage.data)
	{
		printf("empty image!\n");
	}
	srcImage1=srcImage.clone();
	inpaintMask=Mat::zeros(srcImage1.size(),CV_8U);

	imshow(WINDOW_NAME1,srcImage1);
	setMouseCallback(WINDOW_NAME1,On_Mouse,0);
	while(1)
	{
		char c=(char)waitKey();
		if(c==27)
			break;
		if (c=='2')
		{
			inpaintMask=Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1,srcImage1);

		}
		if (c=='1'||c==' ')
		{
			Mat inpaintedImage;
			inpaint(srcImage1,inpaintMask,inpaintedImage,3,INPAINT_TELEA);
			imshow(WINDOW_NAME2,inpaintedImage);
		}
	}
	return 0;

}



















