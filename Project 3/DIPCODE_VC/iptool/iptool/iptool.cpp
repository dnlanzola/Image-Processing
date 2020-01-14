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
/******************************************************************************************************************/
#define MAXLEN 256

int main(int argc, char** argv)
{
	image src, tgt, tgtAmp, tgtBin, tgtBinT;
	ifstream fp(argv[1]);
	char str[MAXLEN];
	rsize_t strmax = sizeof str;
	char outfile[MAXLEN], outfile2[MAXLEN], outfile3[MAXLEN];
	char *pch, *next_pch;
	int nOP;
	if (!fp.is_open()) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	fp >> nOP;
	for (int OP = 0; OP < nOP; OP++) {
		fp >> str;		//input img
		src.read(str);
		cout << (str) << endl;

		fp >> str;		//output img tgtAmp
		strcpy_s(outfile, MAXLEN, str);
		cout << (str) << endl;

		fp >> str;		//output img tgtBin
		strcpy_s(outfile2, MAXLEN, str);
		cout << (str) << endl;

		fp >> str;		//output img tgtBinT
		strcpy_s(outfile3, MAXLEN, str);
		cout << (str) << endl;

		fp >> str;		//function
		cout << (str) << endl;
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

		else if (strncmp(str, "grayED", MAXLEN) == 0) {
			int i, roi, t1, theta1, theta2, theta3, x1, y1, dx1, dy1, t2, x2, y2, dx2, dy2, t3, x3, y3, dx3, dy3;
			fp >> roi;

			switch (roi)
			{
			case 1:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;

				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);

				break;

			case 2:

				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;

				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);

				break;

			case 3:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;
				fp >> t3;
				fp >> theta3;
				fp >> x3;
				fp >> dx3;
				fp >> y3;
				fp >> dy3;

				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);
				utility::grayEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t3, theta3, x3, dx3, y3, dy3);

				break;
			}


		}

		else if (strncmp(str, "compassED", MAXLEN) == 0) {
			int i, roi, t1, theta1, theta2, theta3, x1, y1, dx1, dy1, t2, x2, y2, dx2, dy2, t3, x3, y3, dx3, dy3;
			fp >> roi;

			switch (roi)
			{
			case 1:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;

				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);

				break;

			case 2:

				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;

				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);

				break;

			case 3:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;
				fp >> t3;
				fp >> theta3;
				fp >> x3;
				fp >> dx3;
				fp >> y3;
				fp >> dy3;

				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);
				utility::compassEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t3, theta3, x3, dx3, y3, dy3);

				break;
			}


		}

		else if (strncmp(str, "colorED", MAXLEN) == 0) {
			int i, roi, t1, theta1, theta2, theta3, x1, y1, dx1, dy1, t2, x2, y2, dx2, dy2, t3, x3, y3, dx3, dy3;
			fp >> roi;

			switch (roi)
			{
			case 1:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;

				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);

				break;

			case 2:

				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;

				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);

				break;

			case 3:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;
				fp >> t3;
				fp >> theta3;
				fp >> x3;
				fp >> dx3;
				fp >> y3;
				fp >> dy3;

				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);
				utility::colorEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t3, theta3, x3, dx3, y3, dy3);

				break;
			}
		}

		else if (strncmp(str, "hsiED", MAXLEN) == 0) {
			int i, roi, t1, theta1, theta2, theta3, x1, y1, dx1, dy1, t2, x2, y2, dx2, dy2, t3, x3, y3, dx3, dy3;
			fp >> roi;

			switch (roi)
			{
			case 1:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;

				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);

				break;

			case 2:

				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;

				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);

				break;

			case 3:
				fp >> t1;
				fp >> theta1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				fp >> t2;
				fp >> theta2;
				fp >> x2;
				fp >> dx2;
				fp >> y2;
				fp >> dy2;
				fp >> t3;
				fp >> theta3;
				fp >> x3;
				fp >> dx3;
				fp >> y3;
				fp >> dy3;

				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t1, theta1, x1, dx1, y1, dy1);
				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t2, theta2, x2, dx2, y2, dy2);
				utility::hsiEdgeDetection(src, tgtAmp, tgtBin, tgtBinT, t3, theta3, x3, dx3, y3, dy3);

				break;
			}
		}


	}



tgtAmp.save(outfile);
tgtBin.save(outfile2);
tgtBinT.save(outfile3);

//fclose(fp);
fp.close();
return 0;
}

