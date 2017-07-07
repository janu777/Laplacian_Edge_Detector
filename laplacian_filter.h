#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <gaussian_blur.h>
using namespace std;
using namespace cv;
void zero_crossing(Mat *Result1,Mat *Result2,int r,int c,int Threshold)
{
	int p,q;
	float max1,max2;
	float min1,min2;
	Mat new1,new2;
	new1 = Mat::zeros(r,c,CV_32F);
	new2 = Mat::zeros(r,c,CV_32F);
	for(int x =0;x<r;x++)
	{
		for(int y =0;y<c;y++)
		{		
			max1 = 0;
			max2 = 0;
			min1 = 0;
			min2 = 0;
			for(int u = -1;u<=1;u++)
			{
				for(int v = -1;v<=1;v++)
				{

					p = x + u;
					q = y + v;
					max1 = (Result1->at<float>(p,q)>max1)?Result1->at<float>(p,q):max1;
					max2 = (Result2->at<float>(p,q)>max2)?Result2->at<float>(p,q):max2;
					min1 = (Result1->at<float>(p,q)<min1)?Result1->at<float>(p,q):min1;
					min2 = (Result2->at<float>(p,q)<min2)?Result2->at<float>(p,q):min2;

				}
			}
			if(max1>Threshold && min1<-Threshold) new1.at<float>(x,y)=255;
			if(max2>Threshold && min2<-Threshold) new2.at<float>(x,y)=255; 
		}
	}
	*Result2 = new2;
	*Result1 = new1;
}
void laplacian_filter(Mat gray,int Threshold)
{
	int val_1,val_2;
	int c = gray.cols;
  	int r = gray.rows;
  	Mat laplace_kernel1 = (Mat_<double>(3, 3) << 0,1,0,1,-4,1,0,1,0);
  	Mat laplace_kernel2 = (Mat_<double>(3, 3) << 1, 1, 1, 1,-8,1,1,1,1);
  	//Mat Result1,Result2;
  	Mat Result1(r,c,CV_32F);
  	Mat Result2(r,c,CV_32F);
	for(int x = 0; x<r ; x++)
  	{
  		for(int y = 0; y<c ; y++)
  		{
        	val_1 = (int(gray.at<uchar>(x,y))*(-4))+int(gray.at<uchar>(x-1,y))+int(gray.at<uchar>(x+1,y))+int(gray.at<uchar>(x,y-1))+int(gray.at<uchar>(x,y+1));	
  			Result1.at<float>(x,y) = val_1;
  			val_2 = (int(gray.at<uchar>(x,y))*(-8))+int(gray.at<uchar>(x-1,y))+int(gray.at<uchar>(x-1,y-1))+int(gray.at<uchar>(x-1,y+1))+int(gray.at<uchar>(x+1,y))+int(gray.at<uchar>(x+1,y-1))+int(gray.at<uchar>(x+1,y+1))+int(gray.at<uchar>(x,y-1))+int(gray.at<uchar>(x,y+1));	
  			Result2.at<float>(x,y) = val_2;
  		}
  	}
  	zero_crossing(&Result1,&Result2,r,c,Threshold);
  	namedWindow("Laplace1", CV_WINDOW_NORMAL );
  	namedWindow("Laplace2", CV_WINDOW_NORMAL );
  	namedWindow("original", CV_WINDOW_NORMAL );
  	imshow("Laplace1",Result1);
  	imshow("Laplace2",Result2);
  	imshow("original",gray);
  	waitKey(0);
}