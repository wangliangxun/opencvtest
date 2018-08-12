#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage=imread("1.jpg",0);
	imshow("ԭͼ",srcImage);
	if (!srcImage.data)
	{
		cout<<"failed to load image"<<endl;
		return 0;
	}
	MatND dstHist;
	int dims=1;
	float hranges[]={0,255};
	const float *ranges[]={hranges};
	int size =256;
	int changles=0;

	calcHist(&srcImage,1,&changles,Mat(),dstHist,dims,&size,ranges);
	int scale=1;

	Mat dstImage(size * scale,size,CV_8U,Scalar(0));
	double minValue=0;
	double maxValue=0;
	minMaxLoc(dstHist,&minValue,&maxValue,0,0);

	int hpt=saturate_cast<int>(0.9*size);
	for (int i=0;i<256;i++)
	{
		float binValue=dstHist.at<float>(i);
		int realValue=saturate_cast<int>(binValue*hpt/maxValue);
		rectangle(dstImage,Point(i*scale,size-1),Point((i+1)*scale-1,size-realValue),Scalar(255));

	}
	imshow("ֱ��ͼ",dstImage);
	waitKey(0);

}







