#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage1=imread("1.jpg",1);
	Mat srcImage2=imread("2.jpg",1);
	if (!srcImage1.data||!srcImage2.data)
	{printf(">>error read");return false;
	}
	//使用surf算子检测关键点
	int minHession=400;
	SurfFeatureDetector detector(minHession);//定义一个SurfFeatureDetector特征检测类对象
	vector<KeyPoint> keypoints_object,keypoints_scence;//vector模板类，存放任意类型的动态数组

	//利用detect函数检测出SURF特征关键点，保存在vector容器中
	detector.detect(srcImage1,keypoints_object);
	detector.detect(srcImage2,keypoints_scence);

	//计算描述符（特征向量）
	SurfDescriptorExtractor extractor;
	Mat descriptors_object,descriptors_scence;
	extractor.compute(srcImage1,keypoints_object,descriptors_object);
	extractor.compute(srcImage2,keypoints_scence,descriptors_scence);

	//使用FLANN匹配算子进行匹配
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_object,descriptors_scence,matches);
	double max_dist=0;double min_dist=100;//最小距离和最大距离

	//计算出关键点之间距离的最大值和最小值
	for (int i=0;i<descriptors_object.rows;i++)
	{
		double dist=matches[i].distance;
		if (dist<min_dist)
		{min_dist=dist;
		}
		if (dist>max_dist)
		{max_dist=dist;
		}
	}

	printf(">>max dist : %f \n",max_dist);
	printf(">>min dist : %f \n",min_dist);

	//存下匹配距离小于3*min_dist的点对
	vector<DMatch> good_matches;
	for (int i=0;i<descriptors_object.rows;i++)
	{
		if (matches[i].distance<3*min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	//绘制出匹配到的关键点
	Mat img_matches;
	drawMatches(srcImage1,keypoints_object,srcImage2,keypoints_scence,good_matches,img_matches,
		Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//定义两个局部变量
	vector<Point2f> obj;
	vector<Point2f> scence;

	//从匹配成功的匹配对中获取关键点
	for (unsigned int i=0;i<good_matches.size();i++)
	{
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scence.push_back(keypoints_scence[good_matches[i].trainIdx].pt);
	}

	Mat H=findHomography(obj,scence,CV_RANSAC);//计算透视变换
	//从待测图片中获取角点
	vector<Point2f> obj_corners(4);
	obj_corners[0]=cvPoint(0,0);
	obj_corners[1]=cvPoint(srcImage1.cols,0);
	obj_corners[2]=cvPoint(srcImage1.cols,srcImage1.rows);
	obj_corners[3]=cvPoint(0,srcImage1.rows);
	vector<Point2f> scence_corners(4);

	//进行透视变换
	perspectiveTransform(obj_corners,scence_corners,H);

	//绘制出角点之间的直线
	line(img_matches,scence_corners[0]+Point2f(static_cast<float>(srcImage1.cols),0),
		scence_corners[1]+Point2f(static_cast<float>(srcImage1.cols),0),Scalar(255,0,123),4);
	line(img_matches,scence_corners[1]+Point2f(static_cast<float>(srcImage1.cols),0),
		scence_corners[2]+Point2f(static_cast<float>(srcImage1.cols),0),Scalar(255,0,123),4);
	line(img_matches,scence_corners[2]+Point2f(static_cast<float>(srcImage1.cols),0),
		scence_corners[3]+Point2f(static_cast<float>(srcImage1.cols),0),Scalar(255,0,123),4);
	line(img_matches,scence_corners[3]+Point2f(static_cast<float>(srcImage1.cols),0),
		scence_corners[0]+Point2f(static_cast<float>(srcImage1.cols),0),Scalar(255,0,123),4);

	//显示最终结果
	imshow("Good Matches & Object detection",img_matches);
	waitKey(0);
	return 0;

}










