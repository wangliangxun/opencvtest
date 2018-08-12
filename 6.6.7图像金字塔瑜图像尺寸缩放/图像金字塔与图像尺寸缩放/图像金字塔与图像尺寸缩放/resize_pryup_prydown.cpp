#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME "¡¾³ÌÐò´°¿Ú¡¿"
Mat g_srcImage,g_dstImage,g_tmpImage;

int main()
{
	g_srcImage=imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("¶ÁÈ¡Í¼Ïñ´íÎó~£¡\n");return false;
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
			printf(">¡¾a¡¿¡ª¡ªpyrup¡ª¡ªsize*2\n\n");
			break;
		case 'w':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">¡¾w¡¿¡ª¡ªresize¡ª¡ªsize*2\n\n");
			break;
		case '1':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">¡¾1¡¿¡ª¡ªresize¡ª¡ªsize*2\n\n");
			break;
		case '3':
			pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
			printf(">¡¾3¡¿¡ª¡ªpyrup¡ª¡ªsize*2\n\n");
			break;
		case 'd':
			pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">¡¾d¡¿¡ª¡ªpyrdown¡ª¡ªsize/2\n\n");
			break;
		case 's':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">¡¾s¡¿¡ª¡ªresize¡ª¡ªsize/2\n\n");
			break;
		case '2':
			resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2),(0,0),(0,0),2);
			printf(">¡¾2¡¿¡ª¡ªresize¡ª¡ªsize/2\n\n");
			break;
		case '4':
			pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
			printf(">¡¾4¡¿¡ª¡ªpyrdown¡ª¡ªsize/2\n\n");
			break;
		}
		imshow(WINDOW_NAME,g_dstImage);
		g_tmpImage=g_dstImage;
	}
	return 0;
}





