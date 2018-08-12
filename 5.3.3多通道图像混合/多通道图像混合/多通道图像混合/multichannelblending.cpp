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
	if(MultiChannelBlending()){cout<<endl<<"\n ���гɹ���";}
	waitKey(0);
	return 0;
}
/*��ͨ����Ϻ���*/
bool MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	/*---------��ɫͨ��-----------*/
	Mat imageBlueChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("��ȡsrcImage����\n");return false;}
	if(!logoImage.data){printf("��ȡlogoImage����\n");return false;}

	split(srcImage,channels);
	imageBlueChannel=channels.at(0);

	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<1>��Ϸԭͼ+logo��ɫͨ��");imshow("<1>��Ϸԭͼ+logo��ɫͨ��",srcImage);

	/*---------��ɫͨ��-----------*/
	Mat imageGreenChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("��ȡsrcImage����\n");return false;}
	if(!logoImage.data){printf("��ȡlogoImage����\n");return false;}

	split(srcImage,channels);
	imageGreenChannel=channels.at(1);

	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<2>��Ϸԭͼ+logo��ɫͨ��");imshow("<2>��Ϸԭͼ+logo��ɫͨ��",srcImage);

	/*---------��ɫͨ��-----------*/
	Mat imageRedChannel;
	logoImage=imread("dota_logo.jpg",0);
	srcImage=imread("dota_jugg.jpg");

	if(!srcImage.data){printf("��ȡsrcImage����\n");return false;}
	if(!logoImage.data){printf("��ȡlogoImage����\n");return false;}

	split(srcImage,channels);
	imageRedChannel=channels.at(2);

	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),
		1.0,
		logoImage,
		0.5,
		0,
		imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
	merge(channels,srcImage);
	namedWindow("<3>��Ϸԭͼ+logo��ɫͨ��");imshow("<3>��Ϸԭͼ+logo��ɫͨ��",srcImage);
	return true;
}





