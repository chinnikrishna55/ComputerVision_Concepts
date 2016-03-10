#include "opencv2/opencv.hpp"
#include <opencv2/features2d.hpp>
#include<vector>
using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    Ptr<AKAZE> akaze = AKAZE::create(AKAZE::DESCRIPTOR_MLDB, 64, 1, 0.001f, 2, 2,KAZE::DIFF_PM_G2);
    namedWindow("Video Stream",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
	double t = (double)getTickCount();
	vector<KeyPoint> kpts1, kpts2;
	Mat desc1, desc2;
	akaze->detectAndCompute(frame, noArray(), kpts1, desc1);
	t = ((double)getTickCount() - t)/getTickFrequency();
        drawKeypoints( frame, kpts1, frame, Scalar(0,0,255), DrawMatchesFlags::DEFAULT );
	char text[100];
	sprintf(text,"FPS: %lf", 1/t);
	putText(frame, text, cvPoint(30,30),
	    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	imshow("Video Stream", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
