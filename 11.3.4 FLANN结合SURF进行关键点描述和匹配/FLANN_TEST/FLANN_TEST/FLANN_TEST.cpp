/*
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc,char** argv)
{
	Mat img_1=imread("1.jpg",1);
	Mat img_2=imread("2.jpg",1);
}
*/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace std;
int main()
{
	system("color 6F");
	Mat trainImage=imread("1.jpg"),trainImage_gray;
	imshow("trainImage",trainImage);
	cvtColor(trainImage,trainImage_gray,CV_BGR2GRAY);
	vector<KeyPoint> train_keyPoint;
	Mat trainDescriptor;
	SurfFeatureDetector FeatureDetector(80);
	FeatureDetector.detect(trainImage_gray,train_keyPoint);
	SurfDescriptorExtractor featureEXtractor;
	featureEXtractor.compute(trainImage_gray,train_keyPoint,trainDescriptor);
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1,trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();
	VideoCapture cap(0);
	unsigned int frameCount=0;
	while(char(waitKey(1))!='q')
	{
		int64 time0=getTickCount();
		Mat testImage,testImage_gray;
		cap>>testImage;
		if (testImage.empty())
		{
			continue;
		}
		cvtColor(trainImage,trainImage_gray,CV_BGR2GRAY);
		vector<KeyPoint> test_keyPoint;
		Mat testDescriptor;
		FeatureDetector.detect(testImage_gray,test_keyPoint);
		featureEXtractor.compute(testImage_gray,test_keyPoint,testDescriptor);
		vector<vector<DMatch>> matches;
		matcher.knnMatch(testDescriptor,matches,2);
		vector<DMatch> goodMatches;
		for (unsigned int i=0;i<matches.size();i++)
		{
			if (matches[i][0].distance<0.6*matches[i][0].distance)
			{
				goodMatches.push_back(matches[i][0]);
			}
		}
		Mat dstImage;
		drawMatches(testImage,test_keyPoint,trainImage,train_keyPoint,goodMatches,dstImage);
		imshow("dstImage",dstImage);
		cout<<"µ±Ç°ÆµÂÊ£º"<<getTickFrequency()/(getTickCount()-time0)<<endl;
	}
	return 0;


}




