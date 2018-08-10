#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat srcImage=imread("1.jpg",1);
	imshow("srcImage",srcImage);
	Mat grayImage;
	cvtColor(srcImage,grayImage,CV_BGR2GRAY);

	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoint;
	Mat descriptors;

	featureDetector.detect(grayImage,keyPoint);

	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage,keyPoint,descriptors);

	flann::Index flannIndex(descriptors,flann::LshIndexParams(12,20,2),cvflann::FLANN_DIST_HAMMING);

	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH,360);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,360);

	unsigned int frameCount=0;
	while (1)
	{
		double time0=static_cast<double>(getTickCount());
		Mat captureImage,captureImage_gray;
		cap>>captureImage;
		if (captureImage.empty())
		{continue;
		}

		cvtColor(captureImage,captureImage_gray,CV_BGR2GRAY);

		vector<KeyPoint> captureKeyPoints;
		Mat captureDescription;

		featureDetector.detect(captureImage_gray,captureKeyPoints);

		featureExtractor.compute(captureImage_gray,captureKeyPoints,captureDescription);

		Mat matchIndex(captureDescription.rows,2,CV_32SC1);
		Mat matchDistance(captureDescription.rows,2,CV_32SC1);
		flannIndex.knnSearch(captureDescription,matchIndex,matchDistance,2,flann::SearchParams());

		vector<DMatch> goodMatches;
		for (int i=0;i<matchIndex.rows;i++)
		{
			if (matchDistance.at<float>(i,0)<0.6*matchDistance.at<float>(i,1))
			{
				DMatch dmatches(i,matchIndex.at<int>(i,0),matchDistance.at<float>(i,1));
				goodMatches.push_back(dmatches);
			}
		}
		Mat resultImages;
		drawMatches(captureImage,captureKeyPoints,srcImage,keyPoint,goodMatches,resultImages);
		imshow("resultImages",resultImages);

		cout<<">>frequence = "<<getTickFrequency()/(getTickCount()-time0)<<endl;
		if (char(waitKey(1)==27))
		{break;
		}
	}
	return 0;

}







