#include<opencv2\opencv.hpp>
#include<time.h>
using namespace cv;
using namespace std;

int main()
{
	/*FileStorage fs("test.xml",FileStorage::WRITE);
	fs<<"frameCount"<<5;
	time_t rawtime;time(&rawtime);
	fs<<"calibrationDate"<<asctime(localtime(&rawtime));
	Mat cameraMatrix=(Mat_<double>(3,3)<<100,0,320,0,1000,240,0,0,1);
	Mat distCoeffs=(Mat_<double>(5,1)<<0.1,0.01,-0.001,0,0);

	fs<<"cameraMatrix"<<cameraMatrix<<"distCoeffs"<<distCoeffs;
	fs<<"features"<<"[";
	for(int i=0;i<3;i++)
	{
		int x=rand()%640;
		int y=rand()%480;
		uchar lbp=rand()%256;

		fs<<"{:"<<"x"<<x<<"y"<<y<<"lbp"<<"[:";
		for(int j=0;j<8;j++){fs<<((lbp>>j)&1);}
		fs<<"]"<<"}";
	}
	fs<<"]";
	fs.release();
	printf("-----¶ÁÐ´Íê±Ï-----");
	getchar();
	return 0;*/

	system("color 5F");
	FileStorage fs2("test.yaml",FileStorage::READ);
	int frameCount=(int)fs2["frameCount"];
	std::string date;
	fs2["calibrationDate"]>>date;
	Mat cameraMatrix2,distCoeffs2;
	fs2["cameraMatrix"]>>cameraMatrix2;
	fs2["distCoeffs"]>>distCoeffs2;

	cout<<"frameCount:"<<frameCount<<endl
		<<"calibration date:"<<date<<endl
		<<"camera matrix:"<<cameraMatrix2<<endl
		<<"distortion Coeffs:"<<distCoeffs2<<endl;
	FileNode features=fs2["features"];
	FileNodeIterator it=features.begin(),it_end=features.end();
	int idx=0;
	std::vector<uchar> lbpval;
	for(;it!=it_end;++it,idx++)
	{
		cout<<"feature #"<<idx<<":";
		cout<<"x="<<(int)(*it)["x"]<<"y="<<(int)(*it)["y"]<<",lbp:(";
		(*it)["lbp"]>>lbpval;
		for(int i=0;i<(int)lbpval.size();i++)
			cout<<" "<<(int)lbpval[i];
		cout<<")"<<endl;
	}
	fs2.release();
	printf("\n --------³ÌÐò½áÊø---------");
	getchar();
	return 0;

}