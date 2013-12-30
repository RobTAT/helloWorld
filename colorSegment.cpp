#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static const char WINDOW[] = "Value Control Panel";

Mat input_Image;

int minRGB[3] = {70,15,15};
int maxRGB[3] = {120,30,45};
int minHSV[3] = {0,0,40};
int maxHSV[3] = {26,40,255};


Mat colorSegRGB(const Mat& src){
	assert(src.type() == CV_8UC3);
	Mat filtered_Image;
	inRange(src, Scalar(minRGB[2], minRGB[1], minRGB[0]), 
		     Scalar(maxRGB[2], maxRGB[1], maxRGB[0]), filtered_Image);
	return filtered_Image;
}


Mat colorSegHSV(const Mat& src){
	assert(src.type() == CV_8UC3);
	Mat filtered_Image, HSV_Image;
	cvtColor(src, filtered_Image, CV_BGR2HSV);
	inRange(src, Scalar(minHSV[0], minHSV[1], minHSV[2]), 
		     Scalar(maxHSV[0], maxHSV[1], maxHSV[2]), filtered_Image);
	return filtered_Image;
}



void SliderCallBack_RGB(int, void*){
	Mat filtered_Image = colorSegRGB(input_Image);
	imshow("RGB_filtered_Image", filtered_Image);
}

void SliderCallBack_HSV(int, void*){
	Mat filtered_Image = colorSegHSV(input_Image);
	imshow("HSV_filtered_Image", filtered_Image);
}

void help()
{
 cout << "\nThis program demonstrates Color Segment with simple Slidebar.\n"
	 "Usage:\n"
	 "./colorSegment <image_name>, Default is p1.jpg\n" << endl;
}

int main(int argc, char** argv){
	
	const char* filename = argc >= 2? argv[1] : "p1.jpg";

	input_Image = imread(filename, 1);
	
	if(input_Image.empty()){
		help();
		cout << "can not open " << filename << endl;
		return -1;
	}

	Size s = input_Image.size();
	cout << "Image.height: " << s.height << endl;
	cout << "Image.width: "	<< s.width << endl;
	cout << "Image.type: "	<< input_Image.type() << endl;

	namedWindow(WINDOW);
	
	createTrackbar( "min R:", WINDOW, minRGB,     255, SliderCallBack_RGB );
	createTrackbar( "min G:", WINDOW, (minRGB+1), 255, SliderCallBack_RGB );
	createTrackbar( "min B:", WINDOW, (minRGB+2), 255, SliderCallBack_RGB );
	createTrackbar( "max R:", WINDOW, maxRGB,     255, SliderCallBack_RGB );
	createTrackbar( "max G:", WINDOW, (maxRGB+1), 255, SliderCallBack_RGB );
	createTrackbar( "max B:", WINDOW, (maxRGB+2), 255, SliderCallBack_RGB );

	createTrackbar( "min H:", WINDOW, minHSV    , 180, SliderCallBack_HSV );
	createTrackbar( "min S:", WINDOW, (minHSV+1), 255, SliderCallBack_HSV );
	createTrackbar( "min V:", WINDOW, (minHSV+2), 255, SliderCallBack_HSV );
	createTrackbar( "max H:", WINDOW, maxHSV    , 180, SliderCallBack_HSV );
	createTrackbar( "max S:", WINDOW, (maxHSV+1), 255, SliderCallBack_HSV );
	createTrackbar( "max V:", WINDOW, (maxHSV+2), 255, SliderCallBack_HSV );

	imshow("input_Image", input_Image);
	waitKey();

	return 0;
}








