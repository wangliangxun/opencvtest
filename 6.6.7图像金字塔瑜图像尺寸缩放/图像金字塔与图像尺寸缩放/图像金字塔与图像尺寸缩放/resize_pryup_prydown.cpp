#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME "�����򴰿ڡ�"
Mat g_srcImage,g_dstImage,g_tmpImage;

int main()
{
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("��ȡͼ�����~��\n");return false;
	}
	namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME,g_srcImage);

	g_tmpImage=g_srcImage;
	g_dstImage=g_srcImage;

	int key=0;
	while(1)
	{
		key=waitKey(9);

		switch(key)
		{
		case 27 :
			return 0;
			break;
		case 'q':
			return 0;
			break;
		case 'a':
			pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">��a������pyrup����size*2\n\n");
			break;
		case 'w':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">��w������resize����size*2\n\n");
			break;
		case '1':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">��1������resize����size*2\n\n");
			break;
		case '3':
			pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">��3������pyrup����size*2\n\n");
			break;
		case 'd':
			pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">��d������pyrdown����size/2\n\n");
			break;
		case 's':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">��s������resize����size/2\n\n");
			break;
		case '2':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2),(0,0),(0,0),2);
			printf(">��2������resize����size/2\n\n");
			break;
		case '4':
			pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">��4������pyrdown����size/2\n\n");
			break;
		}
		imshow(WINDOW_NAME,g_dstImage);
		g_tmpImage=g_dstImage;
	}
	return 0;
}





