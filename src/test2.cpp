
#include "tracker.h"


int main(int argc, char **arv)
{

	ObjectTracker tracker(TrackerMode::TRACKER_MULTI, TrackerName::TRACKER_CSRT);

	cv::VideoCapture vc;

	if (!vc.open("../video/1.mp4")) 
	{
		std::cout << "Could not open video file." << std::endl;
		return 1;
	}

	cv::Mat frame;
	std::vector<cv::Scalar> colors;
	if ( vc.read(frame) )
	{
		std::vector<cv::Rect> ROIs;
		cv::selectROIs("Single Object Tracking", frame, ROIs); 
		tracker.getRandomColors(colors, ROIs.size());
		tracker.init(frame, ROIs);
	}
	else
	{
		std::cout << "Could not read from video file." << std::endl;
		return 1;
	}

	std::vector<cv::Rect2d> bboxs;
	while( vc.read(frame) )
	{
		cv::Mat frameCopy = frame.clone();
		if ( tracker.track(frame, bboxs) )
		{
			for(unsigned i=0; i<bboxs.size(); i++)
		    {
		      rectangle(frameCopy, bboxs[i], colors[i], 2, 1);
		    }
		}

		cv::imshow("Single Object Tracking", frameCopy);
		cv::waitKey(1);
	}

	return 0;
}