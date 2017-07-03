#pragma once

#include <opencv2\opencv.hpp>
#include <opencvLibs.h>
#include <vector>

namespace jun {

	class Tracker {

		cv::Ptr<cv::FastFeatureDetector> m_Ffd;

		cv::Mat m_StdOrgImg, m_StdGrayImg;
		std::vector<cv::Point2f> m_StdPts;

		double	m_DownScale;
		bool	m_isAffine, m_isHomography;
		
	public:
		/*
		@param downScale 0< val <1
		*/
		Tracker(double downScale = 1.0);
		~Tracker();

		cv::Mat     m_RigidTransform;		// 32FC1
		cv::Mat		m_Homography;			// 64FC1

		void detectFeature(const cv::Mat & grayimg, std::vector<cv::Point2f>& pts);

		void setStdImg(const cv::Mat &src);

		void cleanUp();

		void setDownScale(double downscale);

		bool processImage(const cv::Mat &img);

		void warpAffine(const cv::Mat &src, cv::Mat &dst);

		void warpHomography(const cv::Mat &src, cv::Mat &dst);

		//void warpImage(const cv::Mat &src, cv::Mat &dst);

		//void drawOptFlowMap(cv::Mat& cflowmap, cv::Mat &dst, int step = 15, const cv::Scalar& color = cv::Scalar(0, 200, 0));

		void drawPoints(const cv::Mat &src, cv::Mat &dst, const std::vector<cv::Point2f> &pts);

		//bool checkHomography(const cv::Mat &homography);

		double getDisparity();

		double *getPos();
	};

}