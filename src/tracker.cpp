
#include "tracker.h"

ObjectTracker::ObjectTracker(TrackerMode trackerMode, TrackerName trackerName)
{

	this->_trackerMode = trackerMode;
	this->_trackerName = trackerName;

	if (trackerMode == TrackerMode::TRACKER_SINGLE){
		this->_tracker = createTracker(trackerName);
	}
	else if (trackerMode == TrackerMode::TRACKER_MULTI)
	{
		this->_multiTracker = cv::MultiTracker::create();
	}
}

cv::Ptr<cv::Tracker> ObjectTracker::createTracker(TrackerName trackerName)
{
	if (trackerName == TrackerName::TRACKER_KCF)
		return cv::TrackerKCF::create();
	else if (trackerName == TrackerName::TRACKER_MIL)
		return cv::TrackerMIL::create();
	else if (trackerName == TrackerName::TRACKER_CSRT)
		return cv::TrackerCSRT::create();
	else if (trackerName == TrackerName::TRACKER_MOSSE)
		return cv::TrackerMOSSE::create();
	else if (trackerName == TrackerName::TRACKER_GOTURN)
		return cv::TrackerGOTURN::create();

	std::cout << "Error. Invalid tracker is set. Setting KCF tracker as default." << std::endl;
	return cv::TrackerKCF::create();
}

void ObjectTracker::init(cv::Mat &frame, cv::Rect2d target)
{
	this->_tracker->init(frame, target);
}

void ObjectTracker::init(cv::Mat &frame, std::vector<cv::Rect> &targets)
{
	for (int i=0; i<targets.size(); i++){
		this->_multiTracker->add(createTracker(this->_trackerName), frame, cv::Rect2d(targets[i]) );
	}
}

bool ObjectTracker::track(cv::Mat &frame, cv::Rect2d &newTarget)
{

	bool success = false;

	if (this->_trackerMode == TrackerMode::TRACKER_SINGLE)
	{
		success = this->_tracker->update(frame, newTarget);
	}
	else
	{
		std::cout << "Error. Despite the specified tracking mode, \
					  this function is called in single-tracking mode." << std::endl;
	}

	return success;
}

bool ObjectTracker::track(cv::Mat &frame, std::vector<cv::Rect2d> &newTargets)
{

	bool success = false;

	if (this->_trackerMode == TrackerMode::TRACKER_SINGLE)
	{
		std::cout << "Error. Despite the specified tracking mode, \
					  this function is called in multi-tracking mode." << std::endl;
	}
	else
	{
		success = this->_multiTracker->update(frame);
		newTargets = this->_multiTracker->getObjects();
	}

	return success;
}

void ObjectTracker::getRandomColors(std::vector<cv::Scalar>& colors, int numColors)
{
  cv::RNG rng(0);
  for(int i=0; i < numColors; i++)
    colors.push_back(cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255))); 
}