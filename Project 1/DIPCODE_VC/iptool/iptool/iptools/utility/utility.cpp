#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

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
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::cbinarization(image &src, image &tgt, int color, int t1, int x1, int dx1, int y1, int dy1)
{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					if (checkValue(tgt.getPixel(i, j)) > t1)
						tgt.setPixel(i, j, 255);
					else
						tgt.setPixel(i, j, 0);
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}



}

/*-----------------------------------------------------------------------**/
void utility::cmodification(image &src, image &tgt, int r, int g, int b, int t1, int x1, int dx1, int y1, int dy1)
{
	for (int i = 0; i < src.getNumberOfRows(); i++)
	{
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				tgt.setPixel(i, j, RED, checkValue(tgt.getPixel(i, j, RED)) + r);
				tgt.setPixel(i, j, GREEN, checkValue(tgt.getPixel(i, j, GREEN)) + g);
				tgt.setPixel(i, j, BLUE, checkValue(tgt.getPixel(i, j, BLUE)) + b);
			}
			else
			{
				tgt.setPixel(i, j, RED, checkValue(tgt.getPixel(i, j, RED)));
				tgt.setPixel(i, j, GREEN, checkValue(tgt.getPixel(i, j, GREEN)));
				tgt.setPixel(i, j, BLUE, checkValue(tgt.getPixel(i, j, BLUE)));
			}
		}
	}

}

