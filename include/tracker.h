#ifndef TRACKER_H
#define TRACKER_H

#include "opencv2/opencv.hpp"
#include <iostream>

enum TrackerMode{
	TRACKER_SINGLE;
	TRACKER_MULTI;
};

enum TrackerName{
	TRACKER_KCF;
	TRACKER_MIL;
	TRACKER_MOSSE;
};

class Tracker{

	public:

		void Tracker(TrackerMode, TrackerName);
		void init(cv::Mat, cv::Rect2d);
		cv::Rect2d track(cv::Mat);

	private:

		TrackerMode _trackerMode;
		cv::Ptr _tracker;


};

#endif 