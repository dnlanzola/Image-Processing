#include "utility.h"
#include <iostream> 
#include <algorithm> 

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
void utility::autoThresholding(image &src, image &tgt, int t1, int x1, int dx1, int y1, int dy1)
{
	int background, foreground;
	int threshold = t1;
	int limit = 50;

	background = 0;
	foreground = 0;
	int count1 = 0;
	int count2 = 0;
	int meanBackground, meanForeground;

	for (int i = 0; i < tgt.getNumberOfRows(); i++)
	{
		for (int j = 0; j < tgt.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				if (checkValue(tgt.getPixel(i, j)) > threshold)
				{
					foreground = foreground + checkValue(tgt.getPixel(i, j));
					count1 = count1 + 1;
				}

				else
				{
					background = background + checkValue(tgt.getPixel(i, j));
					count2 = count2 + 1;
				}

			}
		}
	}

	meanBackground = background / count2;
	meanForeground = foreground / count1;


	threshold = (meanBackground + meanForeground) / 2;



		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					if (checkValue(tgt.getPixel(i, j)) > threshold)
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

void utility::smoothing(image &src, image &tgt, int ws1, int x1, int y1, int dx1, int dy1)
{
	int x1Bound = x1;
	int y1Bound = y1;



		int val = 0;	//variable to hold values of pixels from window

		for (int i = 0; i < src.getNumberOfRows(); i++)
			for (int j = 0; j < src.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					int itX = i - ((ws1 - 1) / 2);
					int itY = j - ((ws1 - 1) / 2);

					if (itX < x1Bound || itX >(x1Bound + dx1) || itY < y1Bound || itY >(y1Bound + dy1))
					{
						tgt.setPixel(i, j, checkValue(src.getPixel(i, j)));
					}
					else
					{
						for (int k = 0; k < ws1; k++)
						{
							val += checkValue(src.getPixel(itX, j));
							itX++;
						}
						tgt.setPixel(i, j, (val / ws1));
						val = 0;

						for (int k = 0; k < ws1; k++)
						{
							val += checkValue(tgt.getPixel(i, itY));
							itY++;
						}
						tgt.setPixel(i, j, (val / ws1));
						val = 0;
					}
				}
				else
					tgt.setPixel(i, j, checkValue(src.getPixel(i, j)));

	}


}


/*-----------------------------------------------------------------------**/
void utility::autoColorThresholding(image &src, image &tgt, int t1, int hsi, int x1, int dx1, int y1, int dy1)
{
	int background, foreground;
	int threshold = t1;
	int limit = 50;

	double intensity, hue, saturation;
	double r, g, b;
	double rn;
	double gn;
	double bn;

	background = 0;
	foreground = 0;
	int count1 = 1;
	int count2 = 1;
	int meanBackground, meanForeground;

	for (int i = 0; i < tgt.getNumberOfRows(); i++)
	{
		for (int j = 0; j < tgt.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				
				if (checkValue(tgt.getPixel(i, j)) > threshold)
				{
					foreground = foreground + checkValue(tgt.getPixel(i, j));
					count1 = count1 + 1;
				}

				else
				{
					background = background + checkValue(tgt.getPixel(i, j));
					count2 = count2 + 1;
				}

			}
		}
	}

	meanBackground = background / count2;
	meanForeground = foreground / count1;


	threshold = (meanBackground + meanForeground) / 2;
	cout << "threshold: " << threshold << endl;
	cout << "hsi: " << hsi << endl;
	cout << "t1: " << t1 << endl;

	if (hsi == 1)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));

					intensity = (r + g + b) / 3.0;
					if (intensity > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}

	if (hsi == 2)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));
					rn = r / (r + g + b);
					gn = g / (r + g + b);
					bn = b / (r + g + b);

					intensity = (r + g + b) / 3.0;
					if (intensity > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}

	if (hsi == 3)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));

					saturation = 1 - 3 * min(rn, min(gn, bn));
					if (saturation > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}
}