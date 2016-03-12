#pragma once

using namespace cv;

class BackgroundModel
{
	Ptr<BackgroundSubtractor> pMOG;
	Mat foreground;
public:
	BackgroundModel(void) { pMOG = createBackgroundSubtractorMOG2(); };
	Mat GetForegroundMask(Mat frame) { pMOG->apply(frame, foreground); return foreground; };
	~BackgroundModel(void) {};
};
