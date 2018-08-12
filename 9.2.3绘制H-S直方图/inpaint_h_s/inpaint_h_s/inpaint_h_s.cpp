#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

int main()
{
	Mat srcImage,hsvImage;
	srcImage=imread("1.jpg");
	cvtColor(srcImage,hsvImage,COLOR_BGR2HSV);

	int hueBinNum=30;
	int saturationBinNum=32;
	int histSize[]={hueBinNum,saturationBinNum};

	float hueRanges[]={0,180};

	float saturationRanges[]={0,256};
	const float* ranges[]={hueRanges,saturationRanges};

	Mat dstHist;

	int changles[]={0,1};
	calcHist(&hsvImage,1,changles,Mat(),dstHist,2,histSize,ranges,true,false);

	double maxValue=0;
	minMaxLoc(dstHist,0,&maxValue,0,0);

	int scale=10;
	
	Mat histImage=Mat::zeros(saturationBinNum*scale,hueBinNum*10,CV_8UC3);

	for (int hue=0;hue<hueBinNum;hue++)
	{
		for (int saturation=0;saturation<saturationBinNum;saturation++)
		{
			float binValue=dstHist.at<float>(hue,saturation);
			int intensity=cvRound(binValue*255/maxValue);
			rectangle(histImage,Point(hue*scale,saturation*scale),
				Point((hue+1)*scale-1,(saturation+1)*scale-1),Scalar::all(intensity),CV_FILLED);
		}
	}
	imshow("ËØ²ÄÍ¼",srcImage);
	imshow("H-SÖ±·½Í¼",histImage);
	waitKey();

}






