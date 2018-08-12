#include <opencv2/core/core.hpp>
#include <features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main( int argc, char** argv)//
{
	Mat img_1=imread("1.jpg");
	Mat img_2=imread("2.jpg");
	//cout<<img_1.data<<endl;
	if (!img_1.data||!img_2.data)
	{
		cout<<"error read!!"<<endl;return false;
	}
	int minHession=100;
	SURF detector(minHession);
	vector<KeyPoint> keyPoints_1,keyPoints_2;
	detector.detect(img_1,keyPoints_1);
	detector.detect(img_2,keyPoints_2);
	SURF extractor;
	Mat descriptors_1,descriptors_2;
	extractor.compute(img_1,keyPoints_1,descriptors_1);
	extractor.compute(img_2,keyPoints_2,descriptors_2);
	
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1,descriptors_2,matches);
	double max_dist=0;
	double min_dist=100;
	for (int i=0;i<descriptors_1.rows;i++)
	{
		double dist=matches[i].distance;
		if(dist<min_dist) min_dist=dist;
		if(dist>max_dist) max_dist=dist;
	}
	printf(">>max dist:%f\n",max_dist);
	printf(">>min dist:%f\n",min_dist);

	vector<DMatch> good_matches;
	for (int i=0;i<descriptors_1.rows;i++)
	{
		if (matches[i].distance<5*min_dist)
		{good_matches.push_back(matches[i]);}
	}
	//cout<<good_matches.data()<<endl;
	Mat img_matches;
	drawMatches(img_1,keyPoints_1,img_2,keyPoints_2,
		good_matches,img_matches,Scalar::all(-1),Scalar::all(-1),
		vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cout<<good_matches.size()<<endl;
	for (int i=0;i<good_matches.size();i++)
	{
		printf(">>符合条件的匹配点【%d】（特征点1：%d--特征点2：%d）\n",i,good_matches[i].queryIdx,good_matches[i].trainIdx);
	}
	imshow("img_matches",img_matches);
	waitKey(0);
	return 0;
}







