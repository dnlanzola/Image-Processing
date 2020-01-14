/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "./iptools/core.h"
#include <string.h>
#include <fstream>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	ifstream fp(argv[1]);
	char str[MAXLEN];
	char infile[MAXLEN];
	char outfile[MAXLEN];
	int checkQR = 0;
	int nOP;
	if (!fp.is_open()) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	fp >> nOP;
	for (int OP = 0; OP < nOP; OP++) {
		fp >> str;
		strcpy_s(infile, MAXLEN, str);

		fp >> str;
		strcpy_s(outfile, MAXLEN, str);

		fp >> str;
		if (strncmp(str, "opencv", 6) == 0) {
			cv::Mat src = cv::imread(infile);
			cv::Mat tgt;
			if (src.empty()) {
				cout << "Could not open or find the image: " << infile << endl;
				return -1;
			}

			fp >> str;
			cout << "Operation: " << str << endl;
			if (strncmp(str, "gray", 4) == 0) {
				utility::cv_gray(src, tgt);
			}
			else if (strncmp(str, "qr", 2) == 0) {
				cout << "Attempting to read QR-Data" << endl;
				utility::cv_qr(src);
				checkQR = 1;
			}

			else if (strncmp(str, "equalization", 2) == 0) {
				int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
				fp >> roi;
				cout << "Applying Histogram Equalization." << endl;
				switch (roi)
				{
				case 1:
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
					break;

				case 2:
					i = 0;

						fp >> x1;
						fp >> dx1;
						fp >> y1;
						fp >> dy1;
						fp >> x2;
						fp >> dx2;
						fp >> y2;
						fp >> dy2;

						utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
						utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);

					break;

				case 3:
					i = 0;

						fp >> x1;
						fp >> dx1;
						fp >> y1;
						fp >> dy1;
						fp >> x2;
						fp >> dx2;
						fp >> y2;
						fp >> dy2;
						fp >> x3;
						fp >> dx3;
						fp >> y3;
						fp >> dy3;
						utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
						utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);
						utility::cv_histogramE(src, tgt, x3, dx3, y3, dy3, 1);

					break;
				}
				
				
			}

			else if (strncmp(str, "stretching", 2) == 0) {
				int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
				fp >> roi;
				cout << "Applying Histogram Stretching." << endl;
				switch (roi)
				{
				case 1:
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cv_histogramS(src, tgt, x1, dx1, y1, dy1, 0);
					break;

				case 2:

						fp >> x1;
						fp >> dx1;
						fp >> y1;
						fp >> dy1;
						fp >> x2;
						fp >> dx2;
						fp >> y2;
						fp >> dy2;

						utility::cv_histogramS(src, tgt, x1, dx1, y1, dy1, 0);
						utility::cv_histogramS(src, tgt, x2, dx2, y2, dy2, 1);

					break;

				case 3:

						fp >> x1;
						fp >> dx1;
						fp >> y1;
						fp >> dy1;
						fp >> x2;
						fp >> dx2;
						fp >> y2;
						fp >> dy2;
						fp >> x3;
						fp >> dx3;
						fp >> y3;
						fp >> dy3;
						utility::cv_histogramS(src, tgt, x1, dx1, y1, dy1, 0);
						utility::cv_histogramS(src, tgt, x2, dx2, y2, dy2, 1);
						utility::cv_histogramS(src, tgt, x3, dx3, y3, dy3, 1);

					break;
				}


			}

			else if (strncmp(str, "sobel", 2) == 0) {
			int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
			fp >> roi;
			cout << "Applying Sobel Edge Detector." << endl;
			switch (roi)
			{
			case 1:
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 0);
				break;

			case 2:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;

					utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_sobel(src, tgt, x2, dx2, y2, dy2, 1);

				break;

			case 3:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					fp >> x3;
					fp >> dx3;
					fp >> y3;
					fp >> dy3;
					utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_sobel(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_sobel(src, tgt, x3, dx3, y3, dy3, 1);

				break;
			}


			}


			else if (strncmp(str, "canny", 2) == 0) {
			int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
			fp >> roi;
			cout << "Applying Canny Edge Detector." << endl;
			switch (roi)
			{
			case 1:
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 0);
				break;

			case 2:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;

					utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_canny(src, tgt, x2, dx2, y2, dy2, 1);

				break;

			case 3:
				i = 0;
				while (i < 3)
				{
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					fp >> x3;
					fp >> dx3;
					fp >> y3;
					fp >> dy3;
					utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_canny(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_canny(src, tgt, x3, dx3, y3, dy3, 1);
					i++;
				}
				break;
			}


			}


			else if (strncmp(str, "histcanny", 5) == 0) {
			int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
			fp >> roi;
			cout << "Applying Histogram Equalization + Canny Edge Detector." << endl;
			switch (roi)
			{
			case 1:
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
				utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 1);
				break;

			case 2:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 1);
					utility::cv_canny(src, tgt, x2, dx2, y2, dy2, 1);

				break;

			case 3:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					fp >> x3;
					fp >> dx3;
					fp >> y3;
					fp >> dy3;
					utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_histogramE(src, tgt, x3, dx3, y3, dy3, 1);
					utility::cv_canny(src, tgt, x1, dx1, y1, dy1, 1);
					utility::cv_canny(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_canny(src, tgt, x3, dx3, y3, dy3, 1);

				break;
			}


			}

			else if (strncmp(str, "histsobel", 5) == 0) {
			int i, color, roi, x1, y1, dx1, dy1, x2, dx2, y2, dy2, x3, dx3, y3, dy3;
			fp >> roi;

			cout << "Applying Histogram Equalization + Sobel Edge Detector." << endl;
			switch (roi)
			{
			case 1:
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
				utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 1);
				break;

			case 2:


					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 1);
					utility::cv_sobel(src, tgt, x2, dx2, y2, dy2, 1);

				break;

			case 3:

					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					fp >> x2;
					fp >> dx2;
					fp >> y2;
					fp >> dy2;
					fp >> x3;
					fp >> dx3;
					fp >> y3;
					fp >> dy3;
					utility::cv_histogramE(src, tgt, x1, dx1, y1, dy1, 0);
					utility::cv_histogramE(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_histogramE(src, tgt, x3, dx3, y3, dy3, 1);
					utility::cv_sobel(src, tgt, x1, dx1, y1, dy1, 1);
					utility::cv_sobel(src, tgt, x2, dx2, y2, dy2, 1);
					utility::cv_sobel(src, tgt, x3, dx3, y3, dy3, 1);

				break;
			}


			}

			else if (strncmp(str, "blur_avg", 8) == 0) {
				int windowSize;
				fp >> windowSize;
				utility::cv_avgblur(src, tgt, windowSize);
			}
			else {
				printf("No function: %s\n", str);
				continue;
			}

			if (checkQR = 0)
				cv::imwrite(outfile, tgt);
			checkQR = 0;
		}
		else {
			image src, tgt;
			src.read(infile);
			if (strncmp(str, "add", 3) == 0) {
				/* Add Intensity */
				fp >> str;
				utility::addGrey(src, tgt, atoi(str));
			}

			else if (strncmp(str, "binarize", 8) == 0) {
				/* Thresholding */
				fp >> str;
				utility::binarize(src, tgt, atoi(str));
			}

			else if (strncmp(str, "scale", 5) == 0) {
				/* Image scaling */
				fp >> str;
				utility::scale(src, tgt, atof(str));
			}

			else {
				printf("No function: %s\n", str);
				continue;
			}

			tgt.save(outfile);
		}
	}
	//fclose(fp);
	fp.close();
	return 0;
}

