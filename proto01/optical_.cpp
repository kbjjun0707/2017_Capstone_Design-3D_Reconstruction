#include "optical_.h"

using namespace std;

iMiner::Tracker::Tracker(double downScale) : m_DownScale(downScale), m_isAffine(false), m_isHomography(false), m_MaxCorner(1000) {
	m_RigidTransform = cv::Mat::eye(3, 3, CV_32FC1); //affine 2x3 in a 3x3 matrix
	m_Homography = cv::Mat::eye(3, 3, CV_64FC1);
	//m_Surf = cv::xfeatures2d::SURF::create();
	m_PrevGray.release();
}

iMiner::Tracker::~Tracker() {
	//m_Surf.release();
}

void iMiner::Tracker::setStdImg(const const cv::Mat & src) {
	cv::Mat l_NxtGray;
	cv::cvtColor(src, l_NxtGray, CV_BGR2GRAY);
	cv::resize(l_NxtGray, l_NxtGray, cv::Size(), m_DownScale, m_DownScale);

	cv::goodFeaturesToTrack(l_NxtGray, m_PosCorner, m_MaxCorner, 0.1, 5);
	//m_Surf->detectAndCompute(l_NxtGray, cv::Mat(), m_PosKeyPnt, m_PosDscrpt);

	//for (cv::KeyPoint k : m_PosKeyPnt)
	//	m_PosCorner.push_back(k.pt);
	
	m_PrevGray  = l_NxtGray;
	m_PreCorner = m_PosCorner;
	//m_PreKeyPnt = m_PosKeyPnt;
	//m_PreDscrpt = m_PosDscrpt;
}

void iMiner::Tracker::setDownScale(double downscale) {
	this->m_DownScale = downscale;
}

bool iMiner::Tracker::processImage(const cv::Mat &img) {
	if (!m_PrevGray.empty()) {
		cv::Mat l_NxtGray;
		cv::cvtColor(img, l_NxtGray, CV_BGR2GRAY);
		cv::resize(l_NxtGray, l_NxtGray, cv::Size(), m_DownScale, m_DownScale);

		cv::goodFeaturesToTrack(l_NxtGray, m_PosCorner, m_MaxCorner, 0.1, 5);
		//m_Surf->detectAndCompute(l_NxtGray, cv::Mat(), m_PosKeyPnt, m_PosDscrpt);

		//for (cv::KeyPoint k : m_PosKeyPnt)
		//	m_PosCorner.push_back(k.pt);

		std::vector<uchar> status; std::vector<float> errors;
		cv::calcOpticalFlowPyrLK(m_PrevGray, l_NxtGray, m_PreCorner, m_PosCorner, status, errors);

		if (cv::countNonZero(status) < (status.size()*0.7)) {
			m_RigidTransform = cv::Mat::eye(3, 3, CV_32FC1);
			m_Homography = cv::Mat::eye(3, 3, CV_64FC1);
			return false;
		}

		cv::Mat mask;
		m_Homography = cv::findHomography(m_PosCorner, m_PreCorner, mask, cv::RANSAC);
		m_isHomography = true;
		if (checkHomography(m_Homography)) {
			m_Homography = cv::Mat::eye(3, 3, CV_64FC1);
			m_isHomography = false;
		}

		cv::Mat newRigidTransform = cv::estimateRigidTransform(m_PosCorner, m_PreCorner, true);
		if (!newRigidTransform.empty()) {
			newRigidTransform.copyTo(m_RigidTransform.rowRange(0, 2));
			m_isAffine = true;
		} else {
			m_RigidTransform = cv::Mat::eye(3, 3, CV_32FC1);
			m_isAffine = false;
		}
	}
	//m_PrevGray  = l_NxtGray;
	//m_PreCorner = m_PosCorner;
	//m_PreKeyPnt = m_PosKeyPnt;
	//m_PreDscrpt = m_PosDscrpt;

	return true;
}

void iMiner::Tracker::warpAffine(const cv::Mat &src, cv::Mat &dst) {
	dst = src.clone();
	//cv::resize(src, res, cv::Size(), m_DownScale, m_DownScale);

	cv::Mat rtfinv = m_RigidTransform.clone();
	rtfinv.at<float>(0, 2) *= (1.0 / m_DownScale);
	rtfinv.at<float>(0, 2) = 0;
	rtfinv.at<float>(1, 2) *= (1.0 / m_DownScale);

	cout << m_RigidTransform << endl << endl;

	cv::warpAffine(dst, dst, rtfinv.rowRange(0, 2), cv::Size());
}

void iMiner::Tracker::warpHomography(const cv::Mat & src, cv::Mat & dst) {
	dst = src.clone();

	cv::Mat resHomo = m_Homography.clone();
	resHomo.at<double>(0, 2) *= (1.0 / m_DownScale);
	resHomo.at<double>(0, 2) = 0;
	resHomo.at<double>(1, 2) *= (1.0 / m_DownScale);

	cout << m_Homography << endl << endl;

	cv::warpPerspective(dst, dst, resHomo, cv::Size());
}

void iMiner::Tracker::warpImage(const cv::Mat & src, cv::Mat & dst) {
	if (m_isAffine) {
		warpAffine(src, dst);
		return;
	}
	warpHomography(src, dst);
}

void iMiner::Tracker::drawOptFlowMap(cv::Mat &src, cv::Mat &dst, int step, const cv::Scalar & color) {
	

	return;
}

void iMiner::Tracker::drawPoints(const cv::Mat & src, cv::Mat & dst) {
	dst = src.clone();

	for (cv::Point2f p : m_PosCorner)
		cv::circle(dst, (1.0/m_DownScale) * p, 3, cv::Scalar(0, 200, 0), CV_FILLED);
}

bool iMiner::Tracker::checkHomography(const cv::Mat & homography) {
	double *hp = (double *)homography.data;

	if (
		(((hp[0] * hp[4]) - (hp[1] * hp[3])) <= 0) ||
		( sqrt((hp[0] * hp[0]) + (hp[3] * hp[3])) < 0.1) ||
		( sqrt((hp[0] * hp[0]) + (hp[3] * hp[3])) > 4.0) ||
		( sqrt((hp[1] * hp[1]) + (hp[4] * hp[4])) < 0.1) ||
		( sqrt((hp[1] * hp[1]) + (hp[4] * hp[4])) > 4.0) ||
		( sqrt((hp[6] * hp[6]) + (hp[8] * hp[8])) > 0.002)
		//(((hp[0] * hp[4]) - (hp[1] * hp[3])) <= 0) ||
		//(((hp[0] * hp[0]) + (hp[3] * hp[3])) < 0.01) ||
		//(((hp[0] * hp[0]) + (hp[3] * hp[3])) > 16.0) ||
		//(((hp[1] * hp[1]) + (hp[4] * hp[4])) < 0.01) ||
		//(((hp[1] * hp[1]) + (hp[4] * hp[4])) > 16.0) ||
		//(((hp[6] * hp[6]) + (hp[8] * hp[8])) > 0.000002)
		) {
		return false;
	}

	return true;
}

double iMiner::Tracker::getDisparity() {
	double res = 0.0, tmp;
	if (m_isAffine) {
		tmp = (double)m_RigidTransform.at<float>(0, 2) / 2.0;
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
	tmp = m_Homography.at<double>(0, 2) / 2.0;
	for (int i = 1; res < tmp; i++) {
		res = (16.0 * i);
	}

	return res;
}

double * iMiner::Tracker::getPos() {
	double res[2] = { 0 };
	if (m_isAffine) {
		res[0] = (double)m_RigidTransform.at<float>(0, 2)*(1.0 / m_DownScale);
		res[1] = (double)m_RigidTransform.at<float>(1, 2)*(1.0 / m_DownScale);

		return res;
	}
	res[0] = m_Homography.at<double>(0, 2)*(1.0 / m_DownScale);
	res[1] = m_Homography.at<double>(1, 2)*(1.0 / m_DownScale);
	return res;
}

