#pragma once

#include <opencv2\opencv.hpp>
#include <opencv2\xfeatures2d.hpp>

#include <vector>

namespace iMiner {

	class Tracker {
		cv::Mat	m_PrevGray;
		//cv::Ptr<cv::xfeatures2d::SURF> m_Surf;
		std::vector<cv::Point2f>	m_PreCorner, m_PosCorner;
		//std::vector<cv::KeyPoint>	m_PreKeyPnt, m_PosKeyPnt;
		//cv::Mat						m_PreDscrpt, m_PosDscrpt;

		double	m_DownScale;
		bool	m_isAffine, m_isHomography;
		int		m_MaxCorner;

	public:
		/*
		@param downScale 0< val <1
		*/
		Tracker(double downScale = 1.0);
		~Tracker();

		cv::Mat     m_RigidTransform;		// 32FC1
		cv::Mat		m_Homography;			// 64FC1

		void setStdImg(const cv::Mat &src);

		void setDownScale(double downscale);

		bool processImage(const cv::Mat &img);

		void warpAffine(const cv::Mat &src, cv::Mat &dst);

		void warpHomography(const cv::Mat &src, cv::Mat &dst);

		void warpImage(const cv::Mat &src, cv::Mat &dst);

		void drawOptFlowMap(cv::Mat& cflowmap, cv::Mat &dst, int step = 15, const cv::Scalar& color = cv::Scalar(0, 200, 0));

		void drawPoints(const cv::Mat &src, cv::Mat &dst);

		bool checkHomography(const cv::Mat &homography);

		double getDisparity();

		double *getPos();
	};

}