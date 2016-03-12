// ForegroundMask.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
#include "BackgroundModel.h"

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
        	return -1;
    	cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    	cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	Mat videoFrame, foreground, out, videoFrameGray;
	BackgroundModel l_bgModel;
	namedWindow("Foreground Detection",1);
	while(1)
    	{
		cap >> videoFrame;
		cvtColor(videoFrame, videoFrameGray, COLOR_BGR2GRAY);
		foreground = l_bgModel.GetForegroundMask(videoFrameGray);
		hconcat(videoFrameGray, foreground, out);
		imshow("Foreground Detection", out);	
		if(waitKey(30) >= 0) break;
	}
	cap.release();
	return 0;
}


