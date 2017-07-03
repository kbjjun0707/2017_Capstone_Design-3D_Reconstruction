#include "optical_.h"

#include <qdebug.h>

using namespace std;

jun::Tracker::Tracker(double downScale) : m_DownScale(downScale), m_isAffine(false), m_isHomography(false) {
	m_RigidTransform = cv::Mat::eye(2, 3, CV_32FC1); //affine 2x3 in a 3x3 matrix
	m_Homography = cv::Mat::eye(3, 3, CV_64FC1);

	m_Ffd = cv::FastFeatureDetector::create();
	m_StdOrgImg.release();
}

jun::Tracker::~Tracker() {
	m_Ffd.release();
}

void jun::Tracker::detectFeature(const cv::Mat & grayimg, std::vector<cv::Point2f>& pts) {
	pts.clear();
	std::vector<cv::KeyPoint> kpts;
	cv::Mat tmp;
	cv::resize(grayimg, tmp, cv::Size(), m_DownScale, m_DownScale);
	m_Ffd->detect(tmp, kpts);
	cv::KeyPoint::convert(kpts, pts);
}

void jun::Tracker::setStdImg(const cv::Mat & src) {
	m_StdOrgImg = src.clone();
	cv::cvtColor(m_StdOrgImg, m_StdGrayImg, cv::COLOR_BGR2GRAY);
	detectFeature(m_StdGrayImg, m_StdPts);
}

void jun::Tracker::cleanUp() {
	m_StdOrgImg.release();
	m_StdGrayImg.release();
	m_StdPts.clear();

	m_RigidTransform = cv::Mat::eye(2, 3, CV_32FC1); //affine 2x3 in a 3x3 matrix
	m_Homography = cv::Mat::eye(3, 3, CV_64FC1);
}

void jun::Tracker::setDownScale(double downscale) {
	this->m_DownScale = downscale;
}

bool jun::Tracker::processImage(const cv::Mat &img) {
	m_isAffine = false;
	if (!m_StdGrayImg.empty()) {
		cv::Mat l_NxtGray;
		cv::cvtColor(img, l_NxtGray, CV_BGR2GRAY);

		//std::vector<cv::Point2f> l_NxtPts;
		//detectFeature(l_NxtGray, l_NxtPts);

		//std::vector<cv::Point2f> refinedA, refinedB;

		//std::vector<uchar> status;
		//std::vector<float> errors;

		//std::vector<cv::Point2f> ptsL_ = m_StdPts, ptsR_ = l_NxtPts;
		//cv::calcOpticalFlowPyrLK(m_StdGrayImg, l_NxtGray, ptsL_, ptsR_, status, errors);

		//refinedA.clear();
		//refinedB.clear();
		//for (unsigned int i = 0; i < status.size(); i++) {
		//	if (status[i] && (errors[i] < 6.0)) {
		//		refinedA.push_back(ptsL_[i]);
		//		refinedB.push_back(ptsR_[i]);
		//	} else {
		//		status[i] = 0;
		//	}
		//}

		cv::Mat tmpA, tmpB;
		cv::resize(m_StdGrayImg, tmpA, cv::Size(), m_DownScale, m_DownScale);
		cv::resize(l_NxtGray, tmpB, cv::Size(), m_DownScale, m_DownScale);

		m_RigidTransform = cv::estimateRigidTransform(tmpB, tmpA, false);
		if (m_RigidTransform.size() != cv::Size(3, 2)) {
			m_RigidTransform = cv::Mat::eye(2, 3, CV_32FC1);
			return false;
		}
		m_isAffine = true;
		return true;
	}
	return false;
}

void jun::Tracker::warpAffine(const cv::Mat &src, cv::Mat &dst) {
	dst = src.clone();

	cv::Mat rtf = m_RigidTransform.clone();
	//rtfinv.at<double>(0, 2) *= (1.0 / m_DownScale);
	rtf.at<double>(0, 2) = 0;
	rtf.at<double>(1, 2) *= (1.0 / m_DownScale);
	
	cv::warpAffine(dst, dst, rtf, cv::Size());
}

void jun::Tracker::warpHomography(const cv::Mat & src, cv::Mat & dst) {
	dst = src.clone();

	cv::Mat resHomo = m_Homography.clone();
	//resHomo.at<double>(0, 2) *= (1.0 / m_DownScale);
	resHomo.at<double>(0, 2) = 0;
	resHomo.at<double>(1, 2) *= (1.0 / m_DownScale);
	
	cv::warpPerspective(dst, dst, resHomo, cv::Size());
}

//void jun::Tracker::warpImage(const cv::Mat & src, cv::Mat & dst) {
//	if (m_isAffine) {
//		warpAffine(src, dst);
//		return;
//	}
//	warpHomography(src, dst);
//}
//
//void jun::Tracker::drawOptFlowMap(cv::Mat &src, cv::Mat &dst, int step, const cv::Scalar & color) {
//	
//
//	return;
//}

void jun::Tracker::drawPoints(const cv::Mat & src, cv::Mat & dst, const std::vector<cv::Point2f> &pts) {
	dst = src.clone();

	for (cv::Point2f p : pts)
		cv::circle(dst, (1.0/m_DownScale) * p, 3, cv::Scalar(0, 200, 0), CV_FILLED);
}

//bool jun::Tracker::checkHomography(const cv::Mat & homography) {
//	double *hp = (double *)homography.data;
//
//	if (
//		(((hp[0] * hp[4]) - (hp[1] * hp[3])) <= 0) ||
//		( sqrt((hp[0] * hp[0]) + (hp[3] * hp[3])) < 0.1) ||
//		( sqrt((hp[0] * hp[0]) + (hp[3] * hp[3])) > 4.0) ||
//		( sqrt((hp[1] * hp[1]) + (hp[4] * hp[4])) < 0.1) ||
//		( sqrt((hp[1] * hp[1]) + (hp[4] * hp[4])) > 4.0) ||
//		( sqrt((hp[6] * hp[6]) + (hp[8] * hp[8])) > 0.002)
//		//(((hp[0] * hp[4]) - (hp[1] * hp[3])) <= 0) ||
//		//(((hp[0] * hp[0]) + (hp[3] * hp[3])) < 0.01) ||
//		//(((hp[0] * hp[0]) + (hp[3] * hp[3])) > 16.0) ||
//		//(((hp[1] * hp[1]) + (hp[4] * hp[4])) < 0.01) ||
//		//(((hp[1] * hp[1]) + (hp[4] * hp[4])) > 16.0) ||
//		//(((hp[6] * hp[6]) + (hp[8] * hp[8])) > 0.000002)
//		) {
//		return false;
//	}
//
//	return true;
//}

double jun::Tracker::getDisparity() {
	double res = 0.0, tmp;
	if (m_isAffine) {
		tmp = (double)m_RigidTransform.at<double>(0, 2) / 2.0;
		if (tmp > 0) {
			for (int i = 1; res < tmp; i++) {
				res = (16.0 * i);
			}
		} else if (tmp < 0) {
			for (int i = 1; tmp < res; i++) {
				res = (-16.0*i);
			}
		}

		return res;
	}
	return res;
}

double * jun::Tracker::getPos() {
	double res[2] = { 0 };
	if (m_isAffine) {
		res[0] = (double)m_RigidTransform.at<float>(0, 2)*(1.0 / m_DownScale);
		res[1] = (double)m_RigidTransform.at<float>(1, 2)*(1.0 / m_DownScale);

		return res;
	}
	return res;
}

