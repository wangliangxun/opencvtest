//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;
//int g_nBoxFilterValue=3;
//int g_nMeanBlurValue=3;
//int g_nGaussianBlurValue=3;
//
//static void on_BoxFilter(int,void *);
//static void on_MeanBlur(int,void *);
//static void on_GaussianBlur(int,void *);
//
//int main()
//{
//	system("color 5E");
//	g_srcImage=imread("1.jpg",1);
//	if (!g_srcImage.data)
//	{
//		printf("----��ȡ1.jpg����----");
//		return false;
//	}
//	g_dstImage1=g_srcImage.clone();
//	g_dstImage2=g_srcImage.clone();
//	g_dstImage3=g_srcImage.clone();
//
//	namedWindow("��<0>ԭͼ���ڡ�",1);
//	imshow("��<0>ԭͼ���ڡ�",g_srcImage);
//
//	/************************************************************************/
//	/* �����˲�                                                                     */
//	/************************************************************************/
//	namedWindow("��<1>�����˲���");
//
//	createTrackbar("�ں�ֵ","��<1>�����˲���",&g_nBoxFilterValue,40,on_BoxFilter);
//	on_BoxFilter(g_nBoxFilterValue,0);
//
//	/************************************************************************/
//	/* ��ֵ�˲�                                                                     */
//	/************************************************************************/
//	namedWindow("��<2>��ֵ�˲���");
//	createTrackbar("�ں�ֵ","��<2>��ֵ�˲���",&g_nMeanBlurValue,40,on_MeanBlur);
//	on_MeanBlur(g_nMeanBlurValue,0);
//
//	/************************************************************************/
//	/* ��˹�˲�                                                                     */
//	/************************************************************************/
//	namedWindow("��<3>��˹�˲���");
//	createTrackbar("�ں�ֵ","��<3>��˹�˲���",&g_nGaussianBlurValue,40,on_GaussianBlur);
//	on_GaussianBlur(g_nGaussianBlurValue,0);
//
//	cout<<endl<<"\t,������������۲�ͼ����~\n\n"
//		<<"\t����q�����˳�~";
//	while(char(waitKey(1))!='q'){}
//	return 0;
//}
///************************************************************************/
///*                                �����˲�����                                      */
///************************************************************************/
//static void on_BoxFilter(int,void*)
//{
//	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
//	imshow("��<1>�����˲���",g_dstImage1);
//}
//
///************************************************************************/
///*                                ��ֵ�˲�����                                      */
///************************************************************************/
//static void on_MeanBlur(int,void*)
//{
//	blur(g_srcImage,g_dstImage2,Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1),Point(-1,-1));
//	imshow("��<2>��ֵ�˲���",g_dstImage2);
//}
//
///************************************************************************/
///*                                ��˹�˲�����                                      */
///************************************************************************/
//static void on_GaussianBlur(int,void*)
//{
//	GaussianBlur(g_srcImage,g_dstImage3,Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),0,0);
//	imshow("��<3>��˹�˲���",g_dstImage3);
//}
//
//
//
//
//
//
//
//
//
//
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue=6;
int g_nMeanBlurValue=10;
int g_nGaussianBlurValue=6;
int g_nMedianBlurValue=10;
int g_nBilateralFilterValue=10;

static void on_BoxFilter(int,void *);
static void on_MeanBlur(int,void *);
static void on_GaussianBlur(int,void *);
static void on_MedianBlur(int,void*);
static void	on_BilateralFilter(int,void*);

int main()
{
	system("color 5E");
	g_srcImage=imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("��ȡsrcImage����\n");return 0;
	}

	g_dstImage1=g_srcImage.clone();
	g_dstImage2=g_srcImage.clone();
	g_dstImage3=g_srcImage.clone();
	g_dstImage4=g_srcImage.clone();
	g_dstImage5=g_srcImage.clone();

	namedWindow("��<0>ԭͼ���ڡ�",1);
	imshow("��<0>ԭͼ���ڡ�",g_srcImage);
	
	/************************************************************************/
	/* �����˲�                                                                     */
	/************************************************************************/
	namedWindow("��<1>�����˲���");
	
	createTrackbar("�ں�ֵ","��<1>�����˲���",&g_nBoxFilterValue,40,on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue,0);
	
	/************************************************************************/
	/* ��ֵ�˲�                                                                     */
	/************************************************************************/
	namedWindow("��<2>��ֵ�˲���");
	createTrackbar("�ں�ֵ","��<2>��ֵ�˲���",&g_nMeanBlurValue,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue,0);
	
	/************************************************************************/
	/* ��˹�˲�                                                                     */
	/************************************************************************/
	namedWindow("��<3>��˹�˲���");
	createTrackbar("�ں�ֵ","��<3>��˹�˲���",&g_nGaussianBlurValue,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue,0);
	
	/************************************************************************/
	/*                          <4>��ֵ�˲�                                  */
	/************************************************************************/
	namedWindow("��<4>��ֵ�˲���",1);
	createTrackbar("�ں�ֵ","��<4>��ֵ�˲���",&g_nMedianBlurValue,50,on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue,0);

	/************************************************************************/
	/*                          <5>˫���˲�                                */
	/************************************************************************/

	namedWindow("��<5>˫���˲���",1);
	createTrackbar("����ֵ","��<5>˫���˲���",&g_nBilateralFilterValue,50,on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue,0);

	cout<<endl<<"\t,������������۲�ͼ����~\n\n"
		<<"\t����q�����˳�~";
	while(char(waitKey(1))!='q'){}
	return 0;
}

/************************************************************************/
/*                                �����˲�����                                      */
/************************************************************************/
static void on_BoxFilter(int,void*)
{
	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
	imshow("��<1>�����˲���",g_dstImage1);
}

/************************************************************************/
/*                                ��ֵ�˲�����                                      */
/************************************************************************/
static void on_MeanBlur(int,void*)
{
	blur(g_srcImage,g_dstImage2,Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1),Point(-1,-1));
	imshow("��<2>��ֵ�˲���",g_dstImage2);
}

/************************************************************************/
/*                                ��˹�˲�����                                      */
/************************************************************************/
static void on_GaussianBlur(int,void*)
{
	GaussianBlur(g_srcImage,g_dstImage3,Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),0,0);
	imshow("��<3>��˹�˲���",g_dstImage3);
}

/************************************************************************/
/*                                ��ֵ�˲�����                          */
/************************************************************************/
static void on_MedianBlur(int,void*)
{
	medianBlur(g_srcImage,g_dstImage4,g_nMedianBlurValue*2+1);
	imshow("��<4>��ֵ�˲���",g_dstImage4);
}


/************************************************************************/
/*                               ˫���˲�����                           */
/************************************************************************/
static void on_BilateralFilter(int,void*)
{
	bilateralFilter(g_srcImage,g_dstImage5,g_nBilateralFilterValue,g_nBilateralFilterValue*2,g_nBilateralFilterValue/2);
	imshow("��<5>˫���˲���",g_dstImage5);
}






