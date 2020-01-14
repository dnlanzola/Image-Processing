#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void cv_gray(cv::Mat &src, cv::Mat &tgt);
		static void cv_avgblur(cv::Mat &src, cv::Mat &tgt, int WindowSize);
		static void cv_histogramS(cv::Mat &src, cv::Mat &tgt, int x1, int y1, int szX1, int szY1, int check);
		static void cv_histogramE(cv::Mat &src, cv::Mat &tgt, int x1, int y1, int szX1, int szY1, int check);
		static void cv_sobel(cv::Mat &src, cv::Mat &tgt, int x1, int y1, int szX1, int szY1, int check);
		static void cv_canny(cv::Mat &src, cv::Mat &tgt, int x1, int y1, int szX1, int szY1, int check);
		static void cv_qr(cv::Mat &src);
};

#endif

