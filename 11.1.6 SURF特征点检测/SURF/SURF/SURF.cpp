#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	system("color 2F");
	//ShowHelpTest();
	Mat srcImage1=imread("1.jpg",1);
	Mat srcImage2=imread("2.jpg",1);
	if (!srcImage1.data||!srcImage2.data)
	{
		cout<<"error imread"<<endl;
	}
	imshow("srcImage1",srcImage1);
	imshow("srcImage2",srcImage2);
	int minHession=400;
	SurfFeatureDetector detector(minHession);
	vector<KeyPoint> keypoint_1,keypoint_2;
	detector.detect(srcImage1,keypoint_1);
	detector.detect(srcImage2,keypoint_2);
	Mat img_keypoints_1,img_keypoints_2;
	drawKeypoints(srcImage1,keypoint_1,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2,keypoint_2,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
	imshow("img_keypoints_1",img_keypoints_1);
	imshow("img_keypoints_2",img_keypoints_2);
	waitKey();
	return 0;


}








