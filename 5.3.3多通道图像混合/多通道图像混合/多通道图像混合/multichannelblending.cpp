#include <opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool MultiChannelBlending();
void ShowHelpText();
int main()
{
	system("color 9F");
	if(MultiChannelBlending()){cout<<endl<<"\n 运行成功！";}
	waitKey(0);
	return 0;
}
/*多通道混合函数*/
bool MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	/*---------蓝色通道-----------*/
	Mat imageBlueChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("读取srcImage错误\n");return false;}
	if(!logoImage.data){printf("读取logoImage错误\n");return false;}

	split(srcImage,channels);
	imageBlueChannel=channels.at(0);

	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<1>游戏原图+logo蓝色通道");imshow("<1>游戏原图+logo蓝色通道",srcImage);

	/*---------绿色通道-----------*/
	Mat imageGreenChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("读取srcImage错误\n");return false;}
	if(!logoImage.data){printf("读取logoImage错误\n");return false;}

	split(srcImage,channels);
	imageGreenChannel=channels.at(1);

	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<2>游戏原图+logo绿色通道");imshow("<2>游戏原图+logo绿色通道",srcImage);

	/*---------红色通道-----------*/
	Mat imageRedChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("读取srcImage错误\n");return false;}
	if(!logoImage.data){printf("读取logoImage错误\n");return false;}

	split(srcImage,channels);
	imageRedChannel=channels.at(2);

	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<3>游戏原图+logo红色通道");imshow("<3>游戏原图+logo红色通道",srcImage);
	return true;
}





