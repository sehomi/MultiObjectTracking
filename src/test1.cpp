
#include "tracker.h"


int main(int argc, char **arv)
{

	ObjectTracker tracker(TrackerMode::TRACKER_SINGLE, TrackerName::TRACKER_MOSSE);

	cv::VideoCapture vc;

	if (!vc.open("../video/1.mp4")) 
	{
		std::cout << "Could not open video file." << std::endl;
		return 1;
	}

	cv::Mat frame;
	if ( vc.read(frame) )
	{
		cv::Rect2d ROI = cv::selectROI(frame);
		tracker.init(frame, ROI);
	}
	else
	{
		std::cout << "Could not read from video file." << std::endl;
		return 1;
	}

	cv::Rect2d bbox;
	while( vc.read(frame) )
	{
		cv::Mat frameCopy = frame.clone();
		if ( tracker.track(frame, bbox) )
		{
			cv::rectangle(frameCopy, bbox, cv::Scalar(0,255,0), 2, 1);
		}

		cv::imshow("Single Object Tracking", frameCopy);
		cv::waitKey(20);
	}

	return 0;
}