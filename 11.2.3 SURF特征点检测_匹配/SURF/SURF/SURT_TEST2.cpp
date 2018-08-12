#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat srcImage1=imread("1.jpg",1);
	Mat srcImage2=imread("2.jpg",1);
	int minHessian=700;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint>keyPoint1,keyPoint2;
	detector.detect(srcImage1,keyPoint1);
	detector.detect(srcImage2,keyPoint2);
	SurfFeatureDetector extractor;
	Mat descriptors1,descriptors2;
	extractor.compute(srcImage1,keyPoint1,descriptors1);
	extractor.compute(srcImage2,keyPoint2,descriptors2);
	imshow("descriptors1",descriptors1);
	imshow("descriptors2",descriptors2);
	BruteForceMatcher<L2<float>> matcher;
	vector<DMatch> matches;
	matcher.match(descriptors1,descriptors2,matches);
	Mat imgMatches;
	drawMatches(srcImage1,keyPoint1,srcImage2,keyPoint2,matches,imgMatches);
	imshow("∆•≈‰Õº",imgMatches);
	waitKey();
	return 0;


}











