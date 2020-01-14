#include "utility.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define MAXRGB 255
#define MINRGB 0

using namespace cv;

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::cv_gray(Mat &src, Mat &tgt)
{
	cvtColor(src, tgt, COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cv_avgblur(Mat &src, Mat &tgt, int WindowSize)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}

void utility::cv_histogramS(Mat &src, Mat &tgt, int x1, int y1, int szX1, int szY1, int check)
{
	if (check == 0)
		cvtColor(src, src, COLOR_BGR2GRAY);
	cv::Rect r(x1, y1, szY1, szX1);
	cv::Mat ROI(src(r));
	normalize(ROI, ROI, 0, 255, NORM_MINMAX);

	tgt = src;
}

void utility::cv_histogramE(Mat &src, Mat &tgt, int x1, int y1, int szX1, int szY1, int check)
{
	if (check == 0)
		cvtColor(src, src, COLOR_BGR2GRAY);
	cv::Rect r(x1, y1, szY1, szX1);
	cv::Mat ROI(src(r));
	equalizeHist(ROI, ROI);

	tgt = src;
}

void utility::cv_sobel(Mat &src, Mat &tgt, int x1, int y1, int szX1, int szY1, int check)
{
	if (check == 0)
		cvtColor(src, src, COLOR_BGR2GRAY);

	cv::Mat gradX, gradY, absGradX, absGradY;
	cv::Rect r(x1, y1, szY1, szX1);
	cv::Mat ROI(src(r));

	//x
	Sobel(ROI, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradX, absGradX);

	//y
	Sobel(ROI, gradY, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradY, absGradY);
	addWeighted(absGradX, .5, absGradY, .5, 0, ROI);

	tgt = src;

}



void utility::cv_canny(Mat &src, Mat &tgt, int x1, int y1, int szX1, int szY1, int check)
{
	if (check == 0)
		cvtColor(src, src, COLOR_BGR2GRAY);



	cv::Mat detected_edges;
	cv::Rect r(x1, y1, szY1, szX1);
	cv::Mat ROI(src(r));

	blur(ROI, detected_edges, Size(3, 3));
	Canny(detected_edges, ROI, 50, 10 * 3, 3);

	tgt = src;

}


void utility::cv_qr(Mat &src)
{
	QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

	Mat bbox, rectifiedImage, dst;

	std::string data = qrDecoder.detectAndDecode(src, bbox, rectifiedImage);
	
	if (data.length() > 0)
		cout << "QR Data: " << data << endl;
	else
	{
		cout << "No data detected. Applying Sobel Edge Detector." << endl;
		cvtColor(src, src, COLOR_BGR2GRAY);
		equalizeHist(src, dst);
		data = qrDecoder.detectAndDecode(dst, bbox, rectifiedImage);
		if (data.length() > 0)
			cout << "QR Data: " << data << endl;
		else
			cout << "No data detected" << endl;


	}
		

}

