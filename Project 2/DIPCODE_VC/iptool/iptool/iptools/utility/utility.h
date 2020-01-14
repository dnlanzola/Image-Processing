#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
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
		static void autoThresholding(image &src, image &tgt, int t1, int x1, int dx1, int y1, int dy1);
		static void cmodification(image &src, image &tgt, int r, int g, int b, int t1, int x1, int dx1, int y1, int dy1);
		static void smoothing(image &src, image &tgt, int ws1, int x1, int y1, int dx1, int dy1);
		static void autoColorThresholding(image &src, image &tgt, int t1, int hsi, int x1, int dx1, int y1, int dy1);
		//static void oneD(image &src, image &tgt, int ws1, int x1, int dx1, int y1, int dy1);
		//static void twoD(image &src, image &tgt, int ws1, int x1, int dx1, int y1, int dy1);
};

#endif

