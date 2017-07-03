#pragma once

#include "disparity.h"
#include <qdebug.h>

iMiner::DisparityMaker::DisparityMaker(double downscale) {
	this->downscale = downscale;

	sgbmWinSize = 5;
	numberOfDisparities = 16 * 1;
	minDisparites = 0;
	cn = 3;
	lambda = 8000.0;
	sigma = 1.5;
	//vis_multi = 1.0;

	sgbm = cv::StereoSGBM::create(minDisparites, numberOfDisparities, sgbmWinSize);
	wls_filter = cv::ximgproc::createDisparityWLSFilter(sgbm);
	sm = cv::ximgproc::createRightMatcher(sgbm);

	sgbm->setBlockSize(sgbmWinSize);
	sgbm->setNumDisparities(numberOfDisparities);
	sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);

	wls_filter->setLambda(lambda);
	wls_filter->setSigmaColor(sigma);
}

iMiner::DisparityMaker::~DisparityMaker() {
	sgbm.release();
	wls_filter.release();
	sm.release();
}

void iMiner::DisparityMaker::setDownScale(double downscale) {
	this->downscale = downscale;
}

void iMiner::DisparityMaker::setting(int pPreFilter, int winblockSize, 
	int pnumberOfDisparities, int mindisparities,
	int channel, double pLambda, double pSigma, int method) {

	this->sgbmWinSize = winblockSize;
	this->numberOfDisparities = pnumberOfDisparities;
	this->minDisparites = mindisparities;
	this->cn = channel;
	this->lambda = pLambda;
	this->sigma = pSigma;

	sgbm->setPreFilterCap(pPreFilter);
	sgbm->setBlockSize(sgbmWinSize);
	sgbm->setNumDisparities(numberOfDisparities);
	sgbm->setP1( 8 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setMode(method);

	wls_filter->setLambda(lambda);
	wls_filter->setSigmaColor(sigma);
}

void iMiner::DisparityMaker::compute(const cv::Mat & pLeft, const cv::Mat & pRight) {
	cv::Mat reLeft, reRight;
	cv::resize(pLeft, reLeft, cv::Size(), downscale, downscale);
	cv::resize(pRight, reRight, cv::Size(), downscale, downscale);
	if (reLeft.channels() > 1) {
		cv::cvtColor(reLeft, reLeft, CV_BGR2GRAY);
	}
	if (reRight.channels() > 1) {
		cv::cvtColor(reRight, reRight, CV_BGR2GRAY);
	}

	sgbm->compute(reLeft, reRight, imgDisparity16S);
	sm->compute(reRight, reLeft, imgDisparity16Sr);
	
	filter(reLeft);
	reproject(pLeft);
}

void iMiner::DisparityMaker::reproject(const cv::Mat &color) {
	if (!imgFilteredDisparity8U.empty()) {
		cv::Mat tmp;
		cv::resize(imgFilteredDisparity8U, tmp, cv::Size(), (1.0 / downscale), (1.0 / downscale));
		imgReproject = cv::Mat(tmp.size(), CV_32FC3);

		unsigned char *depthData = (unsigned char *)tmp.data;
		float *xyzData = (float *)imgReproject.data;

		int width = imgReproject.cols, height = imgReproject.rows;
		
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				xyzData[r*(width * 3) + (c * 3) + 0] = ((float)c / width);
				xyzData[r*(width * 3) + (c * 3) + 1] = ((float)r / height);
				xyzData[r*(width * 3) + (c * 3) + 2] = (depthData[r*width + c]/255.0);
			}
		}
		//imgReprojectColors.release();
		imgReprojectColors = color.clone();
	}
}

void iMiner::DisparityMaker::filter(const cv::Mat &pLeft) {
	wls_filter->filter(imgDisparity16S, pLeft, imgFilteredDisparity16S, imgDisparity16Sr);
	double minVal, maxVal;
	minMaxLoc(imgDisparity16S, &minVal, &maxVal);

	imgFilteredDisparity16S.convertTo(imgFilteredDisparity8U, CV_8UC1, 255.0 / (maxVal - minVal));
}

cv::Mat iMiner::DisparityMaker::getVisDisparity() {
	cv::Mat res;
	double minVal, maxVal;
	minMaxLoc(imgDisparity16S, &minVal, &maxVal);

	imgDisparity16S.convertTo(res, CV_8UC1, 255.0 / (maxVal - minVal));

	cv::resize(res, res, cv::Size(), (1.0 / downscale), (1.0 / downscale));

	return res;
}

cv::Mat iMiner::DisparityMaker::getVisFiltedDisparity() {
	cv::Mat res;

	cv::resize(imgFilteredDisparity8U, res, cv::Size(), (1.0 / downscale), (1.0 / downscale));

	return res;
}

cv::Mat iMiner::DisparityMaker::getVisReprojectMat() {
	cv::Mat res;

	double minVal, maxVal;
	cv::minMaxLoc(imgReproject, &minVal, &maxVal);
	imgReproject.convertTo(res, CV_8UC1, 255.0 / (maxVal - minVal));

	return res;
}

cv::Mat iMiner::DisparityMaker::getReprojectMat() {
	return imgReproject;
}

cv::Mat iMiner::DisparityMaker::getReprojectColor() {
	return imgReprojectColors;
}
