#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <laplacian_filter.h>
using namespace std;
using namespace cv; 

int main()
{
	Mat original = imread("/home/linux/Image processing/Pictures/colorflower.jpg");
	Mat gray,Gauss;
	cvtColor(original,gray,COLOR_BGR2GRAY);
	laplacian_filter(gray,50);
	return 0;
}