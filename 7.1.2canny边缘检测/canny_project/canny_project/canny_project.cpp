#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat src=imread("1.jpg");
	Mat src1=src.clone();
	Mat src2=src.clone();
	
	imshow("¡¾Ô­Ê¼Í¼1¡¿Canny±ßÔµ¼ì²â",src);
	Canny(src2,src2,3,355,3);
	imshow("¡¾Ð§¹ûÍ¼1¡¿Canny±ßÔµ¼ì²â",src2);

	Mat dst,edge,gray;
	dst.create(src1.size(),src1.type());
	cvtColor(src1,gray,COLOR_RGB2GRAY);

	blur(gray,edge,Size(3,3));
	//cout<<edge<<endl;
	
	Canny(edge,edge,55,55,3);
	//cout<<edge<<endl;
	dst=Scalar::all(0);
	src1.copyTo(dst,edge);
	imshow("¡¾Ð§¹ûÍ¼2¡¿Canny±ßÔµ¼ì²â",edge);


	waitKey(0);
	return 0;

}



