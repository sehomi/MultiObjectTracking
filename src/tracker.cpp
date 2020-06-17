
#include "tracker.h"

ObjectTracker::ObjectTracker(TrackerMode trackerMode, TrackerName trackerName){

	this->_trackerMode = trackerMode;

	if (trackerMode == TrackerMode::TRACKER_SINGLE){

		if (trackerName == TrackerName::TRACKER_KCF)
			this->_tracker = cv::TrackerKCF::create();
		else if (trackerName == TrackerName::TRACKER_MIL)
			this->_tracker = cv::TrackerMIL::create();
		else if (trackerName == TrackerName::TRACKER_MOSSE)
			this->_tracker = cv::TrackerMOSSE::create();
		else if (trackerName == TrackerName::TRACKER_GOTURN)
			this->_tracker = cv::TrackerGOTURN::create();
	}
	else if (trackerMode == TrackerMode::TRACKER_MULTI)
	{

	}
}

void ObjectTracker::init(cv::Mat &frame, cv::Rect2d target)
{
	this->_tracker->init(frame, target);
}

bool ObjectTracker::track(cv::Mat &frame, cv::Rect2d &newTarget)
{

	bool success = this->_tracker->update(frame, newTarget);

	return success;
}