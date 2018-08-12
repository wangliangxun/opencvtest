#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage;//ԭʼͼ��Ч��ͼ
int g_nElementShape=MORPH_RECT;//Ԫ�ؽṹ����״

int g_nMaxIterationNum=10; 
int g_nOpenCloseNum=0;
int g_nErodeDilateNum=0;
int g_nTopBlackHatNum=0;

static void on_OpenClose(int,void *);
static void on_ErodeDilate(int,void*);
static void on_TopBlackHat(int,void*);
static void ShowHelpText();

int main()
{
	system("color 2F");
	ShowHelpText();
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("error!\n");return 0;
	}
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��",g_srcImage);

	namedWindow("��������/�����㡿",1);
	namedWindow("����ʴ/���͡�",1);
	namedWindow("����ñ/��ñ��",1);

	g_nOpenCloseNum=9;
	g_nErodeDilateNum=9;
	g_nTopBlackHatNum=2;

	createTrackbar("����ֵ","��������/�����㡿",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("����ֵ","����ʴ/���͡�",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("����ֵ","����ñ/��ñ��",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

	while (1)
	{
		int c;
		on_OpenClose(g_nOpenCloseNum,0);
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);

		c=waitKey(0);
		if ((char)c=='q'||(char)c==27)
		{
			break;
		}
		if ((char)c==49)
		{
			g_nElementShape=MORPH_ELLIPSE;
		} 
		else if((char)c==50)
		{
			g_nElementShape=MORPH_RECT;
		}
		else if ((char)c==51)
		{
			g_nElementShape=MORPH_CROSS;
		}
		else if ((char)c==' ')
		{
			g_nElementShape=(g_nElementShape+1)%3;
		}
	}
	return 0;
}

static void on_OpenClose(int,void *)
{
	int offset=g_nOpenCloseNum-g_nMaxIterationNum;
	int Absolute_offset=offset>0?offset:-offset;
	Mat element=getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1,Absolute_offset*2+1),
		Point(Absolute_offset,Absolute_offset));
	if (offset<0)
	{
		morphologyEx(g_srcImage,g_dstImage,CV_MOP_OPEN,element);
	} 
	else
	{
		morphologyEx(g_srcImage,g_dstImage,CV_MOP_CLOSE,element);
	}
	imshow("��������/�����㡿",g_dstImage);
}

static void on_ErodeDilate(int,void*)
{
	int offset=g_nErodeDilateNum-g_nMaxIterationNum;
	int Absolute_offset=offset>0?offset:-offset;
	Mat element=getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1,Absolute_offset*2+1),
		Point(Absolute_offset,Absolute_offset));
	if (offset<0)
	{
		erode(g_srcImage,g_dstImage,element);
	} 
	else
	{
		dilate(g_srcImage,g_dstImage,element);
	}
	imshow("����ʴ/���͡�",g_dstImage);
}

static void on_TopBlackHat(int,void*)
{
	int offset=g_nTopBlackHatNum-g_nMaxIterationNum;
	int Absolute_offset=offset>0?offset:-offset;
	Mat element=getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1,Absolute_offset*2+1),
		Point(Absolute_offset,Absolute_offset));
	if (offset<0)
	{
		morphologyEx(g_srcImage,g_dstImage,MORPH_TOPHAT,element);
	} 
	else
	{
		morphologyEx(g_srcImage,g_dstImage,MORPH_BLACKHAT,element);
	}
	imshow("����ñ/��ñ��",g_dstImage);
}


static void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV2��ĵ�48������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//���һЩ������Ϣ
	printf("\n\t������������۲�ͼ��Ч��\n\n");
	printf( "\n\t��������˵��: \n\n"
		"\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"
		"\t\t���̰�����1��- ʹ����Բ(Elliptic)�ṹԪ��\n"
		"\t\t���̰�����2��- ʹ�þ���(Rectangle )�ṹԪ��\n"
		"\t\t���̰�����3��- ʹ��ʮ����(Cross-shaped)�ṹԪ��\n"
		"\t\t���̰������ո�SPACE��- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n"	);
}



