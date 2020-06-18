#ifndef TRACKER_H
#define TRACKER_H

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include <iostream>
#include <vector>

enum TrackerMode{
	TRACKER_SINGLE,
	TRACKER_MULTI
};

enum TrackerName{
	TRACKER_KCF,
	TRACKER_MIL,
	TRACKER_CSRT,
	TRACKER_MOSSE,
	TRACKER_GOTURN
};

class ObjectTracker{

	public:

		ObjectTracker(TrackerMode, TrackerName);
		void init(cv::Mat &, cv::Rect2d);
		void init(cv::Mat &, std::vector<cv::Rect> &);
		bool track(cv::Mat &, cv::Rect2d &);
		bool track(cv::Mat &, std::vector<cv::Rect2d> &);
		void getRandomColors(std::vector<cv::Scalar>& colors, int numColors);

	private:

		TrackerMode _trackerMode;
		TrackerName _trackerName;
		cv::Ptr<cv::Tracker> _tracker;
		cv::Ptr<cv::MultiTracker> _multiTracker;

		cv::Ptr<cv::Tracker> createTracker(TrackerName);


};

#endif 