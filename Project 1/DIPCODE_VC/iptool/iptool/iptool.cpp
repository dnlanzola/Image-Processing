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
	image src, tgt;
	ifstream fp(argv[1]);
	char str[MAXLEN];
	rsize_t strmax = sizeof str;
	char outfile[MAXLEN];
	char *pch, *next_pch;
	int nOP;
	if (!fp.is_open()) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	fp >> nOP;
	for (int OP = 0; OP < nOP; OP++) {
		fp >> str;
		src.read(str);

		fp >> str;
		strcpy_s(outfile, MAXLEN, str);

		fp >> str;
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

		else if (strncmp(str, "cbinarization", MAXLEN) == 0) {
			/* Channel Binarization */
			int i, color, roi, t1, x1, y1, dx1, dy1;
			fp >> roi;

			tgt.copyImage(src);

			switch (roi)
			{
			case 1:
				fp >> color;
				fp >> t1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cbinarization(src, tgt, color, t1, x1, dx1, y1, dy1);
				break;

			case 2:
				i = 0;
				while (i < 2)
				{
					fp >> color;
					fp >> t1;
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cbinarization(src, tgt, color, t1, x1, dx1, y1, dy1);
					i++;
				}
				break;

			case 3:
				i = 0;
				while (i < 3)
				{
					fp >> color;
					fp >> t1;
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cbinarization(src, tgt, color, t1, x1, dx1, y1, dy1);
					i++;
				}
				break;
			}

		}
		else if (strncmp(str, "cmodification", MAXLEN) == 0) {
			/* Color modification */
			int i, r, g, b, roi, t1, x1, y1, dx1, dy1;

			fp >> roi;
			fp >> r;
			fp >> g;
			fp >> b;
			
			tgt.copyImage(src);

			switch (roi)
			{
			case 1:

				fp >> t1;
				fp >> x1;
				fp >> dx1;
				fp >> y1;
				fp >> dy1;
				utility::cmodification(src, tgt, r, g, b, t1, x1, dx1, y1, dy1);
				break;

			case 2:
				i = 0;
				while (i < 2)
				{
					fp >> t1;
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cmodification(src, tgt, r, g, b, t1, x1, dx1, y1, dy1);
					i++;
				}
				break;

			case 3:
				i = 0;
				while (i < 3)
				{
					fp >> t1;
					fp >> x1;
					fp >> dx1;
					fp >> y1;
					fp >> dy1;
					utility::cmodification(src, tgt, r, g, b, t1, x1, dx1, y1, dy1);
					i++;
				}
				break;
			}
		}

	}


			


       
		tgt.save(outfile);
		
	//fclose(fp);
	fp.close();
	return 0;
}

