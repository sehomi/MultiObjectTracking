#ifndef TRACKER_H
#define TRACKER_H

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include <iostream>

enum TrackerMode{
	TRACKER_SINGLE,
	TRACKER_MULTI
};

enum TrackerName{
	TRACKER_KCF,
	TRACKER_MIL,
	TRACKER_MOSSE,
	TRACKER_GOTURN
};

class ObjectTracker{

	public:

		ObjectTracker(TrackerMode, TrackerName);
		void init(cv::Mat &, cv::Rect2d);
		bool track(cv::Mat &, cv::Rect2d &);

	private:

		TrackerMode _trackerMode;
		cv::Ptr<cv::Tracker> _tracker;


};

#endif 